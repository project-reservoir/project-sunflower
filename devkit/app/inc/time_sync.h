#ifndef __TIME_SYNC_H
#define __TIME_SYNC_H

#include "stm32f4xx.h"
#include <stdbool.h>
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"

void TimeSyncHwInit(void);

void TimeSyncInit(void);

void TimeSyncTask(void);

bool TimeSync(void);

uint32_t TimeSyncGet(void);

#endif // __TIME_SYNC_H
