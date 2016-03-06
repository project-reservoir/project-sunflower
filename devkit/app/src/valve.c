#include "valve.h"

void InitValveHw(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_AHB1PeriphClockCmd(VALVE_0_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(VALVE_1_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(VALVE_2_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(VALVE_3_CLK, ENABLE);
    
    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Pin = VALVE_0_PIN;
    GPIO_Init(VALVE_0_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = VALVE_1_PIN;
    GPIO_Init(VALVE_1_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = VALVE_2_PIN;
    GPIO_Init(VALVE_2_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = VALVE_3_PIN;
    GPIO_Init(VALVE_3_PORT, &GPIO_InitStructure);
}

void OpenValve(uint8_t valve)
{
    
}

void CloseValve(uint8_t valve)
{
    
}