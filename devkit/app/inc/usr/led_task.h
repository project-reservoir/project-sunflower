#ifndef _LED_TASK_H
#define _LED_TASK_H

#define LED4_PIN                         GPIO_PIN_12
#define LED4_GPIO_PORT                   GPIOD
#define LED4_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()  
#define LED4_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()  

#define LED3_PIN                         GPIO_PIN_13
#define LED3_GPIO_PORT                   GPIOD
#define LED3_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()  
#define LED3_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE() 

#define LED5_PIN                         GPIO_PIN_14
#define LED5_GPIO_PORT                   GPIOD
#define LED5_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()  
#define LED5_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()  

#define LED6_PIN                         GPIO_PIN_15
#define LED6_GPIO_PORT                   GPIOD
#define LED6_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()  
#define LED6_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE() 

void LedTaskHwInit(void);
void LedBlinkTask(const void *argument);

#endif // __LED_TASK_H
