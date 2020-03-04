#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"

/************************************************
 ALIENTEK 阿波罗STM32F7开发板 实验1
 跑马灯实验-HAL库版本
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


int main(void)
{
	u8 key;
	u8 n = 0;
	u8 i,j=0,flag[6]={0};
  Cache_Enable();                 //打开L1-Cache
  HAL_Init();				        //初始化HAL库
  Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
  delay_init(216);                //延时初始化
	uart_init(115200);		        //串口初始化
  LED_Init();                     //初始化LED
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);	//PB1置0
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
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);	//PB1置0
			
  }
}


/*使用寄存器操作实现跑马灯
int main(void)
{ 
    Cache_Enable();                 //打开L1-Cache
    HAL_Init();				        //初始化HAL库
    Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
    delay_init(216);                //延时初始化
	uart_init(115200);		        //串口初始化
    LED_Init();      
	while(1)
	{
      GPIOB->BSRR=GPIO_PIN_1;      //LED0亮
	  GPIOB->BSRR=GPIO_PIN_0<<16;  //LED1灭
	  delay_ms(500);               //延时500ms
      GPIOB->BSRR=GPIO_PIN_1<<16;  //LED0灭
	  GPIOB->BSRR=GPIO_PIN_0;      //LED1亮
	  delay_ms(500);               //延时500ms
	 }
 }	

*/


