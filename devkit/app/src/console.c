#include "cmsis_os.h"
#include "stm32f4xx.h"
#include "uart.h"
#include "console.h"
#include "app_header.h"
#include "debug.h"
#include "radio.h"
#include "radio_packets.h"
#include <string.h>

osMessageQId        uartRxMsgQ;

uint8_t             rxBuff[CONSOLE_MAX_MSG_SIZE];
uint8_t             txBuff[CONSOLE_MAX_MSG_SIZE];
uint8_t             tmpHALRxBuff;

uint8_t             rxBuffPos = 0;
uint8_t             txBuffPos = 0;

uint8_t             console_task_started = 0;

char                testString[] = {"TEST TEST TEST"};

static void         processString(char* str);
static uint8_t      string_len(char* str);
static void         processDebugCommand(char* str, uint8_t len);
static void         processRadioCommand(char* str, uint8_t len);

void ConsoleTaskHwInit(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    
    USARTn_TX_GPIO_CLK_ENABLE();
    USARTn_RX_GPIO_CLK_ENABLE();
    USARTn_CLK_ENABLE(); 
    
    GPIO_InitStructure.GPIO_Pin   = USARTn_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(USARTn_TX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = USARTn_RX_PIN;
    GPIO_Init(USARTn_RX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(USARTn_TX_GPIO_PORT, USARTn_TX_PIN_SOURCE, USARTn_TX_AF);
    GPIO_PinAFConfig(USARTn_RX_GPIO_PORT, USARTn_RX_PIN_SOURCE, USARTn_RX_AF);    

    NVIC_InitStructure.NVIC_IRQChannel = USARTn_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_LOWEST_INTERRUPT_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void ConsoleTaskOSInit(void)
{
    USART_InitTypeDef config;
    osMessageQDef(UARTRxMsgQueue, CONSOLE_MSG_Q_SIZE, char*);
    uartRxMsgQ = osMessageCreate(osMessageQ(UARTRxMsgQueue), NULL);
    
    config.USART_BaudRate               = 115200;
    config.USART_HardwareFlowControl    = USART_HardwareFlowControl_None;
    config.USART_Mode                   = USART_Mode_Rx | USART_Mode_Tx;
    config.USART_Parity                 = USART_Parity_No;
    config.USART_StopBits               = USART_StopBits_1;
    config.USART_WordLength             = USART_WordLength_8b;

    USART_Init(USARTn, &config);
}

void ConsoleTask(void)
{
    osEvent msgQueueEvent;
    char* rxChars = NULL;
    
    UART_Start(USARTn);
    
    while(1)
    {
        UART_StartRX(USARTn);
        
        console_task_started = 1;
        
        // Sleep until we receive some data
        msgQueueEvent = osMessageGet(uartRxMsgQ, osWaitForever);
        
        if(msgQueueEvent.status == osEventMessage)
        {
            rxChars = (char*)msgQueueEvent.value.p;
            processString(rxChars);
        }
        
        memset(rxBuff, 0, CONSOLE_MAX_MSG_SIZE);
        rxBuffPos = 0;
    }
}

void processString(char* str)
{
    uint8_t len = string_len(str);
    uint8_t i;
    
    (void)i;
    
    ConsolePrint("\r\n");
    
    switch(str[0])
    {
        case 'r':
            if(len >= 2)
            {
                if(str[1] == 'r')
                {
                    NVIC_SystemReset();
                }
            }
            else
            {
                ConsolePrint("Reset commands\r\n");
                ConsolePrint("rr: reset the microprocessor completely\r\n");
            }
            break;
        case 'd':
            processDebugCommand(str, len);
            break;
        case 'x':
            processRadioCommand(str, len);
            break;
        case 'v':
            ConsolePrint("SUNFLOWER OS V ");
            ConsolePrint(APP_VERSION_STR);
            ConsolePrint("\r\n");
            ConsolePrint("BUILD DATE: ");
            ConsolePrint(__DATE__);
            ConsolePrint("  :  ");
            ConsolePrint(__TIME__);
            ConsolePrint("\r\n\r\n");
            break;
        default:
            ConsolePrint("h : print help\r\n");
            ConsolePrint("x : radio commands\r\n");
            ConsolePrint("v : print version info\r\n");
            ConsolePrint("d : debug information\r\n");
            ConsolePrint("u : perform a fake firmware upgrade\r\n");
            ConsolePrint("r : reset commands\r\n");
            break;
    }
    
    ConsolePrint("> ");
}

void processRadioCommand(char* str, uint8_t len)
{
    radio_message_t* generic_msg;
    
    if(len >= 2)
    {
        switch(str[1])
        {
            case 'p':
            generic_msg = pvPortMalloc(sizeof(radio_message_t));
        
            // TODO: check we didn't run out of RAM (we should catch this in the 
            //       application Malloc failed handler, but just in case)
        
            generic_msg->ping.cmd = PING;
        
            SendToBroadcast((uint8_t*)generic_msg, sizeof(radio_message_t));
            return;
        }
    }
    
    ConsolePrint("Radio Commands\r\n");
    ConsolePrint("xp : send a radio ping packet\r\n");
}

void processDebugCommand(char* str, uint8_t len)
{
    if(len >= 2)
    {
        if(str[1] == 'd')
        {
            ToggleDebug();
            return;
        }
        else if(str[1] == 'i')
        {
            ToggleInfo();
            return;
        }
        else if(str[1] == 'w')
        {
            ToggleWarn();
            return;
        }
        else if(str[1] == 'e')
        {
            ToggleError();
            return;
        }
    }
    
    ConsolePrint("Debug commands\r\n");
    ConsolePrint("dd : toggle debug messages\r\n");
    ConsolePrint("di : toggle info messages\r\n");
    ConsolePrint("dw : toggle warn messages\r\n");
    ConsolePrint("de : toggle error messages\r\n");
}

uint8_t string_len(char* str)
{
    uint8_t i = 0;
    
    while(str[i] != '\0' && i < CONSOLE_MAX_MSG_SIZE)
    {
        i++;
    }
    
    return i;
}

void ConsolePrint(char* text)
{
    uint8_t i = string_len(text);
        
    while(!console_task_started)
    {
        osDelay(10);
    }
    
    // While the UART is not ready for TX, spin
    while(UART_ReadyTX(USARTn) != UART_OK)
    {
        osDelay(10);
    }
    
    UART_StartTX(USARTn, text, i);
}

void ConsoleGetChar(char c)
{
    // Silently drop chars if buffer is full: OS is dealing with the message
    if(rxBuffPos >= CONSOLE_MAX_MSG_SIZE)
    {
        return;
    }
    
    switch(c)
    {
        case '\r':
        case '\n':
            osMessagePut(uartRxMsgQ, (uint32_t)rxBuff, osWaitForever);
            break;
        
        default:
            rxBuff[rxBuffPos++] = c;
    }
    
    if(rxBuffPos >= CONSOLE_MAX_MSG_SIZE)
    {
        osMessagePut(uartRxMsgQ, (uint32_t)rxBuff, osWaitForever);
    }
    
    UART_CharTX(USARTn, c);
}
