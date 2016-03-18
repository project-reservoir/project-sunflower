#ifndef _CRC_H
#define _CRC_H

#include "stm32f4xx.h"

uint32_t crc32(uint32_t crc, uint8_t *buf, uint32_t len);

#endif //_CRC_H
