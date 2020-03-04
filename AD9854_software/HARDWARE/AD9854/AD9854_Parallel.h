/*-----------------------------------------------
  名称：AD9854并口驱动
  编写：Lu
  日期：2014.3
  修改：无
  内容：
------------------------------------------------*/
#ifndef __AD9854_PARALLEL_H__
#define __AD9854_PARALLEL_H__
#include "stm32f10x.h"

#define uchar unsigned char
#define uint  unsigned int		 




#define OSK(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_15)

#define FSK_D(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define RDB(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_13)
					
#define WRB(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_12)
				

#define UDCLK(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_15)
				

#define RESET(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_0)

//#define PDATA	GPIOA_Pin7	// 并行数据
//#define ADDR	P0		// 地址选择，取低6位
//sbit OSK    = P4^6;	//	
//sbit FSK_D  = P4^5;	//	
//sbit RDB	= P1^2;	// 读控制
//sbit WRB	= P1^1; // 写控制
//sbit UDCLK	= P1^0;	// 数据更新时钟
//sbit RESET  = P1^3; // 主复位

//extern unsigned char DATA[6];      ////  函数不带参数传输

void Init_9854(void);  //INIT 9854 
void Write_9854(unsigned char address,unsigned char DATA);//写数据
void Write_frequence(unsigned long x);										//写频率
void Write_Amplitude(unsigned char Channel,unsigned int Amplitude);	//写幅度


					
					
#endif
					
					
					








