/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; Portions COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
 /**
  ******************************************************************************
  * <h2><center>&copy; Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.</center></h2>
  * @file    main.c
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-December-2012
  * @brief   Main program body     
  *          Modified to support the STM32F4DISCOVERY, STM32F4DIS-BB and
  *          STM32F4DIS-LCD modules. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
  * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
  * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  */ 

#include "stm32f4x7_eth.h"
#include "netconf.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tcpip.h"
#include "cmsis_os.h"
#include "console.h"
#include "radio.h"
#include "time_sync.h"
#include "led.h"
#include "debug.h"
#include "tcpecho.h"
#include "valve.h"
#include "sunflower_app_header.h"

/*--------------- LCD Messages ---------------*/
#define MESSAGE1   "     STM32F4x7      "
#define MESSAGE2   "  STM32F-4 Series   "
#define MESSAGE3   " UDP/TCP EchoServer "
#define MESSAGE4   "                    "

/*--------------- Tasks Priority -------------*/
#define DHCP_TASK_PRIO      osPriorityNormal      
#define LED_TASK_PRIO       osPriorityLow
#define TIME_SYNC_TASK_PRIO osPriorityLow
#define CONSOLE_TASK_PRIO   osPriorityNormal
#define RADIO_TASK_PRIO     osPriorityHigh

extern struct netif xnetif;
 
extern void tcpecho_init(void);
extern void udpecho_init(void);

int main(void)
{
    // Needed for FreeRTOS (only use pre-emption priority values)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /*!< At this stage the microcontroller clock setting is already configured to 
       144 MHz, this is done through SystemInit() function which is called from
       startup file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */
    
    /*Initialize LCD and Leds */ 
    LCD_LED_Init();

    /* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
    ETH_BSP_Config();
    
    InitValveHw();
    
    ConsoleTaskHwInit();
    ConsoleTaskOSInit();
    
    RadioTaskHwInit();
    RadioTaskOSInit();
    tcpecho_os_init();
    
    //TimeSyncHwInit();
    //TimeSyncInit();
    
    /* Initilaize the LwIP stack */
    LwIP_Init();

    /* Initialize tcp echo server */
    tcpecho_init();

#ifdef USE_DHCP
    /* Start DHCPClient */
    osThreadDef(DHCP_Thread, LwIP_DHCP_task, DHCP_TASK_PRIO, 1, configMINIMAL_STACK_SIZE * 2);
    osThreadCreate(osThread(DHCP_Thread), NULL);
#endif

    /* Start toogleLed4 task : Toggle LED4  every 250ms */
    osThreadDef(LED_Thread, (os_pthread)ToggleLed4Task, LED_TASK_PRIO, 1, configMINIMAL_STACK_SIZE);
    osThreadCreate(osThread(LED_Thread), NULL);
    
    osThreadDef(Console_Thead, (os_pthread)ConsoleTask, CONSOLE_TASK_PRIO, 1, configMINIMAL_STACK_SIZE);
    osThreadCreate(osThread(Console_Thead), NULL);
    
    osThreadDef(Radio_Thead, (os_pthread)RadioTask, RADIO_TASK_PRIO, 1, configMINIMAL_STACK_SIZE * 2);
    osThreadCreate(osThread(Radio_Thead), NULL);
    
    //osThreadDef(Time_Sync_Thread, (os_pthread)TimeSyncTask, TIME_SYNC_TASK_PRIO, 1, configMINIMAL_STACK_SIZE);
    //osThreadCreate(osThread(Time_Sync_Thread), NULL);
    
    osThreadDef(Unix_Time_Thread, (os_pthread)unix_time_thread, LED_TASK_PRIO, 1, configMINIMAL_STACK_SIZE);
    osThreadCreate(osThread(Unix_Time_Thread), NULL);

    /* Start scheduler */
    vTaskStartScheduler();

    /* We should never get here as control is now taken by the scheduler */
    for( ;; );
}

void vApplicationStackOverflowHook(void)
{
    //TODO: fix 
    //HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN, GPIO_PIN_SET);
    //__BKPT(0);
    ERR("STACK OVERFLOW HOOK! HALTING SYSTEM\r\n");
    while(1);
}

void vApplicationMallocFailedHook(void)
{
    //TODO: fix 
    //HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN, GPIO_PIN_SET);
    //__BKPT(0);
    ERR("MALLOC FAILED HOOK! HALTING SYSTEM\r\n");
    while(1);
}

#ifdef  USE_FULL_ASSERT

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
    
    ERR("ASSERT FAILED in %s at line %d", (char*)file, line);
    
    AssertBlink();
    
    /* Infinite loop */
    while (1)
    {}
}
#endif


/*********** Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE****/
