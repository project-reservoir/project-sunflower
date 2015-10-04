#include "system_interrupts.h"
#include "cmsis_os.h"
#include "app_header.h"
#include "led_task.h"
#include "radio.h"

volatile uint8_t sendRadioCmd = 0;

extern void __main(void);
extern void xPortSysTickHandler();

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