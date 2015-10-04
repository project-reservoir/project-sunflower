#include "hwctrl.h"
#include "stm32f4xx_hal.h"
#include "led_task.h"
#include "radio.h"
#include "cmsis_os.h"
#include "stm32f4x7_eth.h"
#include "netconf.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tcpip.h"
#include "httpserver-socket.h"

#define DHCP_TASK_PRIO   ( tskIDLE_PRIORITY + 2 ) 

#pragma import(__use_no_semihosting)

unsigned portBASE_TYPE makeFreeRtosPriority (osPriority priority)
{
  unsigned portBASE_TYPE fpriority = tskIDLE_PRIORITY;
  
  if (priority != osPriorityError) {
    fpriority += (priority - osPriorityIdle);
  }
  
  return fpriority;
}

void vApplicationStackOverflowHook(void)
{
    HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN, GPIO_PIN_SET);
}

int main(void)
{	
	xTaskHandle ledTaskHandle;
    xTaskHandle radioTaskHandle;
    
    // Configure the system clock
    SystemClock_Config();
    
    // Setup external ports on the MCU
    HwCtrl_Init();
    
    // Initialize the ST Micro Board Support Library
    HAL_Init();
    
    RadioTaskOSInit();
    
    ETH_BSP_Config();
    
    /* Initilaize the LwIP stack */
    LwIP_Init();

    /* Initialize webserver demo */
    http_server_socket_init();
	
    /* Start DHCPClient */
    xTaskCreate(LwIP_DHCP_task, "DHCPClient", configMINIMAL_STACK_SIZE * 2, NULL,DHCP_TASK_PRIO, NULL);
    
    xTaskCreate(RadioTask,
                "RadioTask",
                configMINIMAL_STACK_SIZE,
                NULL,
                makeFreeRtosPriority(osPriorityNormal),
                &radioTaskHandle);
    
    // Create an LED blink tasks	
    xTaskCreate(LedBlinkTask,
                "LEDTask",
                configMINIMAL_STACK_SIZE,
                NULL,
                makeFreeRtosPriority(osPriorityNormal),
                &ledTaskHandle);
    
    // Start scheduler
    vTaskStartScheduler();

    // We should never get here as control is now taken by the scheduler
    for(;;);
}

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
