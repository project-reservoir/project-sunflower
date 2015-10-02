#include "app_header.h"
#include "stm32f4xx.h"

// DEFINES
#define ARM_THUMB_MODE 0x1

extern void launch(uint32_t stackPtr, uint32_t progCtr);

// GLOBAL VARIABLES
APP_HEADER* main_app = (APP_HEADER*)MAIN_APP_START;

// LOCAL FUNCTION DECLARATIONS
void createIVT(APP_HEADER* app);
void launchImage(APP_HEADER* app);

// GLOBAL FUNCTIONS
int main(void)
{    
    launchImage(main_app);

    for(;;);
}

void launchImage(APP_HEADER* app)
{
    uint32_t stackPtr = (uint32_t)(*((uint32_t*)app));
    uint32_t progCtr  = (uint32_t)(*((uint32_t*)((uint32_t)app + 4))) | ARM_THUMB_MODE;
    
    //Set NVIC to point to the new IVT
    SCB->VTOR = (uint32_t)app;
    
    __DMB();
    
    launch(stackPtr, progCtr);
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
