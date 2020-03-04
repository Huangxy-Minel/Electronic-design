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

#include "LDChip.h"
#include "Reg_RW.h"

#include  "gui_include.h"


uint8 nLD_Mode = LD_MODE_IDLE;		//	用来记录当前是在进行ASR识别还是在播放MP3

uint8 ucRegVal;
uint8 ucHighInt;
uint8 ucLowInt;

extern uint8  nAsrStatus;

void ProcessInt0(void);

/************************************************************************
功能描述： 芯片硬件初始化
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
void LD_reset(void)
{
	LD_RST_H();
	LD3320_delay(10);
	LD_RST_L();
LD3320_delay(10);
	LD_RST_H();
	LD3320_delay(10);
	LD_CS_L();
	LD3320_delay(10);
	LD_CS_H();
	LD3320_delay(10);
}
/************************************************************************
功能描述： 初始化命令		 软初始化
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
void LD_Init_Common(void)
{

	LD_ReadReg(0x06);  
	LD_WriteReg(0x17, 0x35); 
	LD3320_delay(10);
	LD_ReadReg(0x06);  

	LD_WriteReg(0x89, 0x03);  
	LD3320_delay(5);
	LD_WriteReg(0xCF, 0x43);   
	LD3320_delay(5);
	LD_WriteReg(0xCB, 0x02);
	
	/*PLL setting*/
	LD_WriteReg(0x11, LD_PLL_11);       
	if (nLD_Mode == LD_MODE_MP3)
	{
		LD_WriteReg(0x1E, 0x00); 
		LD_WriteReg(0x19, LD_PLL_MP3_19);   
		LD_WriteReg(0x1B, LD_PLL_MP3_1B);   
		LD_WriteReg(0x1D, LD_PLL_MP3_1D);
	}
	else
	{
		LD_WriteReg(0x1E,0x00);
		LD_WriteReg(0x19, LD_PLL_ASR_19); 
		LD_WriteReg(0x1B, LD_PLL_ASR_1B);		
	    LD_WriteReg(0x1D, LD_PLL_ASR_1D);
	}
	LD3320_delay(10);
	
	LD_WriteReg(0xCD, 0x04);
	LD_WriteReg(0x17, 0x4c); 
	LD3320_delay(5);
	LD_WriteReg(0xB9, 0x00);
	LD_WriteReg(0xCF, 0x4F); 
	LD_WriteReg(0x6F, 0xFF); 
}


