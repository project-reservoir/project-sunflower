#ifndef __CONSOLE_H
#define __CONSOLE_H

#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD 
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD 
#define USARTx_RX_AF                     GPIO_AF7_USART3

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART3_IRQn
#define USARTx_Handler                   USART3_IRQHandler

#define CONSOLE_MSG_Q_SIZE               8
#define CONSOLE_MAX_MSG_SIZE             64

void ConsoleTaskHwInit(void);
void ConsoleTaskOSInit(void);
void ConsolePrint(char* text);
void ConsoleTask(void);
void ConsoleGetChar(char c);

#endif //__CONSOLE_H
