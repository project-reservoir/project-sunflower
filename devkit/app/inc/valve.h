#ifndef _VALVE_H
#define _VALVE_H

#include "stm32f4xx.h"


#define VALVE_0_PIN     GPIO_Pin_0
#define VALVE_0_PORT    GPIOD
#define VALVE_0_CLK     RCC_AHB1Periph_GPIOD

#define VALVE_1_PIN     GPIO_Pin_2
#define VALVE_1_PORT    GPIOD
#define VALVE_1_CLK     RCC_AHB1Periph_GPIOD

#define VALVE_2_PIN     GPIO_Pin_4
#define VALVE_2_PORT    GPIOD
#define VALVE_2_CLK     RCC_AHB1Periph_GPIOD

#define VALVE_3_PIN     GPIO_Pin_6
#define VALVE_3_PORT    GPIOD
#define VALVE_3_CLK     RCC_AHB1Periph_GPIOD

void InitValveHw(void);
void OpenValve(uint8_t valve);
void CloseValve(uint8_t valve);

#endif //_VALVE_H