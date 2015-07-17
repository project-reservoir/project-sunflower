#ifndef _RADIO_H
#define _RADIO_H

#include "stm32f4xx_hal.h"

#define SPIx                             SPI1
#define SPIx_CLK_ENABLE()                __SPI1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __GPIOA_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE() 
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE() 

#define SPIx_FORCE_RESET()               __SPI1_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __SPI1_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_NSS_PIN                     GPIO_PIN_15
#define SPIx_NSS_GPIO_PORT               GPIOA
#define SPIx_NSS_AF                      GPIO_AF5_SPI1

#define SPIx_SCK_PIN                     GPIO_PIN_5
#define SPIx_SCK_GPIO_PORT               GPIOA
#define SPIx_SCK_AF                      GPIO_AF5_SPI1

#define SPIx_MISO_PIN                    GPIO_PIN_4
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MISO_AF                     GPIO_AF5_SPI1

#define SPIx_MOSI_PIN                    GPIO_PIN_5
#define SPIx_MOSI_GPIO_PORT              GPIOB
#define SPIx_MOSI_AF                     GPIO_AF5_SPI1

#define RADIO_NIRQ_PIN                   GPIO_PIN_1
#define RADIO_NIRQ_GPIO_PORT             GPIOB
#define NIRQ_IRQn                        EXTI1_IRQn

#define RADIO_SDL_PIN                    GPIO_PIN_0
#define RADIO_SDL_GPIO_PORT              GPIOB

#define KEY_BUTTON_PIN                   GPIO_PIN_0
#define KEY_BUTTON_GPIO_PORT             GPIOA
#define KEY_BUTTON_GPIO_CLK_ENABLE()     __GPIOA_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()    __GPIOA_CLK_DISABLE()
#define KEY_BUTTON_EXTI_LINE             GPIO_PIN_0
#define KEY_BUTTON_EXTI_IRQn             EXTI0_IRQn

#define SPIx_IRQn                        SPI1_IRQn
/* Size of buffer */
#define BUFFSIZE                         255

#define RADIO_MSG_QUEUE_SIZE             8

#define RADIO_MAX_PACKET_LENGTH          64u

// Radio command definitions
#define CRC_ERROR                        (1 << 3)
#define PACKET_RX                        (1 << 4)
#define PACKET_SENT                      (1 << 5)


// Typedefs
typedef enum RadioTaskState_t {
    CONNECTED,
    CONNECTING,
    SEARCHING
} RadioTaskState;

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

typedef enum RadioTaskWakeupReason_t {
    RADIO_IRQ_DETECTED,
    RADIO_TX_NEEDED
} RadioTaskWakeupReason;

// OS Task related functions
void RadioTaskHwInit(void);
void RadioTaskOSInit(void);
void RadioTask(void);
void RadioTaskHandleIRQ(void);

// Public Radio API
void SendToBaseStation(uint8_t* data, uint8_t size);
void SendToBroadcast(uint8_t* data, uint8_t size);
void SignalRadioIRQ(void);

#endif // _RADIO_H
