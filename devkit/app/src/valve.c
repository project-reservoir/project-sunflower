#include "valve.h"

void InitValveHw(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_AHB1PeriphClockCmd(VALVE_0_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(VALVE_1_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(VALVE_2_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(VALVE_3_CLK, ENABLE);
    
    CloseValve(0);
    CloseValve(1);
    CloseValve(2);
    CloseValve(3);
    
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

void CloseValve(uint8_t valve)
{
    switch(valve)
    {
        case 0:
            GPIO_SetBits(VALVE_0_PORT, VALVE_0_PIN);
            break;
        
        case 1:
            GPIO_SetBits(VALVE_1_PORT, VALVE_1_PIN);
            break;
        
        case 2:
            GPIO_SetBits(VALVE_2_PORT, VALVE_2_PIN);
            break;
        
        case 3:
            GPIO_SetBits(VALVE_3_PORT, VALVE_3_PIN);
            break;
    }
}

void OpenValve(uint8_t valve)
{
    switch(valve)
    {
        case 0:
            GPIO_ResetBits(VALVE_0_PORT, VALVE_0_PIN);
            break;
        
        case 1:
            GPIO_ResetBits(VALVE_1_PORT, VALVE_1_PIN);
            break;
        
        case 2:
            GPIO_ResetBits(VALVE_2_PORT, VALVE_2_PIN);
            break;
        
        case 3:
            GPIO_ResetBits(VALVE_3_PORT, VALVE_3_PIN);
            break;
    }
}