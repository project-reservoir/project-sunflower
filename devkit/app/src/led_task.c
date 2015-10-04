#include "led_task.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "hwctrl.h"

void LedTaskHwInit(void)
{
    // Initialize LED3 and LED4
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* Enable the GPIO_LED Clock */
	
    LED4_GPIO_CLK_ENABLE();
    LED5_GPIO_CLK_ENABLE();    

	GPIO_InitStruct.Pin = LED4_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(LED4_GPIO_PORT, LED4_PIN, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = LED5_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(LED5_GPIO_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN, GPIO_PIN_RESET);
}

void LedBlinkTask(const void *argument)
{
	// Flash an LED on and off forever.
	while(1)
	{
		HAL_GPIO_WritePin(LED4_GPIO_PORT, LED4_PIN, GPIO_PIN_RESET);
        //HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
		osDelay(100);

		HAL_GPIO_WritePin(LED4_GPIO_PORT, LED4_PIN, GPIO_PIN_SET);
        //HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_RESET);
		osDelay(100);
	}
}
