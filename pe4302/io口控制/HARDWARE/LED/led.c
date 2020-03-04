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
    __HAL_RCC_GPIOF_CLK_ENABLE();			//����GPIOBʱ��
	  __HAL_RCC_GPIOE_CLK_ENABLE();			//����GPIOBʱ��
	  __HAL_RCC_GPIOI_CLK_ENABLE();			//����GPIOBʱ��
	  __HAL_RCC_GPIOC_CLK_ENABLE();			//����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4; //PB0,1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);     //��ʼ��GPIOB.0��GPIOB.1	
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_SET);	//PB1��0
	
    GPIO_Initure.Pin=GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11; //PB0,1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //��ʼ��GPIOB.0��GPIOB.1
    HAL_GPIO_WritePin(GPIOI,GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11,GPIO_PIN_SET);	//PB1��0
	
    GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6; //PB0,1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);     //��ʼ��GPIOB.0��GPIOB.1
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_SET);	//PB1��0
		
    GPIO_Initure.Pin=GPIO_PIN_13; //PB0,1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);     //��ʼ��GPIOB.0��GPIOB.1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);	//PB1��0
}

