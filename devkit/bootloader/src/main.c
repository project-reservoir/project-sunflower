#include "sunflower_app_header.h"
#include "fw_update.h"
#include "stm32f4xx.h"
#include "stm32f4xx_flash.h"

// DEFINES
#define ARM_THUMB_MODE 0x1

extern void launch(uint32_t stackPtr, uint32_t progCtr);

// GLOBAL VARIABLES
SUNFLOWER_APP_HEADER* main_app = (SUNFLOWER_APP_HEADER*)SUNFLOWER_MAIN_APP_START;
SUNFLOWER_APP_HEADER* backup_app = (SUNFLOWER_APP_HEADER*)SUNFLOWER_BACKUP_APP_START;

// LOCAL FUNCTION DECLARATIONS
void createIVT(SUNFLOWER_APP_HEADER* app);
void launchImage(SUNFLOWER_APP_HEADER* app);
void CopyBackupToMain(void);

// GLOBAL FUNCTIONS
int main(void)
{   
    // If the backup region is valid and the main app is not a debug app
    if(Is_Sunflower_Image_Valid(false))
    {
        // Check if the version is greater than the main app region
        // Or if the main app is invalid
        if((backup_app->version > main_app->version) || !Is_Sunflower_Image_Valid(true))
        {
            CopyBackupToMain();
        }
    }
    
    launchImage(main_app);
    for(;;);
}

void launchImage(SUNFLOWER_APP_HEADER* app)
{
    uint32_t stackPtr = (uint32_t)(*((uint32_t*)app));
    uint32_t progCtr  = (uint32_t)(*((uint32_t*)((uint32_t)app + 4))) | ARM_THUMB_MODE;
    
    //Set NVIC to point to the new IVT
    SCB->VTOR = (uint32_t)app;
    
    __DMB();
    
    launch(stackPtr, progCtr);
}

void CopyBackupToMain(void)
{
    // Erase the main application
    FLASH_Unlock();
    FLASH_EraseSector(FLASH_Sector_5, VoltageRange_1);
    FLASH_EraseSector(FLASH_Sector_6, VoltageRange_1);
    
    for(uint32_t i = 0; i < backup_app->image_size; i += 4)
    {
        FLASH_ProgramWord(i + SUNFLOWER_MAIN_APP_START, *((uint32_t*)(SUNFLOWER_BACKUP_APP_START + i)));
    }
    
    FLASH_Lock();
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
