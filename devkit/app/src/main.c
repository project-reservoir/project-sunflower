#include "hwctrl.h"
#include "stm32f4xx_hal.h"
#include "led_task.h"
#include "radio.h"
#include "cmsis_os.h"
#include "console.h"
#include "tcp_task.h"
#include "ethernetif.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"

/*Static IP ADDRESS*/
#define IP_ADDR0   10
#define IP_ADDR1   0
#define IP_ADDR2   0
#define IP_ADDR3   4
   
/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   10
#define GW_ADDR1   0
#define GW_ADDR2   0
#define GW_ADDR3   1  

static void Netif_Config(void);

/* network interface structure */
struct netif gnetif; 

/* Semaphore to signal Ethernet Link state update */
osSemaphoreId Netif_LinkSemaphore = NULL;

/* Ethernet link thread Argument */
struct link_str link_arg;

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
    __BKPT(0);
}

void vApplicationMallocFailedHook(void)
{
    HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN, GPIO_PIN_SET);
    __BKPT(0);
}

static void TCPStartThread()
{
  
  /* Create tcp_ip stack thread */
  tcpip_init(NULL, NULL);
  
  /* Initialize the LwIP stack */
  Netif_Config();
  
  /* Initialize tcp echo server */
  tcpecho_init();

  for( ;; )
  {
    /* Delete the Init Thread*/ 
    osThreadTerminate(NULL);
  }
}

int main(void)
{	
	xTaskHandle ledTaskHandle;
    xTaskHandle radioTaskHandle;
    xTaskHandle startTaskHandle;
    xTaskHandle consoleTaskHandle;
    
    // Initialize the ST Micro Board Support Library
    HAL_Init();
    
    // Configure the system clock
    SystemClock_Config();
    
    // Setup external ports on the MCU
    HwCtrl_Init();
    
    RadioTaskOSInit();
    ConsoleTaskOSInit();
    	
    // TODO: use CMSIS_OS functions for this to remove dependency on makeFreeRtosPriority()
    xTaskCreate(ConsoleTask,
                "ConsoleTask",
                configMINIMAL_STACK_SIZE,
                NULL,
                makeFreeRtosPriority(osPriorityNormal),
                &consoleTaskHandle);
    
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
    
    // Create an LED blink tasks	
    /*xTaskCreate(TCPStartThread,
                "TCPStartThread",
                configMINIMAL_STACK_SIZE,
                NULL,
                makeFreeRtosPriority(osPriorityNormal),
                &startTaskHandle);*/
    
    // Start scheduler
    vTaskStartScheduler();

    // We should never get here as control is now taken by the scheduler
    for(;;);
}

void Netif_Config(void)
{
  struct ip_addr ipaddr;
  struct ip_addr netmask;
  struct ip_addr gw;	
  
  /* IP address setting */
  IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
  
  /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
  struct ip_addr *netmask, struct ip_addr *gw,
  void *state, err_t (* init)(struct netif *netif),
  err_t (* input)(struct pbuf *p, struct netif *netif))
  
  Adds your network interface to the netif_list. Allocate a struct
  netif and pass a pointer to this structure as the first argument.
  Give pointers to cleared ip_addr structures when using DHCP,
  or fill them with sane numbers otherwise. The state pointer may be NULL.
  
  The init function pointer must point to a initialization function for
  your ethernet netif interface. The following code illustrates it's use.*/
  
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
  
  /*  Registers the default network interface. */
  netif_set_default(&gnetif);
  
  if (netif_is_link_up(&gnetif))
  {
    /* When the netif is fully configured this function must be called.*/
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }

  /* Set the link callback function, this function is called on change of link status*/
  netif_set_link_callback(&gnetif, ethernetif_update_config);
  
  /* create a binary semaphore used for informing ethernetif of frame reception */
  osSemaphoreDef(Netif_SEM);
  Netif_LinkSemaphore = osSemaphoreCreate(osSemaphore(Netif_SEM) , 1 );
  
  link_arg.netif = &gnetif;
  link_arg.semaphore = Netif_LinkSemaphore;
  
  /* Create the Ethernet link handler thread */
  osThreadDef(LinkThr, ethernetif_set_link, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  osThreadCreate(osThread(LinkThr), &link_arg);
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

  /* Infinite loop */
  while (1)
  {}
}
#endif
