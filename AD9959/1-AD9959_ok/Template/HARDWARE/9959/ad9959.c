#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "ad9959.h"

u8 AD9959_Value[4] = {0x00, 0x00, 0x00, 0x00};
u8 Reg_Len[25]={1,3,2,3,4,2,3,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};		//对应不同寄存器位数，1*8,2*8，3*8，或者4*8

void AD9959_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();			//开启GPIOA时钟 
	__HAL_RCC_GPIOC_CLK_ENABLE();			//开启GPIOC时钟 
	__HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOF时钟 
	__HAL_RCC_GPIOG_CLK_ENABLE();			//开启GPIOG时钟 
	
	//初始化PA8(P3)
	GPIO_Initure.Pin=GPIO_PIN_6;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	//初始化PC6(3.3V),PC7(SCLK),PC8(CS),PC9(UD)
	GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);
	
	//初始化PG2(PWDN),PG4(RST),PG5(D3),PG6(D2),PG7(D1),PG8(D0)
	GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	//初始化PH13(P2),PH14(P1),PH15(P0)
	GPIO_Initure.Pin=GPIO_PIN_2;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOG,&GPIO_Initure);
	
	
	AD9959_SDIO3(0);//datasheet说第三脚不用得拉低
	AD9959_PWDN(0);
	AD9959_Reset();
	delay_ms(10);
	AD9959_WRrg(FR1,0xD00000,1);//设置系统时钟倍频
	delay_ms(10);
	
}

void AD9959_Reset(void)
{
	AD9959_RST(0);
	delay_us(50);
	AD9959_RST(1);
	delay_us(50);
	AD9959_RST(0);
}

//update the locked data
void AD9959_Update(void)
{
	AD9959_UP(0);
	delay_us(50);
	AD9959_UP(1);
	delay_us(50);
	AD9959_UP(0);
}

void AD9959_WRrg(u8 reg, u32 data,u8 temp)
{
	u8	ControlValue = 0;
	u8	ValueToWrite = 0;
	u8 i,j, nbyte;
	nbyte= Reg_Len[reg];
	ControlValue = reg;	//Create the 8-bit header

	AD9959_SCK(0);
	AD9959_CS(0);	 				//bring CS low
	for(i=0; i<8; i++)				//Write out the control word
	{
		AD9959_SCK(0);
		if(0x80 == (ControlValue & 0x80))
		{
			AD9959_SDIO0(1);	  	//Send one to SDIO0pin
		}
		else
		{
			AD9959_SDIO0(0);	  	//Send zero to SDIO0pin
		}
		AD9959_SCK(1);
		ControlValue <<= 1;			//Rotate data
	}
	AD9959_SCK(0);

	for (j=0; j<nbyte; j++)		//And then the data
	{
		ValueToWrite=((data>>((nbyte-1-j)*8))&0xff);
		for (i=0; i<8; i++)
		{
			AD9959_SCK(0);
			if(0x80 == (ValueToWrite & 0x80))
			{
				AD9959_SDIO0(1);	  	//Send one to SDIO0pin
			}
			else
			{
				AD9959_SDIO0(0);	  	//Send zero to SDIO0pin
			}
			AD9959_SCK(1);
			ValueToWrite <<= 1;			//Rotate data
		}
		AD9959_SCK(0);
	}
	if(temp==1)
		AD9959_Update();
	AD9959_CS(1);						//bring CS high again
} 

void AD9959_Set_Fre(u8 Channel,double Freq)
{	 	  
	  unsigned long Temp;            
	  Temp=(u32)(Freq*FRE_REF);	 

	  AD9959_WRrg(CSR,Channel,0);
	  AD9959_WRrg(CFTW0,Temp,0);
}

void AD9959_Set_Amp(u8 Channel,u16 amp)
{
	u32 dat;
	dat = 0x00001000+amp;
	AD9959_WRrg(CSR,Channel,0);
	AD9959_WRrg(0x06,dat,0);
}

void AD9959_Set_Pha(u8 Channel,double pha)
{
	u16 Temp;
	Temp = (u16)(PHA_REF*pha);
	AD9959_WRrg(CSR,Channel,0);
	AD9959_WRrg(CPOW,Temp,0);
}
