/************************************************************************************
**	��Ȩ���У�Copyright (c) 2005 - 2010 ICRoute INC.
** Ӳ��˵����STM32f103vet6  8MHZ  �ڲ�ʱ��Ϊ72MHZ 
** 					 LD3320 ��Դ���� 12MHZ  ��ͬ�ľ������޸�LDChip.h �еĶ���ֵ����define CLK_IN  12��
** ���˵�������ж�д�Ĵ�����ʽ�������������ʽ���޸�Reg_RW.c �ļ����ɣ�
** �޸���:  http://shop64790118.taobao.com/
** ʱ�䣺2011.10.15
** ˵�����������޸��� ICRoute��˾ ���׵�Դ���򣬰�Ȩ�������С�
************************************************************************************/

#include  <stm32f10x_conf.h>
#include  <stm32f10x.h>
#include "Reg_RW.h"

#include "delay.h"

////extern void _nop_(void);

/************************************************************************************/
//	����MCU����LD3320��д�Ĵ�����ʵ�������֣�
//	#define SOFT_PARA_PORT		//	���ģ�Ⲣ�ж�д
//	#define HARD_PARA_PORT		//	Ӳ��ʵ�ֲ��ж�д ����Ҫ����MCU��Ӳ����WR/RD�˿ڣ�
//	#define SOFT_SPI_PORT		//	���ģ��SPI��д
//	#define HARD_SPI_PORT		//	Ӳ��ʵ��SPI��д	  ����Ҫ����MCU��Ӳ��SPI�ӿڣ�
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
	
	LD3320_GPIO_OUTPUT(); /*���ݶ˿ڳ�ʼ��Ϊ���ģʽ*/

}



	////	#define DELAY_NOP	_nop_();_nop_();_nop_();
		#define DELAY_NOP	delay_us(14)	//��ʱ����
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





