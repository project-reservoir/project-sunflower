#ifndef _VALVE_H
#define _VALVE_H

#include "stm32f4xx.h"


#define VALVE_0_PIN     GPIO_Pin_2
#define VALVE_0_PORT    GPIOC
#define VALVE_0_CLK     RCC_AHB1Periph_GPIOC

#define VALVE_1_PIN     GPIO_Pin_3
#define VALVE_1_PORT    GPIOC
#define VALVE_1_CLK     RCC_AHB1Periph_GPIOC

#define VALVE_2_PIN     GPIO_Pin_10
#define VALVE_2_PORT    GPIOB
#define VALVE_2_CLK     RCC_AHB1Periph_GPIOB

#define VALVE_3_PIN     GPIO_Pin_14
#define VALVE_3_PORT    GPIOB
#define VALVE_3_CLK     RCC_AHB1Periph_GPIOB

void InitValveHw(void);
void OpenValve(uint8_t valve);
void CloseValve(uint8_t valve);

#endif //_VALVE_H