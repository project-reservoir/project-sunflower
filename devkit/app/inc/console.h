#ifndef __CONSOLE_H
#define __CONSOLE_H

#define USARTn                           USART3
#define USARTn_CLK_ENABLE()              RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE)
#define USARTn_RX_GPIO_CLK_ENABLE()      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define USARTn_TX_GPIO_CLK_ENABLE()      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)

/* Definition for USARTx Pins */
#define USARTn_TX_PIN                    GPIO_Pin_8
#define USARTn_TX_PIN_SOURCE             GPIO_PinSource8
#define USARTn_TX_GPIO_PORT              GPIOD 
#define USARTn_TX_AF                     GPIO_AF_USART3

#define USARTn_RX_PIN                    GPIO_Pin_9
#define USARTn_RX_PIN_SOURCE             GPIO_PinSource9
#define USARTn_RX_GPIO_PORT              GPIOD 
#define USARTn_RX_AF                     GPIO_AF_USART3

/* Definition for USARTx's NVIC */
#define USARTn_IRQn                      USART3_IRQn
#define USARTn_Handler                   USART3_IRQHandler

#define CONSOLE_MSG_Q_SIZE               8
#define CONSOLE_MAX_MSG_SIZE             64

void ConsoleTaskHwInit(void);
void ConsoleTaskOSInit(void);
void ConsolePrint(char* text);
void ConsoleTask(void);
void ConsoleGetChar(char c);

#endif //__CONSOLE_H
