#ifndef __LED_H
#define __LED_H

#include "main.h"

void LCD_LED_Init(void);
void ToggleLed4Task(void * pvParameters);
void BlinkLed3(void);

void AssertBlink(void);
void HardfaultBlink(void);

#endif // __LED_H
