#ifndef __HWCTRL_H
#define __HWCTRL_H

#include "stm32f4xx_hal.h"

// DEFINES
#define LED4_PIN                         GPIO_PIN_12
#define LED4_GPIO_PORT                   GPIOD
#define LED4_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()  
#define LED4_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()  

#define LED3_PIN                         GPIO_PIN_13
#define LED3_GPIO_PORT                   GPIOD
#define LED3_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()  
#define LED3_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()  

// GLOBAL FUNCTIONS
void SystemClock_Config(void);
void HwCtrl_Init(void);
void HwCtrl_Led_Control(void);

#endif  // __HWCTRL_H
