/************************************************************************************
**	版权所有：Copyright (c) 2005 - 2010 ICRoute INC.
** 硬件说明：STM32f103vet6  8MHZ  内部时钟为72MHZ 
** 					 LD3320 有源晶振 12MHZ  不同的晶振请修改LDChip.h 中的定义值（＃define CLK_IN  12）
** 软件说明：并行读写寄存器方式，如采用其他方式即修改Reg_RW.c 文件即可！
** 修改者:  http://shop64790118.taobao.com/
** 时间：2011.10.15
** 
************************************************************************************/

#include  <stm32f10x_conf.h>
#include  <stm32f10x.h>

#include "LDchip.h"
#include "Reg_RW.h"

#include "delay.h"
#include  "gui_include.h"

/************************************************************************************/
//	nAsrStatus 用来在main主程序中表示程序运行的状态，不是LD3320芯片内部的状态寄存器
//	LD_ASR_NONE:		表示没有在作ASR识别
//	LD_ASR_RUNING：		表示LD3320正在作ASR识别中
//	LD_ASR_FOUNDOK:		表示一次识别流程结束后，有一个识别结果
//	LD_ASR_FOUNDZERO:	表示一次识别流程结束后，没有识别结果
//	LD_ASR_ERROR:		表示一次识别流程中LD3320芯片内部出现不正确的状态
/***********************************************************************************/
uint8 nAsrStatus=0;	

#define DEMO_SOUND_SIZE 1235

void LD3320_Init(void);

uint8 RunASR(void);
void ProcessInt0(void);
void LD3320_EXTI_Cfg(void);
void LD3320_NVIC_Cfg(void);

u8 ld3320_exti=0;	 //中断标志信号，为1是代表中断产生。以下采用查询方式。
/************************************************************************************/
//	这个示范程序是基于STC10L08XE编译的完整地，可以执行的程序
//	实现了从数组中播放的功能
//  
//  verygood_withHead.mp3(verygood_withoutHead)是一段MP3格式的声音文件，播放内容为英文单词"very good"
//	demosound.h 中定义了数组 bpDemoSound[]，
//  数组的内容就是 verygood_withHead.mp3(verygood_withoutHead)文件的内容
//  用户可以用16进制阅读器（比如 UltraEdit ）打开verygood_withHead.mp3文件和 bpDemoSound 数组相对照
//
//	关于两个MP3文件的差异：  
//	这两个MP3文件只差有没有ID3文件头，MP3的数据都是一样的，
//	ID3文件头传入LD芯片与否不影响播放
//  用Windows自带的MediaPlayer播放没有ID3头的vertygood_withoutHead.mp3 后，会自动加上ID3文件头
//  PlayDemoSound_Once/PlayDemoSound_Continue 函数就是把 bpDemoSound数组中的数据依次传入LD3320芯片进行播放
//
//  与LD3320芯片有关的函数功能，都在"开发手册.pdf"中有详细说明
//	请开发者对照"开发手册.pdf“阅读
//	
//	开发者在学习LD3320开始时，可以直接把在这个main函数拷贝到自己单片机中编译运行
//	
//	当然，用户要根据自己实际的单片机去修改 mcu_init ，以及对应的管脚连接的定义，中断定义
/************************************************************************************/

void  LD3320_main(void)
{

	nAsrStatus = LD_ASR_NONE;		//	初始状态：没有在作ASR
	while(1)
	{
 	switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
												break;
			case LD_ASR_NONE:

											nAsrStatus=LD_ASR_RUNING;
											if (RunASR()==0)	//	启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算
											{		
												nAsrStatus = LD_ASR_ERROR;
											}
											break;

			case LD_ASR_FOUNDOK:

											LD_GetResult();	//	一次ASR识别流程结束，去取ASR识别结果				
											nAsrStatus = LD_ASR_NONE;
											break;
			
			case LD_ASR_FOUNDZERO:
			default:
								nAsrStatus = LD_ASR_NONE;
								break;
			}
	
	  if(ld3320_exti !=0) {	/*采用查询方式进入中断处理*/

		 ld3320_exti =0;
		 ProcessInt0();		
		}

		  OSTimeDlyHMSM(0,0,0,50);
	
	
	}// while

}
/************************************************************************
功能描述： 
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
void LD3320_Init(void)
{
	LD3320_GPIO_config();	
	LD3320_EXTI_Cfg();
  LD3320_NVIC_Cfg();
	LD_reset();
}
/************************************************************************
功能描述： 
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
 void  LD3320_delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	for (j=0;j<5;j++)
	{
		for (g=0;g<uldata;g++)
		{
			delay_us(120);
		}
	}
}

/*********************************************************************
//为了消除编译时的 警告 *** WARNING L15: MULTIPLE CALL TO SEGMENT
//把在中断函数中需要调用的函数重新复制并命名
//消除警告 Warning L15，并且避免由于函数重入可能带来的隐藏Bug
*********************************************************************/
 void  LD3320_delay_2(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	for (j=0;j<5;j++)
	{
		for (g=0;g<uldata;g++)
		{
			delay_us(120);
		}
	}
}


/************************************************************************************/
//	RunASR()函数实现了一次完整的ASR语音识别流程
//	LD_AsrStart() 函数实现了ASR初始化
//	LD_AsrAddFixed() 函数实现了添加关键词语到LD3320芯片中
//	LD_AsrRun()	函数启动了一次ASR语音识别流程
//
//	任何一次ASR识别流程，都需要按照这个顺序，从初始化开始进行
/************************************************************************************/

uint8 RunASR(void)
{
	uint8 i=0;
	uint8 asrflag=0;
	for (i=0; i<5; i++)			//	防止由于硬件原因导致LD3320芯片工作不正常，所以一共尝试5次启动ASR识别流程
	{
		LD_AsrStart();			//初始化ASR
		LD3320_delay(100);
		if (LD_AsrAddFixed()==0)	//添加关键词语到LD3320芯片中
		{
			LD_reset();			//	LD3320芯片内部出现不正常，立即重启LD3320芯片
			LD3320_delay(50);			//	并从初始化开始重新ASR识别流程
			continue;
		}

		LD3320_delay(10);

		if (LD_AsrRun() == 0)
		{
			LD_reset();			//	LD3320芯片内部出现不正常，立即重启LD3320芯片
			LD3320_delay(50);			//	并从初始化开始重新ASR识别流程
			continue;
		}

		asrflag=1;
		break;					//	ASR流程启动成功，退出当前for循环。开始等待LD3320送出的中断信号
	}

	return asrflag;
}

/************************************************************************
功能描述： 		STM32 嵌套中断配置 
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
void LD3320_NVIC_Cfg(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
    
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}
/************************************************************************
功能描述： 	STM32 外部中断和 IO口配置，利用外部中断线1
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
void LD3320_EXTI_Cfg(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(EXTI_Line1);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_1);

}


/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!= RESET ) 
	{

			
			ld3320_exti=1;//进入中断标志 LD3320
						 
				EXTI_ClearFlag(EXTI_Line1);
				EXTI_ClearITPendingBit(EXTI_Line1);

		}
}
