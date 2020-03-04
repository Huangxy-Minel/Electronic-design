#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"

/************************************************
 ALIENTEK ������STM32F7������ ʵ��1
 �����ʵ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


int main(void)
{
	u8 key;
	u8 n = 0;
	u8 i,j=0,flag[6]={0};
  Cache_Enable();                 //��L1-Cache
  HAL_Init();				        //��ʼ��HAL��
  Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
  delay_init(216);                //��ʱ��ʼ��
	uart_init(115200);		        //���ڳ�ʼ��
  LED_Init();                     //��ʼ��LED
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);	//PB1��0
  while(1)
  {
		key = KEY_Scan(0);
		switch(key)
		{
			case 0: 
				if(n<126)
					n++;
				break;
			case 1: 
				if(n>0)
					n--;
				break;
		}
		if(n <= 63)
		{
			for(i=1;i<=32;i*=2)
			{
				flag[j] = n&i;
				j++;
			}
		}
		if(flag[0] == 1)
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);	//PB1��0
			
  }
}


/*ʹ�üĴ�������ʵ�������
int main(void)
{ 
    Cache_Enable();                 //��L1-Cache
    HAL_Init();				        //��ʼ��HAL��
    Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
    delay_init(216);                //��ʱ��ʼ��
	uart_init(115200);		        //���ڳ�ʼ��
    LED_Init();      
	while(1)
	{
      GPIOB->BSRR=GPIO_PIN_1;      //LED0��
	  GPIOB->BSRR=GPIO_PIN_0<<16;  //LED1��
	  delay_ms(500);               //��ʱ500ms
      GPIOB->BSRR=GPIO_PIN_1<<16;  //LED0��
	  GPIOB->BSRR=GPIO_PIN_0;      //LED1��
	  delay_ms(500);               //��ʱ500ms
	 }
 }	

*/


