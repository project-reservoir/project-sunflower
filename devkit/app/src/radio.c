#include "radio.h"
#include "radio_config.h"
#include "cmsis_os.h"
#include "si446x_api_lib.h"
#include "si446x_cmd.h"
#include "spi.h"
#include "sensor_conversions.h"
#include "radio_packets.h"
#include "debug.h"

// Global variables
osMessageQId radioTxMsgQ;
osMessageQId radioRxMsgQ;
osMessageQId radioWakeupMsgQ;

uint8_t                 Radio_Configuration_Data_Array[]    = RADIO_CONFIGURATION_DATA_ARRAY;
tRadioConfiguration     RadioConfiguration                  = RADIO_CONFIGURATION_DATA;
tRadioConfiguration*    pRadioConfiguration                 = &RadioConfiguration;

uint8_t customRadioPacket[RADIO_MAX_PACKET_LENGTH];

// Local variables
static uint8_t          rxBuff[RADIO_MAX_PACKET_LENGTH];

static NetworkMember_t  networkTable[MAX_NETWORK_MEMBERS];

static RadioTaskState radioTaskState = CONNECTED;
static NetworkInfo    network;
static SensorData     sensorData;

// Local function prototypes
static uint8_t    SendRadioConfig(void);
static void       Radio_StartTx_Variable_Packet(uint8_t channel, uint8_t *pioRadioPacket, uint8_t length);
static void       Radio_StartRX(uint8_t channel);
static void       SignalRadioTXNeeded(void);
static SensorData ParseSensorMessage(uint8_t* radioMessage);

// Global function implementations
void RadioTaskOSInit(void)
{
    SPI_InitTypeDef spiConfig;
    
    osMessageQDef(RadioTxMsgQueue, RADIO_MSG_QUEUE_SIZE, RadioMessage*);
    osMessageQDef(RadioRxMsgQueue, RADIO_MSG_QUEUE_SIZE, RadioMessage*);
    osMessageQDef(RadioWakeupMsgQueue, RADIO_MSG_QUEUE_SIZE, RadioTaskWakeupReason);
    
    radioTxMsgQ = osMessageCreate(osMessageQ(RadioTxMsgQueue), NULL);
    radioRxMsgQ = osMessageCreate(osMessageQ(RadioRxMsgQueue), NULL);
    radioWakeupMsgQ = osMessageCreate(osMessageQ(RadioWakeupMsgQueue), NULL);
    
    assert_param(radioTxMsgQ != NULL);
    assert_param(radioRxMsgQ != NULL);
    assert_param(radioWakeupMsgQ != NULL);
    
    spiConfig.SPI_BaudRatePrescaler  = SPI_BaudRatePrescaler_256;
    spiConfig.SPI_Direction          = SPI_Direction_2Lines_FullDuplex;    
    spiConfig.SPI_CPHA               = SPI_CPHA_1Edge;
    spiConfig.SPI_CPOL               = SPI_CPOL_Low;
    spiConfig.SPI_DataSize           = SPI_DataSize_8b;
    spiConfig.SPI_FirstBit           = SPI_FirstBit_MSB;
    spiConfig.SPI_NSS                = SPI_NSS_Soft;
    spiConfig.SPI_Mode               = SPI_Mode_Master;
    
    SPI_Init(SPIn, &spiConfig);
    
    SPIn->CR1 |= SPI_CR1_SPE;
}

