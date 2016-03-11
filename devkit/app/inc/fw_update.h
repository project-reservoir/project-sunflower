#ifndef __FW_UPDATE_H
#define __FW_UPDATE_H

#include "stm32f4xx.h"
#include "stm32f4xx_flash.h"
#include "stdbool.h"
#include "sunflower_app_header.h"

// Sunflower image is kept in sectors 9-10 (256k max image size)
#define SUNFLOWER_IMAGE_START 0x080C0000
#define SUNFLOWER_IMAGE_SIZE  (256 * 1024)

// Dandelion image is kept in sector 11
#define DANDELION_IMAGE_START 0x080E0000
#define DANDELION_IMAGE_SIZE  (128 * 1024)


bool        Write_Dandelion_Word(uint32_t address, uint32_t word);
bool        Write_Sunflower_Word(uint32_t address, uint32_t word);
bool        Is_Dandelion_Image_Valid(void);
bool        Is_Sunflower_Image_Valid(bool main_region);
uint32_t    Get_Dandelion_Version(void);
uint32_t    Get_Sunflower_Version(void);
void        Erase_Dandelion_Image(void);
void        Erase_Sunflower_Image(void);
uint32_t crc32(uint32_t crc, uint8_t *buf, uint32_t len);

#endif // __FW_UPDATE_H
