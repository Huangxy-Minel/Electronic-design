#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY0        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)  //KEY0����PC0
#define KEY1        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)  //KEY1����PC1
#define KEY2        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)  //KEY2����PC2
#define KEY3        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)  //KEY3����PC3
#define KEY4        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)  //KEY4����PC4
#define KEY5        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)  //KEY5����PC5

#define KEY0_PRES 	1
#define KEY1_PRES		2
#define KEY2_PRES		3
#define KEY3_PRES		4
#define KEY4_PRES		5
#define KEY5_PRES		6

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
