#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/11/27
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//��ʼ��PB0,PB1Ϊ���.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOC_CLK_ENABLE();			//����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9; //PB0,1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);	//PB1��0
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);	//PB1��1 
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);	//PB1��1 
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET);	//PB1��1 
}