void RadioTaskHwInit(void)
{   
    GPIO_InitTypeDef    GPIO_InitStructure;
    EXTI_InitTypeDef    EXTI_InitStructure;
    
    SPIn_SCK_GPIO_CLK_ENABLE();
    SPIn_MISO_GPIO_CLK_ENABLE();
    SPIn_MOSI_GPIO_CLK_ENABLE();
    SPIn_CLK_ENABLE();
    
    GPIO_InitStructure.GPIO_Pin   = SPIn_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(SPIn_SCK_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = SPIn_MISO_PIN;
    GPIO_Init(SPIn_MISO_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = SPIn_MOSI_PIN;
    GPIO_Init(SPIn_MOSI_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(SPIn_SCK_GPIO_PORT, SPIn_SCK_PIN_SOURCE, SPIn_SCK_AF);
    GPIO_PinAFConfig(SPIn_MISO_GPIO_PORT, SPIn_MISO_PIN_SOURCE, SPIn_MISO_AF);
    GPIO_PinAFConfig(SPIn_MOSI_GPIO_PORT, SPIn_MOSI_PIN_SOURCE, SPIn_MOSI_AF);    
    
    GPIO_InitStructure.GPIO_Pin   = SPIn_NSS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(SPIn_NSS_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = RADIO_SDL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_Init(SPIn_NSS_GPIO_PORT, &GPIO_InitStructure);
    
    // NIRQ config
    GPIO_InitStructure.GPIO_Pin   = RADIO_NIRQ_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(RADIO_NIRQ_GPIO_PORT, &GPIO_InitStructure);
    
    // Configure NIRQ EXTI line
    SYSCFG_EXTILineConfig(RADIO_NIRQ_EXTI_PORT_SOURCE, RADIO_NIRQ_EXTI_PIN_SOURCE);
    EXTI_InitStructure.EXTI_Line = RADIO_NIRQ_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    // De-select all SPI devices
    GPIO_SetBits(SPIn_NSS_GPIO_PORT, SPIn_NSS_PIN);
}

void RadioTask(void)
{
    uint8_t             radioConfigured = 0;
    osEvent             msgQueueEvent;
    RadioMessage*       msg;
    NVIC_InitTypeDef    NVIC_InitStructure;
    
    // Delay to allow other tasks to start
    // Not delaying before starting the radio causes unpredictable behavior at boot!
    osDelay(2000);
    
    // Configure radio
    while(!radioConfigured)
    {
        if(SendRadioConfig() == SI446X_SUCCESS)
        {
            radioConfigured = 1;
        }
        else
        {
            // TODO: we should delay for a while before trying to reprogram the radio.
            // TODO: consider entering an ultra-low power mode if radio config fails?
            //       We can't send sensor readings without the radio, so performing
            //       sensor polling is probably a waste of power
            
            // TODO: do something else if Radio config fails
            assert_param(0);
        }
    }
    
    Radio_StartRX(pRadioConfiguration->Radio_ChannelNumber);
    
    // Now that the radio has been configured, enable radio interrupts
    NVIC_InitStructure.NVIC_IRQChannel = NIRQ_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
        
    while(1)
    {               
        switch(radioTaskState)
        {
            // Try and join the network. If success, enter CONNECTED state, else return to LOOKING_FOR_BASE_STATION
            case CONNECTING:
                break;
            
            // Perform regular radio duties. If we loose connection, enter the CONNECTING_TO_BASE_STATION state
            case CONNECTED:
                // Pend on the message queue that will wakeup the radio task. 
                // This can come from a TX event or an IRQ event
                msgQueueEvent = osMessageGet(radioWakeupMsgQ, osWaitForever);
                
                if(msgQueueEvent.status == osEventMessage)
                {
                    if(msgQueueEvent.value.v == RADIO_IRQ_DETECTED)
                    {
                        RadioTaskHandleIRQ();
                    }
                    else if(msgQueueEvent.value.v == RADIO_TX_NEEDED)
                    {
                        // Wait on the transmit queue
                        // TODO: this should timeout, since it should have a message in it already if we got this far
                        msgQueueEvent = osMessageGet(radioTxMsgQ, osWaitForever);
                        
                        if(msgQueueEvent.status == osEventMessage)
                        {
                            msg = (RadioMessage*)(msgQueueEvent.value.p);
                            ((generic_message_t*)(msg->pData))->dst = msg->dest;
                            ((generic_message_t*)(msg->pData))->src = RadioGetMACAddress();
                            
                            // Transmit the packet to the radio hardware
                            Radio_StartTx_Variable_Packet(pRadioConfiguration->Radio_ChannelNumber, msg->pData, msg->size);
                            
                            // Free the data
                            vPortFree(msg->pData);
                            vPortFree(msg);
                        }
                    }
                }
                break;
            
            // Send ANNOUNCE packets every 20 seconds and see if we get a reply
            case SEARCHING:
                // Send message
                // Wait for reply
                // If network found, store details and move to -> CONNECTING
                break;
        }
        
        osDelay(10);
    }
}

// The pointer passed into this function should have been allocated using 
// the osAlloc() routine: it will be freed using the osFree routine
void SendToDevice(uint8_t* data, uint8_t size, uint32_t mac)
{
    RadioMessage* message = pvPortMalloc(sizeof(RadioMessage));
    message->pData = data;
    message->size = size;
    message->dest = mac;
    
    // TODO: Check that this actually succeeded, and don't block forever.
    //       Might need to return a status to indicate to calling function that we failed to send message
    osMessagePut(radioTxMsgQ, (uint32_t)message, osWaitForever);
    
    SignalRadioTXNeeded();
}

// The pointer passed into this function should have been allocated using 
// the pvPortMalloc() routine: it will be freed using the osFree routine
void SendToBroadcast(uint8_t* data, uint8_t size)
{
    RadioMessage* message = pvPortMalloc(sizeof(RadioMessage));
    message->pData = data;
    message->size = size;
    message->dest = 0xFFFFFFFF; // Send to broadcast address
    
    // TODO: Check that this actually succeeded, and don't block forever.
    //       Might need to return a status to indicate to calling function that we failed to send message
    osMessagePut(radioTxMsgQ, (uint32_t)message, osWaitForever);
    
    SignalRadioTXNeeded();
}

// Local function implementations

uint8_t SendRadioConfig(void)
{
    uint16_t wDelay = 0;
    uint8_t retVal;
    
    si446x_reset();
    
    /* Wait until reset timeout or Reset IT signal */
    //for (wDelay = 0; wDelay < pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++);
    osDelay(100);
    
    taskENTER_CRITICAL();
    retVal = si446x_configuration_init(pRadioConfiguration->Radio_ConfigurationArray);
    taskEXIT_CRITICAL();
    
    return retVal;
}

void SignalRadioIRQ(void)
{
    // Wakeup the radio task by putting a message on it's "wakeup" queue.
    // TODO: Check that this actually succeeded, and don't block forever.
    //       Might need to return a status to indicate to calling function that we failed to send message
    osMessagePut(radioWakeupMsgQ, RADIO_IRQ_DETECTED, osWaitForever);
}

void SignalRadioTXNeeded(void)
{
    // Wakeup the radio task by putting a message on it's "wakeup" queue.
    // TODO: Check that this actually succeeded, and don't block forever.
    //       Might need to return a status to indicate to calling function that we failed to send message
    osMessagePut(radioWakeupMsgQ, RADIO_TX_NEEDED, osWaitForever);
}

void Radio_StartTx_Variable_Packet(uint8_t channel, uint8_t *pioRadioPacket, uint8_t length)
{
  /* Leave RX state */
  si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_READY);

  /* Read ITs, clear pending ones */
  si446x_get_int_status(0u, 0u, 0u);

  /* Reset the Tx Fifo */
  si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_TX_BIT);

  /* Fill the TX fifo with datas */
  si446x_write_tx_fifo(length, pioRadioPacket);

  /* Start sending packet, channel 0, START immediately */
   si446x_start_tx(channel, 0x30, length);
}

void Radio_StartRX(uint8_t channel)
{
    // Read ITs, clear pending ones
    si446x_get_int_status(0u, 0u, 0u);

    // Reset the FIFO
    si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);

    /* Start Receiving packet, channel 0, START immediately, Packet n bytes long */
    si446x_start_rx(channel, 0u, RadioConfiguration.Radio_PacketLength,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX );
}

void RadioTaskHandleIRQ(void)
{
    uint8_t phInt = 0;
    uint8_t chipInt = 0;
    uint8_t modemInt = 0;
    
    // Get the interrupts from the radio: clear them all
    si446x_get_int_status(0u, 0u, 0u);
    
    // Only process status flags if they triggered this interrupt
    phInt = Si446xCmd.GET_INT_STATUS.PH_PEND; // & Si446xCmd.GET_INT_STATUS.PH_STATUS;
    chipInt = Si446xCmd.GET_INT_STATUS.CHIP_PEND; // & Si446xCmd.GET_INT_STATUS.CHIP_STATUS;
    modemInt = Si446xCmd.GET_INT_STATUS.MODEM_PEND; // & Si446xCmd.GET_INT_STATUS.MODEM_STATUS;      
    
    // PACKET_SENT
    if(phInt & PACKET_SENT)
    {
        // TODO: Packet was transmitted, move to the "wait for ACK" state
    }
    
    // PACKET_RX
    if(phInt & PACKET_RX)
    {
        DEBUG("Radio RX Event\r\n");
        
        si446x_read_rx_fifo(RadioConfiguration.Radio_PacketLength, rxBuff);
        
        generic_message_t* message = (generic_message_t*)rxBuff;
        generic_message_t* generic_msg;
        
        if(message->dst == RadioGetMACAddress() || message->dst == 0xFFFFFFFF)
        {
            switch(message->cmd)
            {
                // The base station has requested info from us: reply with it
                case DEVICE_INFO:
                    // TODO: Store the response for later sending to Bouquet
                    break;
                
                case SENSOR_MSG:
                    DEBUG("Sensor Message\r\n");
                    // TODO: Store the response for later sending to Bouquet
                    break;
                
                case FW_UPD_START:
                    // TODO: shouldn't receive this ever (since only 1 Sunflower exists!)
                    break;
                
                case FW_UPD_END:
                    // TODO: shouldn't receive this ever (since only 1 Sunflower exists!)
                    break;
                    
                case FW_UPD_PAYLOAD:
                    // TODO: shouldn't receive this ever (since only 1 Sunflower exists!)
                    break;
                
                case PING:
                    DEBUG("PING\r\n");
                    generic_msg = pvPortMalloc(sizeof(generic_message_t));
                
                    // TODO: check we didn't run out of RAM (we should catch this in the 
                    //       application Malloc failed handler, but just in case)
                
                    generic_msg->cmd = PONG;
                    generic_msg->src = RadioGetMACAddress();
                    generic_msg->dst = message->src;
                
                    SendToBroadcast((uint8_t*)generic_msg, sizeof(generic_message_t));
                    break;

                case PONG:
                    INFO("PONG\r\n");
                    break;
                
                case ANNOUNCE:
                    DEBUG("ANNOUNCE RECEIVED\r\n");
                    generic_msg = pvPortMalloc(sizeof(generic_message_t));
                
                    // TODO: check we didn't run out of RAM (we should catch this in the 
                    //       application Malloc failed handler, but just in case)
                
                    generic_msg->cmd = JOIN;
                    generic_msg->src = RadioGetMACAddress();
                    generic_msg->dst = message->src;
                
                    SendToBroadcast((uint8_t*)generic_msg, sizeof(generic_message_t));
                    break;
            }
        }
    }
    
    // CRC_ERROR
    if(phInt & CRC_ERROR)
    {
        // TODO: Recevied a garbled packet. Reply with a NAK
    }
     
    // Other interesting interrupts:
    //  CHIP_READY
    //  LOW_BATT
    //  CMD_ERROR
    //  FIFO_UNDERFLOW_OVERFLOW_ERROR
    //  FILTER_MATCH 
    //  SYNC_DETECT
    //  PREAMBLE_DETECT
    //  RSSI
    //  RSSI_JUMP
    //  INVALID_SYNC
    //  TX_FIFO_ALMOST_EMPTY
    //  RX_FIFO_ALMOST_FULL
    
    Radio_StartRX(pRadioConfiguration->Radio_ChannelNumber);
}

uint32_t RadioGetMACAddress(void)
{
    return *((uint32_t*)0x1FFF7A10);
}

