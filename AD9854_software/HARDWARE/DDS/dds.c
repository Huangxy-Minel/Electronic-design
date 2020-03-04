#include "dds.h"
#include "delay.h"

unsigned long Frequence[2];	//频率
int Amplitude[2] = {4095,4095};		//·幅度(两个通道)
unsigned int phase = 90;					//相位差
unsigned char Ref_Frequence = 25;	//基准频率（MHz）

void pin_Init()
{
		 GPIO_InitTypeDef  GPIO_InitStructure;
		 
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			
		 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_15;	
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		 GPIO_Init(GPIOA, &GPIO_InitStructure);					
		 //GPIO_SetBits(GPIOB,GPIO_Pin_5);					
	
		 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_9;	//GPIO_Pin_15
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}



void write_9854(unsigned char address,unsigned char data)
{
	u8 msk = 1;
	WR = 1;

	//按位写地址（六位）
	
	//按位写地址（六位）
	
	A0 = (address & msk)?1:0;
	msk <<= 1;
	A1 = (address & msk)?1:0;
	msk <<= 1;
	A2 = (address & msk)?1:0;
	msk <<= 1;
	A3 = (address & msk)?1:0;
	msk <<= 1;
	A4 = (address & msk)?1:0;
	msk <<= 1;
	A5 = (address & msk)?1:0;
	
	//按位写数据（八位）
	msk = 1;
	D0 = (data & msk)?1:0;
	msk <<= 1;
	D1 = (data & msk)?1:0;
	msk <<= 1;
	D2 = (data & msk)?1:0;
	msk <<= 1;
	D3 = (data & msk)?1:0;
	msk <<= 1;
	D4 = (data & msk)?1:0;
	msk <<= 1;
	D5 = (data & msk)?1:0;
	msk <<= 1;
	D6 = (data & msk)?1:0;
	msk <<= 1;
	D7 = (data & msk)?1:0;

	WR = 0;
	//WR = 1;
		//RD = 0;
		//RD = 1;
}






//更新频率
void write_fre(int channel,unsigned long x)
{
	if(channel){
		WR = 0;
		UD = 0;
		write_9854(0x0E,0);
		write_9854(0x0F,0);
		x *= (429.4967296/Ref_Frequence);	//控制字 = 频率（HZ） 2^48 / (2^16) / (300*10^6)
		
		write_9854(0x0D,(unsigned char)x);
		write_9854(0x0C,(unsigned char)(x>>8));
		write_9854(0x0B,(unsigned char)(x>>16));
		write_9854(0x0A,(unsigned char)(x>>24));
		
		UD = 1;
		UD = 0;
	}
	else{
		WR = 0;
		UD = 0;
		write_9854(0x08,0);
		write_9854(0x09,0);
		x *= (429.4967296/Ref_Frequence);	//控制字 = 频率（HZ） 2^48 / (2^16) / (300*10^6)
		
		write_9854(0x07,(unsigned char)x);
		write_9854(0x06,(unsigned char)(x>>8));
		write_9854(0x05,(unsigned char)(x>>16));
		write_9854(0x04,(unsigned char)(x>>24));
		
		UD = 1;
		UD = 0;
	}
}

//更新幅度
void write_amp(int channel,unsigned int Ampli)
{
	WR = 0;
	UD = 0;
	
	if(channel)
	{
		write_9854(0x23,(Ampli>>8));
		write_9854(0x24,Ampli);
	}
	else
	{
		write_9854(0x21,(Ampli>>8));
		write_9854(0x22,Ampli);
	}
	
	UD = 1;
	UD = 0;
}	




void Init_9854()
{
	Frequence[0] = 10000;
	Frequence[1] = 10000;
	//初始化引脚
	pin_Init();
	WR = 0;
//	RD = 1;
	UD = 0;
	MRST = 1;
	MRST = 0;
	
	//1.先写控制字
	write_9854(0x1d,0x00);//10
	write_9854(0x1e,0x4a);
	write_9854(0x1f,0x00);
	write_9854(0x20,0x60);//0x20,0x00

	//2.写频率
	write_fre(0,Frequence[0]);
	write_fre(1,Frequence[1]);
	
	//3.写幅度
	write_amp(0,Amplitude[0]);
	write_amp(1,Amplitude[1]);
	
	UD = 1;
	UD = 0;
}
                                                                                   

