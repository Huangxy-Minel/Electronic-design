/*-----------------------------------------------
  名称：AD9854并口驱动
  编写：Lu
  日期：2014.3
  修改：无
  内容：
------------------------------------------------*/
#include "AD9854_Parallel.h"
#define Ref_Frequence 25

extern unsigned long Frequence;	//频率，单位HZ
extern int Amplitude[2];		//幅度，两个通道
extern unsigned int phase;					//相位差，单位 度
GPIO_InitTypeDef GPIO_InitStructure;

//uchar Freq1Word[6] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00};

void Init_9854(void)  //INIT 9854 
{// uint i;
 
	

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE); // 使能PC端口时钟  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_15;	//选择对应的引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PC端
	
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//选择对应的引脚
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始
	
	
	WRB(0);
	UDCLK(0);
//	FSK_D(0);
	RESET(1);
	RESET(0);
	
//1.先写控制字
//Bit5-Bit7为任意；Bit4为比较器PD；Bit3保留.一般为低；Bit2为QDAC的PD(Power-down)；Bit1为DAC的PD；Bit0为DIG PD
	Write_9854(0x1d,0x00);//10
//Bit7为任意；Bit6为PLL range；Bit5为旁路PLL；bit4-bit0为倍频数////30晶振*10＝300MHz系统
	Write_9854(0x1e,0x4a);
//bit7为清零ACC1；bit6为清零ACC2（一般必须为低）；bit5为三角扫频；bit4为外用QDAC；bit3-bit1为模式选择；bit0为使用内/外更新时钟
	Write_9854(0x1f,0x00);
//Bit7为任意；bit6为旁路反正弦；bit5为OSK使能（默认为1，单频模式下无输出）；bit4为OSK INT；bit3-2为任意；bit1为设置串行模式下低位先传；bit0为设置串行模式下SDO可用
	Write_9854(0x20,0x60);//0x20,0x00

//2.写频率
	Write_frequence(Frequence);
//3.写幅度
	Write_Amplitude(0,Amplitude[0]);
	Write_Amplitude(1,Amplitude[1]);
 
	UDCLK(1); 
	UDCLK(0); 
}

void Write_9854(unsigned char address,unsigned char DATA)
{
	WRB(1);
	//ADDR =  address; 
	
	GPIOB->BSRR =(address<<3) & 0x01f8; 
	GPIOB->BRR = ~(address<<3) & 0x01f8;
	
	//GPIO_SetBits(GPIOB,address& 0x01f8); 
	//GPIO_ResetBits(GPIOB,~address& 0x01f8); 
	
	
	GPIOA->BSRR = DATA & 0x00ff; 
	GPIOA->BRR = ~DATA & 0x00ff;
	
	//GPIO_SetBits(GPIOA, DATA & 0x00FF); 
	//GPIO_ResetBits(GPIOA, (~DATA & 0x00FF)); 
	///PDATA = DATA;	
	
	WRB(0);
}

//==============更新频率====================================
void Write_frequence(unsigned long x)
{
	WRB(0);
	UDCLK(0);
	
	Write_9854(0x08,0);
	Write_9854(0x09,0);
	x *= (429.4967296/Ref_Frequence);	//	控制字 = 频率(HZ) 2^48 /(2^16)/(300*10^6)

  Write_9854(0x07,(unsigned char)x);
  Write_9854(0x06,(unsigned char)(x>>8));
	Write_9854(0x05,(unsigned char)(x>>16));
	Write_9854(0x04,(unsigned char)(x>>24));
	
	UDCLK(1); 
	UDCLK(0); 

}
//==============更新幅度====================================
void Write_Amplitude(unsigned char Channel,unsigned int Ampli)
{  
	WRB(0);
	UDCLK(0);
	
	if(Channel)
		{	Write_9854(0x23,(Ampli>>8));
			Write_9854(0x24,Ampli);
		}		 
	else
		{	Write_9854(0x21,(Ampli>>8));
			Write_9854(0x22,Ampli);
		}
	UDCLK(1); 
	UDCLK(0);
}
