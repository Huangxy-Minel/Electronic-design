/************************************************************************************
**	��Ȩ���У�Copyright (c) 2005 - 2010 ICRoute INC.
** Ӳ��˵����STM32f103vet6  8MHZ  �ڲ�ʱ��Ϊ72MHZ 
** 					 LD3320 ��Դ���� 12MHZ  ��ͬ�ľ������޸�LDChip.h �еĶ���ֵ����define CLK_IN  12��
** ���˵�������ж�д�Ĵ�����ʽ�������������ʽ���޸�Reg_RW.c �ļ����ɣ�
** �޸���:  http://shop64790118.taobao.com/
** ʱ�䣺2011.10.15
** ˵�����������޸��� ICRoute��˾ ���׵�Դ���򣬰�Ȩ�������С�
************************************************************************************/

// Reg_RW.h  ��дLD3320оƬ�ļĴ������������ַ�����
#ifndef REG_RW_H
#define REG_RW_H

// ���¶������ֻ��һ����Ч
//#define SOFT_PARA_PORT	//	���ģ�Ⲣ�ж�д
//#define HARD_PARA_PORT		//	Ӳ��ʵ�ֲ��ж�д ����Ҫ����MCU��Ӳ����WR/RD�˿ڣ�
//#define SOFT_SPI_PORT		//	���ģ��SPI��д
//#define HARD_SPI_PORT		//	Ӳ��ʵ��SPI��д	  ����Ҫ����MCU��Ӳ��SPI�ӿڣ�

////sbit	LD_MODE	= P1^0;		//ģʽѡ�����ţ�Ӳ��ģ�����߷�ʽ ��������

////		sbit	LD_WR 	= P3^6;
////		sbit	LD_RD	= P3^7;
////		sbit	LD_CS	= P2^6;
////		sbit	LD_A0	= P2^0;

#define LD_WR    GPIO_Pin_8  //PA8
#define LD_RD    GPIO_Pin_9  //PA9
#define LD_CS    GPIO_Pin_10  //PA10
#define LD_A0    GPIO_Pin_11  //PA11
#define LD_RST	 GPIO_Pin_12  //PA12


#define LD_WR_H() GPIOA->BSRR = LD_WR
#define LD_WR_L() GPIOA->BRR  = LD_WR

#define LD_RD_H() GPIOA->BSRR = LD_RD
#define LD_RD_L() GPIOA->BRR  = LD_RD

#define LD_CS_H() GPIOA->BSRR = LD_CS
#define LD_CS_L() GPIOA->BRR  = LD_CS

#define LD_A0_H() GPIOA->BSRR = LD_A0
#define LD_A0_L() GPIOA->BRR  = LD_A0

#define LD_RST_H() GPIOA->BSRR = LD_RST
#define LD_RST_L() GPIOA->BRR  = LD_RST

/****************************************************************
�������� LD_WriteReg
���ܣ�дLD3320оƬ�ļĴ���
������  address, 8λ�޷�����������ַ
		dataout��8λ�޷���������Ҫд�������
����ֵ����
****************************************************************/ 
void LD_WriteReg( unsigned char address, unsigned char dataout );

/****************************************************************
�������� LD_ReadReg
���ܣ���LD3320оƬ�ļĴ���
������  address, 8λ�޷�����������ַ
����ֵ��8λ�޷�����������ȡ�Ľ��
****************************************************************/ 
unsigned char LD_ReadReg( unsigned char address );

void LD3320_GPIO_config(void);


#endif
