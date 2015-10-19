#include "uart.h"

#define UART_ENABLE(Instance)                   Instance->CR1 |= USART_CR1_UE
#define UART_DISABLE(Instance)                  Instance->CR1 &= ~USART_CR1_UE

char* uartTxBuff = NULL;
uint8_t txSize = 0;
uint8_t txPos = 0;

void UART_CharTX(USART_TypeDef* uart, char c)
{
    uart->DR = c;
}

UART_Status UART_ReadyTX(USART_TypeDef* uart)
{
    if(uartTxBuff != NULL || txSize != 0)
    {
        return UART_NOT_READY;
    }
    
    return UART_OK;
}

UART_Status UART_StartRX(USART_TypeDef* uart)
{    
    // Enable USART receive mode
    uart->CR1 |= USART_CR1_RE;
    
    // Enable RX interrupts
    uart->CR1 |= USART_CR1_RXNEIE;
    
    return UART_OK;
}

UART_Status UART_StartTX(USART_TypeDef* uart, char* buff, uint8_t size)
{
    uartTxBuff = buff;
    txSize = size;
    txPos = 0;
    
    UART_ContinueTX(uart);
    
    // Enable TX interrupts
    uart->CR1 |= USART_CR1_TCIE;
    
    return UART_OK;
}

void UART_ContinueTX(USART_TypeDef* uart)
{
    uint32_t ticks = 0;
    
    while((uart->SR & USART_SR_TXE) != USART_SR_TXE && ticks < UART_TIMEOUT_TICKS)
    {
        ticks++;
    }
    
    if(uartTxBuff == NULL || txSize == 0 || txPos >= txSize)
    {
        return;
    }
    
    uart->DR = (uartTxBuff[txPos++] & (uint8_t)0xFF);
    
    while((uart->SR & USART_SR_TC) != USART_SR_TC && ticks < UART_TIMEOUT_TICKS)
    {
        ticks++;
    }
    
    // Finished transmitting
    if(txPos >= txSize)
    {
        txPos = 0;
        txSize = 0;
        uartTxBuff = NULL;
        
        // Disable TX interrupts
        uart->CR1 &= (~USART_CR1_TCIE);
    }
}
