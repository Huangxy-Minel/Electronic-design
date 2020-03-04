/*-----------------------------------------------
  ���ƣ�AD9854��������
  ��д��Lu
  ���ڣ�2014.3
  �޸ģ���
  ���ݣ�
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

//#define PDATA	GPIOA_Pin7	// ��������
//#define ADDR	P0		// ��ַѡ��ȡ��6λ
//sbit OSK    = P4^6;	//	
//sbit FSK_D  = P4^5;	//	
//sbit RDB	= P1^2;	// ������
//sbit WRB	= P1^1; // д����
//sbit UDCLK	= P1^0;	// ���ݸ���ʱ��
//sbit RESET  = P1^3; // ����λ

//extern unsigned char DATA[6];      ////  ����������������

void Init_9854(void);  //INIT 9854 
void Write_9854(unsigned char address,unsigned char DATA);//д����
void Write_frequence(unsigned long x);										//дƵ��
void Write_Amplitude(unsigned char Channel,unsigned int Amplitude);	//д����


					
					
#endif
					
					
					








