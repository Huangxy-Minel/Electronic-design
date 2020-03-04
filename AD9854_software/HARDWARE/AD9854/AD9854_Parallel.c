/*-----------------------------------------------
  ���ƣ�AD9854��������
  ��д��Lu
  ���ڣ�2014.3
  �޸ģ���
  ���ݣ�
------------------------------------------------*/
#include "AD9854_Parallel.h"
#define Ref_Frequence 25

extern unsigned long Frequence;	//Ƶ�ʣ���λHZ
extern int Amplitude[2];		//���ȣ�����ͨ��
extern unsigned int phase;					//��λ���λ ��
GPIO_InitTypeDef GPIO_InitStructure;

//uchar Freq1Word[6] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00};

void Init_9854(void)  //INIT 9854 
{// uint i;
 
	

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PC�˿�ʱ��  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_15;	//ѡ���Ӧ������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PC��
	
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//ѡ���Ӧ������
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ
	
	
	WRB(0);
	UDCLK(0);
//	FSK_D(0);
	RESET(1);
	RESET(0);
	
//1.��д������
//Bit5-Bit7Ϊ���⣻Bit4Ϊ�Ƚ���PD��Bit3����.һ��Ϊ�ͣ�Bit2ΪQDAC��PD(Power-down)��Bit1ΪDAC��PD��Bit0ΪDIG PD
	Write_9854(0x1d,0x00);//10
//Bit7Ϊ���⣻Bit6ΪPLL range��Bit5Ϊ��·PLL��bit4-bit0Ϊ��Ƶ��////30����*10��300MHzϵͳ
	Write_9854(0x1e,0x4a);
//bit7Ϊ����ACC1��bit6Ϊ����ACC2��һ�����Ϊ�ͣ���bit5Ϊ����ɨƵ��bit4Ϊ����QDAC��bit3-bit1Ϊģʽѡ��bit0Ϊʹ����/�����ʱ��
	Write_9854(0x1f,0x00);
//Bit7Ϊ���⣻bit6Ϊ��·�����ң�bit5ΪOSKʹ�ܣ�Ĭ��Ϊ1����Ƶģʽ�����������bit4ΪOSK INT��bit3-2Ϊ���⣻bit1Ϊ���ô���ģʽ�µ�λ�ȴ���bit0Ϊ���ô���ģʽ��SDO����
	Write_9854(0x20,0x60);//0x20,0x00

//2.дƵ��
	Write_frequence(Frequence);
//3.д����
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

//==============����Ƶ��====================================
void Write_frequence(unsigned long x)
{
	WRB(0);
	UDCLK(0);
	
	Write_9854(0x08,0);
	Write_9854(0x09,0);
	x *= (429.4967296/Ref_Frequence);	//	������ = Ƶ��(HZ) 2^48 /(2^16)/(300*10^6)

  Write_9854(0x07,(unsigned char)x);
  Write_9854(0x06,(unsigned char)(x>>8));
	Write_9854(0x05,(unsigned char)(x>>16));
	Write_9854(0x04,(unsigned char)(x>>24));
	
	UDCLK(1); 
	UDCLK(0); 

}
//==============���·���====================================
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
