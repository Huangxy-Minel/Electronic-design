#include "ads1274.h"
#include "usart.h"
//#include "delay.h"
#include "main.h"

#define DOUT1 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8);
#define DOUT2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4);
u16 count=0;
u8 flag;

void ADS1274_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	/* 打开GPIOF时钟 F7<->SYNC F3<->SCLK */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	/* IO口设置 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure); //初始化 GPIOF8
		
	/* 打开数据接收中断 ADDRDY GPIOE2 */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2); //以上是F1的写法
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); //使能 SYSCFG 时钟
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

}


void ADS1274_ReadData(void) {

	u8 i;
	int DATA_DOUT1 = 0;
	int DATA_DOUT2 = 0;
	float RESULT_DOUT1,RESULT_DOUT2;
	float temp;
	if(flag==0) {
		for(i=0; i<24; i++) {
			//delay_us(15);
			GPIO_SetBits(GPIOF,GPIO_Pin_3);
			DATA_DOUT1 = (DATA_DOUT1 << 1) + DOUT1;
			DATA_DOUT2 = (DATA_DOUT2 << 1) + DOUT2;
			//delay_us(15);
			GPIO_ResetBits(GPIOF,GPIO_Pin_3);
		}
		
		if((DATA_DOUT1 & 0x00800000) != 0) {
			DATA_DOUT1 |= 0xFF000000;
			RESULT_DOUT1 = (float)DATA_DOUT1 / 8388608*2.5;//(2^23);
		}
		else
			RESULT_DOUT1 = (float)DATA_DOUT1 / 8388607*2.5;//(2^23-1);
		RESULT_DOUT1 *= -1;
		FFT_INPUT[count]=RESULT_DOUT1;
		
		if((DATA_DOUT2 & 0x00800000) != 0) {
			DATA_DOUT2 |= 0xFF000000;
			RESULT_DOUT2 = (float)DATA_DOUT2 / 8388608*2.5;//(2^23);
		}
		else
			RESULT_DOUT2 = (float)DATA_DOUT2 / 8388607*2.5;//(2^23-1);
		RESULT_DOUT2*=-1;
//		FFT_INPUT2[count]=RESULT_DOUT2;
		
		count++;
		
//		printf("%f\r\n", RESULT_DOUT1);
		if(count==FFT_LENGTH) {
			flag=1;
			count=0;
		}
	}
}


/* ADDRDY中断处理函数 */
void EXTI2_IRQHandler(void) {
	if(EXTI_GetFlagStatus(EXTI_Line2) == SET)
		ADS1274_ReadData();
	EXTI_ClearITPendingBit(EXTI_Line2);
}