/************************************************************************
功能描述： 	初始化ASR
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/	
void LD_Init_ASR(void)
{
	nLD_Mode=LD_MODE_ASR_RUN;
	LD_Init_Common();

	LD_WriteReg(0xBD, 0x00);
		GUI_DispDecAt(LD_ReadReg(0xBD),300,20,3);	//text................................
	LD_WriteReg(0x17, 0x48);
	
	LD3320_delay( 10 );

	LD_WriteReg(0x3C, 0x80);    
		GUI_DispDecAt(LD_ReadReg(0x3C),300,40,3);	//1 text................................
	LD_WriteReg(0x3E, 0x07);
		GUI_DispDecAt(LD_ReadReg(0x3e),300,60,3);	//text................................
	LD_WriteReg(0x38, 0xff);    
		GUI_DispDecAt(LD_ReadReg(0x38),300,80,3);	//text................................
	LD_WriteReg(0x3A, 0x07);
		GUI_DispDecAt(LD_ReadReg(0x3a),300,100,3);	//text................................
	LD_WriteReg(0x40, 0); 
		GUI_DispDecAt(LD_ReadReg(0x40),300,120,3);	//text................................         
	LD_WriteReg(0x42, 8);
		GUI_DispDecAt(LD_ReadReg(0x42),300,140,3);	//text................................
	LD_WriteReg(0x44, 0);    
		GUI_DispDecAt(LD_ReadReg(0x44),300,160,3);	//text................................
	LD_WriteReg(0x46, 8); 
		GUI_DispDecAt(LD_ReadReg(0x46),300,180,3);	//text................................
	LD3320_delay( 1 );
}

/************************************************************************
功能描述： 	识别处理函数 ，可以利用查询方式，或中断方式进行调用
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
void ProcessInt0(void)
{
	uint8 nAsrResCount=0;

	ucRegVal = LD_ReadReg(0x2B);

	if(nLD_Mode == LD_MODE_ASR_RUN)
	{	
			//GUI_DispDecAt(2,20,70,5);	//text................................
			// 语音识别产生的中断
			// （有声音输入，不论识别成功或失败都有中断）
			LD_WriteReg(0x29,0) ;
			LD_WriteReg(0x02,0) ;
//	
			GUI_DispDecAt(ucRegVal,200,100,3);
			GUI_DispDecAt(LD_ReadReg(0xb2),200,120,3);
			GUI_DispDecAt(LD_ReadReg(0xbf),200,140,3);
	
			if((ucRegVal & 0x10) && LD_ReadReg(0xb2)==0x21 && LD_ReadReg(0xbf)==0x35)		
				{	 
						GUI_DispDecAt(3,20,90,5); 	//text................................
						nAsrResCount = LD_ReadReg(0xba);
			
						if(nAsrResCount>0 && nAsrResCount<=4) 
						{
							nAsrStatus=LD_ASR_FOUNDOK; 				
						}
						else
					    {
							nAsrStatus=LD_ASR_FOUNDZERO;
							}	
				}
	
			else
				{	GUI_DispDecAt(4,20,100,5);		//text................................
					nAsrStatus=LD_ASR_FOUNDZERO;	//执行没有识别
				}

			LD_WriteReg(0x2b, 0);
    	LD_WriteReg(0x1C,0);	 //ADC开关 设为不可用
	}
	
	// 声音播放产生的中断，有三种：
	// A. 声音数据已全部播放完。
	// B. 声音数据已发送完毕。
	// C. 声音数据暂时将要用完，需要放入新的数据。
		
	ucHighInt = LD_ReadReg(0x29); 
	ucLowInt=LD_ReadReg(0x02); 

		GUI_DispDecAt(ucHighInt,20,160,4);
		GUI_DispDecAt(ucLowInt,20,180,4);

	LD_WriteReg(0x29,0) ;
	LD_WriteReg(0x02,0) ;	

   if(LD_ReadReg(0xBA)&CAUSE_MP3_SONG_END)
    {
	// A. 声音数据已全部播放完。

		LD_WriteReg(0x2B, 0);
    LD_WriteReg(0xBA, 0);	
		LD_WriteReg(0xBC,0x0);	

		LD_WriteReg(0x08,1);
		LD3320_delay_2(5);
    LD_WriteReg(0x08,0);
		LD_WriteReg(0x33, 0);

		return ;
     }
		 else 
				{
				// B. 声音数据已发送完毕。
			
					LD_WriteReg(0xBC, 0x01);
					LD_WriteReg(0x29, 0x10);			
					return;	
				}
	
	LD_WriteReg(0x29,ucHighInt); 
	LD_WriteReg(0x02,ucLowInt) ;

	LD3320_delay_2(1);

}
/************************************************************************
功能描述： 检测 ASR 是否忙状态， 返回1为空闲状态
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
uint8 LD_Check_ASRBusyFlag_b2(void)
{
	uint8 j;
	uint8 flag = 0;
	for (j=0; j<10; j++)
	{
		if (LD_ReadReg(0xb2) == 0x21)
		{
			flag = 1;
			break;
		}
		LD3320_delay(10);		
	}
	return flag;
}

void LD_AsrStart()
{
	LD_Init_ASR();
}
/************************************************************************
功能描述： 
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
// Return 1: success.
uint8 LD_AsrRun(void)
{
	LD_WriteReg(0x35, MIC_VOL);
	LD_WriteReg(0x1C, 0x09);
	LD_WriteReg(0xBD, 0x20);
	LD_WriteReg(0x08, 0x01);
	LD3320_delay( 1 );
	LD_WriteReg(0x08, 0x00);
	LD3320_delay( 1 );

	if(LD_Check_ASRBusyFlag_b2() == 0)
	{
		return 0;
	}

	LD_WriteReg(0xB2, 0xff);	
	LD_WriteReg(0x37, 0x06);
	LD_WriteReg(0x37, 0x06);
	LD3320_delay( 5);
	GUI_DispDecAt(LD_ReadReg(0xbf),200,40,3);	//text  0xbf==0x31--49
	LD_WriteReg(0x1C, 0x0b);
	LD_WriteReg(0x29, 0x10);
	
	LD_WriteReg(0xBD, 0x00);   
	return 1;
}
/************************************************************************
功能描述： 添加识别关键词语
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
// Return 1: success.
//	添加识别关键词语，开发者可以学习"语音识别芯片LD3320高阶秘籍.pdf"中关于垃圾词语吸收错误的用法
uint8 LD_AsrAddFixed(void)
{
	uint8 k, flag;
	uint8 nAsrAddLength;
	const char sRecog[5][13] = {"kai deng", "guan deng", 
		"fang jian a", "tian jin", "chong qing"};
		const uint8 pCode[5] = {CODE_KAIDENGD, CODE_GUANDENG, CODE_FANGJIANA, CODE_TIANJIN, CODE_CHONGQING};
		
	flag = 1;
	for (k=0; k<5; k++)
	{			
		if(LD_Check_ASRBusyFlag_b2() == 0)
		{
			flag = 0;
			break;
		}
		
		LD_WriteReg(0xc1, pCode[k] );
		LD_WriteReg(0xc3, 0 );
		LD_WriteReg(0x08, 0x04);
		LD3320_delay(1);
		LD_WriteReg(0x08, 0x00);
		LD3320_delay(1);

		for (nAsrAddLength=0; nAsrAddLength<20; nAsrAddLength++)
		{
			if (sRecog[k][nAsrAddLength] == 0)
				break;
			LD_WriteReg(0x5, sRecog[k][nAsrAddLength]);
		}
		LD_WriteReg(0xb9, nAsrAddLength);
		LD_WriteReg(0xb2, 0xff);
		LD_WriteReg(0x37, 0x04);
		LD_WriteReg(0x37, 0x04);
	}	 
	    GUI_DispDecAt(LD_ReadReg(0xbf),200,20,3);	//text  0xbf==0x31--49
    return flag;
}


/************************************************************************
功能描述： 	获取识别结果
调用函数： 
入口参数： 
返回函数： 
**************************************************************************/
uint8 LD_GetResult(void)
{
	GUI_DispDecAt(LD_ReadReg(0xc5),200,80,3);
	return LD_ReadReg(0xc5 );
}



