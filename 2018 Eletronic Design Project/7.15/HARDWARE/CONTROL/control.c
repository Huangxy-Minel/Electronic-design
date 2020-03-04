#include "control.h"

void control_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

  //GPIOE4,E5,E6��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
	GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_5);
	  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOEʱ��

  //GPIOE4,E5,E6��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
	GPIO_SetBits(GPIOG,GPIO_Pin_9 | GPIO_Pin_10);
}

void control_scan_1(uint16_t i)//���������ֵ���е�һ��λ�ж�
{
	if(i>3000)
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_4);
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		}
	else
		GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_5);
}

void control_scan_2(uint16_t i)//���������ֵ���еڶ���λ�ж�
{
	if(i>3000)
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_4);
			GPIO_SetBits(GPIOE,GPIO_Pin_5);
		}
	else
		GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_5);
}
