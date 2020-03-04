#include "control.h"

void control_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

  //GPIOE4,E5,E6初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_5);
	  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOE时钟

  //GPIOE4,E5,E6初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化
	GPIO_SetBits(GPIOG,GPIO_Pin_9 | GPIO_Pin_10);
}

void control_scan_1(uint16_t i)//传入基波峰值进行第一档位判断
{
	if(i>3000)
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_4);
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		}
	else
		GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_5);
}

void control_scan_2(uint16_t i)//传入基波峰值进行第二挡位判断
{
	if(i>3000)
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_4);
			GPIO_SetBits(GPIOE,GPIO_Pin_5);
		}
	else
		GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_5);
}
