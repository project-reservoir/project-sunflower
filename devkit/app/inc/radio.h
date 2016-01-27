#ifndef _RADIO_H
#define _RADIO_H

#include "stm32f4xx.h"

#define SPIn                             SPI1
#define SPIn_CLK_ENABLE()                RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)
#define SPIn_SCK_GPIO_CLK_ENABLE()       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)
#define SPIn_MISO_GPIO_CLK_ENABLE()      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)
#define SPIn_MOSI_GPIO_CLK_ENABLE()      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)

/* Definition for SPIn Pins */
#define SPIn_NSS_PIN                     GPIO_Pin_15
#define SPIn_NSS_PIN_SOURCE              GPIO_PinSource15
#define SPIn_NSS_GPIO_PORT               GPIOA
#define SPIn_NSS_AF                      GPIO_AF_SPI1

#define SPIn_SCK_PIN                     GPIO_Pin_5
#define SPIn_SCK_PIN_SOURCE              GPIO_PinSource5
#define SPIn_SCK_GPIO_PORT               GPIOA
#define SPIn_SCK_AF                      GPIO_AF_SPI1

#define SPIn_MISO_PIN                    GPIO_Pin_4
#define SPIn_MISO_PIN_SOURCE             GPIO_PinSource4
#define SPIn_MISO_GPIO_PORT              GPIOB
#define SPIn_MISO_AF                     GPIO_AF_SPI1

#define SPIn_MOSI_PIN                    GPIO_Pin_5
#define SPIn_MOSI_PIN_SOURCE             GPIO_PinSource5
#define SPIn_MOSI_GPIO_PORT              GPIOB
#define SPIn_MOSI_AF                     GPIO_AF_SPI1

#define RADIO_NIRQ_PIN                   GPIO_Pin_1
#define RADIO_NIRQ_EXTI_PIN_SOURCE       EXTI_PinSource1
#define RADIO_NIRQ_GPIO_PORT             GPIOB
#define RADIO_NIRQ_EXTI_PORT_SOURCE      EXTI_PortSourceGPIOB
#define NIRQ_IRQn                        EXTI1_IRQn
#define RADIO_NIRQ_EXTI_LINE             EXTI_Line1


#define RADIO_SDL_PIN                    GPIO_Pin_0
#define RADIO_SDL_PIN_SOURCE             GPIO_PinSource0
#define RADIO_SDL_GPIO_PORT              GPIOB

#define SPIn_IRQn                        SPI1_IRQn

#define BUFFSIZE                         255
#define RADIO_MSG_QUEUE_SIZE             8
#define RADIO_MAX_PACKET_LENGTH          64

// Radio command definitions
#define CRC_ERROR                        (1 << 3)
#define PACKET_RX                        (1 << 4)
#define PACKET_SENT                      (1 << 5)

#define MAX_NETWORK_MEMBERS              1024

// Typedefs
typedef enum RadioTaskState_t {
    CONNECTED,
    CONNECTING,
    SEARCHING
} RadioTaskState;

typedef enum RadioTaskWakeupReason_t {
    RADIO_IRQ_DETECTED,
    RADIO_TX_NEEDED
} RadioTaskWakeupReason;

typedef struct NetworkInfo_t {
    uint32_t baseStationMac;
} NetworkInfo;

typedef struct RadioMessage_t {
    uint8_t* pData;
    uint8_t  size;
    uint32_t dest;
} RadioMessage;

typedef struct
{
    uint8_t   *Radio_ConfigurationArray;

    uint8_t   Radio_ChannelNumber;
    uint8_t   Radio_PacketLength;
    uint8_t   Radio_State_After_Power_Up;

    uint16_t  Radio_Delay_Cnt_After_Reset;

    uint8_t   Radio_CustomPayload[RADIO_MAX_PACKET_LENGTH];
} tRadioConfiguration;

typedef struct {
    uint32_t mac_address;
} NetworkMember_t;

// OS Task related functions
void RadioTaskHwInit(void);
void RadioTaskOSInit(void);
void RadioTask(void);
void RadioTaskHandleIRQ(void);
uint32_t RadioGetMACAddress(void);
void RadioPrintConnectedDevices(void);
uint32_t RadioGetDeviceMAC(uint16_t position);

// Public Radio API
void SendToDevice(uint8_t* data, uint8_t size, uint32_t mac);
void SendToBroadcast(uint8_t* data, uint8_t size);
void SignalRadioIRQ(void);

#endif // _RADIO_H
