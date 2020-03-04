/************************************************************************************
**	版权所有：Copyright (c) 2005 - 2010 ICRoute INC.
** 硬件说明：STM32f103vet6  8MHZ  内部时钟为72MHZ 
** 					 LD3320 有源晶振 12MHZ  不同的晶振请修改LDChip.h 中的定义值（＃define CLK_IN  12）
** 软件说明：并行读写寄存器方式，如采用其他方式即修改Reg_RW.c 文件即可！
** 修改者:  http://shop64790118.taobao.com/
** 时间：2011.10.15
** 说明：本程序修改于 ICRoute公司 配套的源程序，版权归其所有。
************************************************************************************/

#include  <stm32f10x_conf.h>
#include  <stm32f10x.h>
#include "Reg_RW.h"

#include "delay.h"

////extern void _nop_(void);

/************************************************************************************/
//	主控MCU对于LD3320读写寄存器的实现有四种：
//	#define SOFT_PARA_PORT		//	软件模拟并行读写
//	#define HARD_PARA_PORT		//	硬件实现并行读写 （需要主控MCU有硬件的WR/RD端口）
//	#define SOFT_SPI_PORT		//	软件模拟SPI读写
//	#define HARD_SPI_PORT		//	硬件实现SPI读写	  （需要主控MCU有硬件SPI接口）
/************************************************************************************/
void LD3320_GPIO_OUTPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOA clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12 | 
															GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void LD3320_GPIO_INPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOA clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12 | 
															GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void LD3320_GPIO_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11 |GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	LD3320_GPIO_OUTPUT(); /*数据端口初始化为输出模式*/

}



	////	#define DELAY_NOP	_nop_();_nop_();_nop_();
		#define DELAY_NOP	delay_us(14)	//延时代替
////		sbit	LD_WR 	= P3^6;
////		sbit	LD_RD	= P3^7;
////		sbit	LD_CS	= P2^6;
////		sbit	LD_A0	= P2^0;

		void LD_WriteReg( unsigned char address, unsigned char dataout )
		{
		LD3320_GPIO_OUTPUT();
		////	P0 = address;
		GPIOB->ODR=( (u16) (address) )<<8;
			LD_A0_H();
			LD_CS_L();
			LD_WR_L();
			//DELAY_NOP;
		
			LD_WR_H();
			LD_CS_H();
			//DELAY_NOP;
		
		////	P0 = dataout;
		GPIOB->ODR= ( (u16) (dataout) ) <<8;
			LD_A0_L();
			LD_CS_L();
			LD_WR_L();
			//DELAY_NOP;
		
			LD_WR_H();
			LD_CS_H();
			//DELAY_NOP;
		}
		
		unsigned char LD_ReadReg( unsigned char address )
		{
			unsigned char datain;

			LD3320_GPIO_OUTPUT();
//// P0 = address;
			GPIOB->ODR= ( (u16) (address) ) <<8;
			LD_A0_H();
			LD_CS_L();
			LD_WR_L();
			//DELAY_NOP;
		
			LD_WR_H();
			LD_CS_H();
		//	DELAY_NOP;
		
			LD_A0_L();
			LD_CS_L();
			LD_RD_L();
			LD3320_GPIO_INPUT();
			//DELAY_NOP;

/////			datain = P0;
			datain=(u8)(( 0xFF00 & GPIOB->IDR) >>8);
			LD_RD_H();
			LD_CS_H();
			//DELAY_NOP;
		
			return datain;
		}





