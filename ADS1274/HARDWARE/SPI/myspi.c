#include "myspi.h"
#include "delay.h"

void SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
  __HAL_RCC_GPIOF_CLK_ENABLE();			//����GPIOFʱ��
  //__HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOFʱ��
	
  GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5; //PF0,2,3,4,5--DRDY,D1,D2,D3,D4
	//GPIO_Initure.Pin=GPIO_PIN_2;
  GPIO_Initure.Mode=GPIO_MODE_INPUT;  //����
  GPIO_Initure.Pull=GPIO_PULLUP;          //����
  GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
  HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_6; //PF6,1--SYNC,SCLK
	//GPIO_Initure.Pin=GPIO_PIN_1;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
  GPIO_Initure.Pull=GPIO_PULLUP;          //����
  GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
  HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET);	//SYNC��0
	delay_us(1);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET);	//SYNC��0
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET);	//SCLK��0
	
}

void Get_Adc(u32 * adc_buf)
{
	u8 i=0,j;
	int adc_temp;
//	SYNC(0);
//	SCLK(0);
//	SYNC(1); //��������
	while(1)
	{
		if(DRDY == 0)
		{
			for(j=0;j<23;j++)
			{
				SCLK(1);
				//delay_us(50);
				adc_buf[0] += D1;
				adc_buf[0] <<= 1;
				
				adc_buf[1] += D2;
				adc_buf[1] <<= 1;
				
				adc_buf[2] += D3;
				adc_buf[2] <<= 1;
				
				adc_buf[3] += D4;
				adc_buf[3] <<= 1;
				SCLK(0);
				//delay_us(50);
			}
			adc_buf[0] += D1;
			adc_buf[1] += D2;
			adc_buf[2] += D3;
			adc_buf[3] += D4;
			break;
		}
	}
	for(i=0;i<4;i++)
	{
		adc_buf[i] = ~adc_buf[i] + 1;
		adc_buf[i] &= 0x00FFFFFF;
	}
//	SYNC(0);
//	if(adc_buf & 0x800000)
//		adc_buf |= 0xFF000000;
	//return adc_buf;
}

