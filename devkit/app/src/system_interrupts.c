#include "system_interrupts.h"
#include "cmsis_os.h"
#include "app_header.h"
#include "led_task.h"
#include "radio.h"
#include "console.h"
#include "uart.h"
#include "ethernetif.h"

volatile uint8_t sendRadioCmd = 0;

extern UART_HandleTypeDef UartHandle;

extern void __main(void);
extern osSemaphoreId Netif_LinkSemaphore;

void SysTick_Handler(void)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();
	}

	HAL_IncTick();
}

void EXTI0_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(KEY_BUTTON_PIN) != RESET)
    { 
        __HAL_GPIO_EXTI_CLEAR_IT(KEY_BUTTON_PIN);
        sendRadioCmd = 1;
    }
}

void EXTI1_IRQHandler(void)
{
    __HAL_GPIO_EXTI_CLEAR_IT(RADIO_NIRQ_PIN);        
    SignalRadioIRQ();
}

void ETH_IRQHandler(void)
{
  ETHERNET_IRQHandler();
}

void USARTx_Handler(void)
{
    //HAL_UART_IRQHandler(& UartHandle);
    
    
    // This code is here to ensure that the function isn't inlined
    if((USARTx->SR & USART_SR_RXNE) == USART_SR_RXNE)
    {
        ConsoleGetChar(USARTx->DR);
        //ConsoleGetChar((USART1->DR));
    }
    
    if((USARTx->SR & USART_SR_TC) == USART_SR_TC && (USARTx->CR1 & USART_CR1_TCIE) == USART_CR1_TCIE)
    {
        UART_ContinueTX(USARTx);
    }
    
    if((USARTx->SR & USART_SR_ORE) == USART_SR_ORE)
    {
        USARTx->SR = USARTx->SR & ~USART_SR_ORE;
    }
}
