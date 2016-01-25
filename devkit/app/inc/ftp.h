#ifndef __FTP_H
#define __FTP_H

#include "stm32f4xx.h"
#include <stdbool.h>
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"

bool FTP_Init(void);
bool FTP_DownloadFirmware(void);
bool FTP_Connect(ip_addr_t *addr, uint16_t port);
bool FTP_GetFwVersions(char* sunflower, char* dandelion, uint8_t max_len);
void FTP_Get(void);

#endif //__FTP_H
