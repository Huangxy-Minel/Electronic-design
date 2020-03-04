#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/6/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//LED�˿ڶ���
#define LED0(n)		(n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET))
#define LED0_Toggle (HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6))

#define LED1(n)		(n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET))
#define LED1_Toggle (HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7))

#define LED2(n)		(n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET))
#define LED2_Toggle (HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8))

#define LED3(n)		(n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET))
#define LED3_Toggle (HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9))

#define LED4(n)		(n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET))
#define LED4_Toggle (HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10))

void LED_Init(void);
#endif
