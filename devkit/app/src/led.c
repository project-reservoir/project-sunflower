#include "led.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

#define CRUDE_1MS 16800  

/**
  * @brief  Initializes the STM324xG-EVAL's LCD and LEDs resources.
  * @param  None
  * @retval None
  */
void LCD_LED_Init(void)
{
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);     
    STM_EVAL_LEDInit(LED6); 
}

/**
  * @brief  Toggle Led4 task
  * @param  pvParameters not used
  * @retval None
  */
void ToggleLed4Task(void * pvParameters)
{  
    while(1)
    {
        /* toggle LED4 each 250ms */
        STM_EVAL_LEDToggle(LED4);
        vTaskDelay(250);
    }
}

void BlinkLed3(void)
{
    STM_EVAL_LEDOn(LED3);
    vTaskDelay(40);
    STM_EVAL_LEDOff(LED3);
}

// Called in the Assert handler: the OS may have failed so use crude loops
// This function does not return
void AssertBlink(void)
{
    STM_EVAL_LEDOff(LED5);
    
    while(1)
    {
        STM_EVAL_LEDOff(LED5);
        
        for(uint32_t i = 0; i < CRUDE_1MS * 500; i++)
        {
            __DMB();
        }
        
        STM_EVAL_LEDOn(LED5);
        
        for(uint32_t i = 0; i < CRUDE_1MS * 500; i++)
        {
            __DMB();
        }
    }
}

// Called in the Assert handler: the OS isn't running so use crude loops
// This function does not return
void HardfaultBlink(void)
{
    while(1)
    {
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        STM_EVAL_LEDOff(LED5);
        STM_EVAL_LEDOff(LED6);
    
        for(uint32_t i = 0; i < CRUDE_1MS * 500; i++)
        {
            __DMB();
        }
        
        STM_EVAL_LEDOn(LED3);
        STM_EVAL_LEDOn(LED4);
        STM_EVAL_LEDOn(LED5);
        STM_EVAL_LEDOn(LED6);
        
        for(uint32_t i = 0; i < CRUDE_1MS * 500; i++)
        {
            __DMB();
        }
    }
}
