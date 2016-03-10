#include "crc.h"

// Compute and return the CRC32
// This CRC32 should match the zlib.crc32 python routine
uint32_t crc32(uint32_t crc, uint8_t *buf, uint32_t len)
{
    crc = ~crc;
    while (len--) {
        crc ^= *buf++;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
        crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
    }
    return ~crc;
}