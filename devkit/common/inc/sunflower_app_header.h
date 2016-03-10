#ifndef __SUNFLOWER_APP_HEADER_H
#define __SUNFLOWER_APP_HEADER_H

#include "stm32f4xx.h"
#include "sunflower_app_version_num.h"

#define SUNFLOWER_SRAM_START			0x20000000
#define SUNFLOWER_FLASH_START			0x08000000
#define SUNFLOWER_MAIN_APP_START		0x08004000

#define xstr(s) str(s)
#define str(s) #s

// App Version format:  0xAABBCCDD
//      AA = OS Major Revision
//      BB = OS Minor Revision
//      CC = HW ID (01 = DEVKIT, 02 = EVT1, 03 = EVT2)
//      DD = Build type (01 = DEBUG, 02 = PRODUCTION)

#define SUNFLOWER_APP_VERSION       0x01010101

typedef struct SUNFLOWER_APP_HEADER_T {
    uint32_t reserved[98]; // The header appears after the Interrupt Vector Table, which contains 98 entries
    uint32_t header_crc32;
	uint32_t body_crc32;
	uint32_t crc32_start_mark;
    uint32_t image_size;
	uint32_t version;
} SUNFLOWER_APP_HEADER;

#endif // __SUNFLOWER_APP_HEADER_H
