/************************************************************************************
**	版权所有：Copyright (c) 2005 - 2010 ICRoute INC.
** 硬件说明：STM32f103vet6  8MHZ  内部时钟为72MHZ 
** 					 LD3320 有源晶振 12MHZ  不同的晶振请修改LDChip.h 中的定义值（＃define CLK_IN  12）
** 软件说明：并行读写寄存器方式，如采用其他方式即修改Reg_RW.c 文件即可！
** 修改者:  http://shop64790118.taobao.com/
** 时间：2011.10.15
** 说明：本程序修改于 ICRoute公司 配套的源程序，版权归其所有。
************************************************************************************/

// Reg_RW.h  读写LD3320芯片的寄存器，共有四种方法。
#ifndef REG_RW_H
#define REG_RW_H

// 以下定义必须只有一个有效
//#define SOFT_PARA_PORT	//	软件模拟并行读写
//#define HARD_PARA_PORT		//	硬件实现并行读写 （需要主控MCU有硬件的WR/RD端口）
//#define SOFT_SPI_PORT		//	软件模拟SPI读写
//#define HARD_SPI_PORT		//	硬件实现SPI读写	  （需要主控MCU有硬件SPI接口）

////sbit	LD_MODE	= P1^0;		//模式选择引脚，硬件模拟总线方式 必须拉低

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
函数名： LD_WriteReg
功能：写LD3320芯片的寄存器
参数：  address, 8位无符号整数，地址
		dataout，8位无符号整数，要写入的数据
返回值：无
****************************************************************/ 
void LD_WriteReg( unsigned char address, unsigned char dataout );

/****************************************************************
函数名： LD_ReadReg
功能：读LD3320芯片的寄存器
参数：  address, 8位无符号整数，地址
返回值：8位无符号整数，读取的结果
****************************************************************/ 
unsigned char LD_ReadReg( unsigned char address );

void LD3320_GPIO_config(void);


#endif
