#include "AD9959.h"
#include "delay.h"

u8 CSR_DATA0[1] = {0x10};     // 开 CH0
u8 CSR_DATA1[1] = {0x20};      // 开 CH1
u8 CSR_DATA2[1] = {0x40};      // 开 CH2
u8 CSR_DATA3[1] = {0x80};      // 开 CH3   
                                  
 
u8 FR2_DATA[2] = {0x00,0x00};//default Value = 0x0000
u8 CFR_DATA[3] = {0x00,0x03,0x02};//default Value = 0x000302     
                                  
u8 CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360
                                  


u8 LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----
                                  
u8 RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------
                                  
u8 FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

u32 SinFre[5] = {50, 50, 50, 50};
u32 SinAmp[5] = {1023, 1023, 1023, 1023};
u32 SinPhr[5] = {0, 4095, 4095*3, 4095*2};

float Freq_Constant;
u8 PLL_DIV;

void Cal_define_Var(void)
{
  PLL_DIV = AD9959SYS_CLK/25;
  Freq_Constant = 0xFFFFFFFF/(AD9959SYS_CLK*1000000.0);
}

void Init_AD9959(void)
{
	GPIO_InitTypeDef GPIO_Initure;
  u8 FR1_DATA[3] = {0xD0,0x00,0x00};// Charge pump control = 75uA FR1<23> -- VCO gain control =0? system clock below 160 MHz;    
  //FR1_DATA[0] = FR1_DATA[0]+(PLL_DIV<<2);//PLL_DIV??
	
	__HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOF时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOB时钟	

	GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10; //PF0,1
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_9; //PB9
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	InitIO_9959();
	InitReset();
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//写功能寄存器1
  //  WriteData_AD9959(FR2_ADD,2,FR2_DATA,0);
  //  WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
  //  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  //  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
  //  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
  //  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
  //  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
   //??????
  Write_frequence(3,SinFre[3]);
  Write_frequence(0,SinFre[0]); 
  Write_frequence(1,SinFre[1]);
  Write_frequence(2,SinFre[2]);

  ////  Write_frequence(3,50);
  ////  Write_frequence(0,50);
  ////  Write_frequence(1,50);
  ////  Write_frequence(2,50);

  Write_Phase(3, SinPhr[3]);
  Write_Phase(0, SinPhr[0]);
  Write_Phase(1, SinPhr[1]);
  Write_Phase(2, SinPhr[2]);

  Write_Amplitude(3, SinAmp[3]);
  Write_Amplitude(0, SinAmp[0]);
  Write_Amplitude(1, SinAmp[1]);
  Write_Amplitude(2, SinAmp[2]);
}

void InitIO_9959(void)
{
  //AD9959_PWR(0);
  CS(0);
  SCLK(0);
  UPDATE(0);
  PS0(0);
  PS1(0);
  PS2(0);
  PS3(0);
  SDIO0(0);
  SDIO1(0);
  SDIO2(0);
  SDIO3(0);
}

void InitReset(void)
{
  Reset(0);
  delay_us(50);
  Reset(1);
  delay_us(50);
  Reset(0);
}

void IO_Update(void)  
{
  UPDATE(0);
  delay_us(50);
  UPDATE(1);
  delay_us(50);
  UPDATE(0);
}

/**
  * @brief  写入数据
  * @funna  WriteData_9959
  * @param  地址(RegisterAddress), 数据长度(NumberofRegisters), 数据(*RegisterData), 更新(temp)
  * @retval None
  */
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp)
{
  u8  ControlValue = 0;
  u8  ValueToWrite = 0;
  u8  RegisterIndex = 0;
  u8  i = 0;

  ControlValue = RegisterAddress;
//写入地址
  SCLK(0);
  CS(0);  
  for(i=0; i<8; i++)
  {
    SCLK(0);
    if(0x80 == (ControlValue & 0x80))
			SDIO0(1);   
    else
			SDIO0(0);   
    SCLK(1);
    ControlValue <<= 1;
  }
  SCLK(0);
//写入数据
  for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
  {
    ValueToWrite = RegisterData[RegisterIndex];
    for (i=0; i<8; i++)
    {
      SCLK(0);
      if(0x80 == (ValueToWrite & 0x80))
				SDIO0(1);   
      else
				SDIO0(0);   
      SCLK(1);
      ValueToWrite <<= 1;
    }
    SCLK(0);   
  } 
  if(temp==1)
		IO_Update();  
  CS(1);
}

/**
  * @brief  写入频率
  * @funna  Write_frequence
  * @param  通道(channel), 频率(freq)
  * @retval None
  */
void Write_frequence(u8 Channel,u32 Freq)
{  
  u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};  //????
  u32 Temp;            
  Temp=(u32)Freq*Freq_Constant;    //?????????????  4.294967296=(2^32)/500000000
  CFTW0_DATA[3]=(u8)Temp;
  CFTW0_DATA[2]=(u8)(Temp>>8);
  CFTW0_DATA[1]=(u8)(Temp>>16);
  CFTW0_DATA[0]=(u8)(Temp>>24);
  if(Channel==0)    
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//???????CH0??
    WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.??CH0????
  }
  else if(Channel==1) 
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//???????CH1??
    WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.??CH1????  
  }
  else if(Channel==2) 
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//???????CH2??
    WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.??CH2????  
  }
  else if(Channel==3) 
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//???????CH3??
    WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,3);//CTW0 address 0x04.??CH3????  
  }
} 

/**
  * @brief  设置幅度
  * @funna  Write_Amplitude
  * @param  通道(channel), 幅度(ampli)
  * @retval None
  */
void Write_Amplitude(u8 Channel, u16 Ampli)
{ 
  u16 A_temp;//=0x23ff;
  u8 ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
  
  A_temp=Ampli|0x1000;
  ACR_DATA[2] = (u8)A_temp;  //????
  ACR_DATA[1] = (u8)(A_temp>>8); //????
  if(Channel==0)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
  }
  else if(Channel==1)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
  }
  else if(Channel==2)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
  }
  else if(Channel==3)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
  }
}

/**
  * @brief  写入相位
  * @funna  Write_Phase
  * @param  通道(channel), 相位(Phase)
  * @retval None
  */
void Write_Phase(u8 Channel,u16 Phase)
{
  u16 P_temp=0;
  P_temp=(u16)Phase;
  CPOW0_DATA[1]=(u8)P_temp;
  CPOW0_DATA[0]=(u8)(P_temp>>8);
  if(Channel==0)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA0,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==1)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA1,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==2)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA2,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==3)
  {
    WriteData_AD9959(CSR_ADD,1,CSR_DATA3,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
}  














