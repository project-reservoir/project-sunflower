#include "fw_update.h"
#include "app_header.h"
#include "sunflower_app_header.h"
#include "crc.h"

bool Write_Dandelion_Word(uint32_t address, uint32_t word)
{
    if(address < DANDELION_IMAGE_SIZE)
    {
        FLASH_ProgramWord(address + DANDELION_IMAGE_START, word);
        return true;
    }
            
    return false;
}

bool Write_Sunflower_Word(uint32_t address, uint32_t word)
{
    if(address < SUNFLOWER_IMAGE_SIZE)
    {
        FLASH_ProgramWord(address + SUNFLOWER_IMAGE_START, word);
        return true;
    }
            
    return false;
}

bool Is_Dandelion_Image_Valid(void)
{       
    APP_HEADER* dandelion = ((APP_HEADER*)DANDELION_IMAGE_START);
    
    if(dandelion->image_size < DANDELION_IMAGE_SIZE && dandelion->image_size != 0 && dandelion->image_size != 0xFFFFFFFF) {
        return crc32(0x00000000, (uint8_t*)(DANDELION_IMAGE_START + 4), dandelion->image_size) == dandelion->crc32;
    }
    return false;
}

bool Is_Sunflower_Image_Valid(void)
{
    return false;
}

uint32_t Get_Dandelion_Version(void)
{
    APP_HEADER* dandelion = ((APP_HEADER*)DANDELION_IMAGE_START);
    
    return dandelion->version;
}

uint32_t Get_Sunflower_Version(void)
{
    // TODO: implement sunflower image storage
    return 0x00000000;
}

void Erase_Dandelion_Image(void)
{
    FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3);
}

void Erase_Sunflower_Image(void)
{
    FLASH_EraseSector(FLASH_Sector_9, VoltageRange_3);
    FLASH_EraseSector(FLASH_Sector_10, VoltageRange_3);
}
