#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "AD9959.h"


int main(void)
{
  HAL_Init();				        //初始化HAL库
	Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz
	delay_init(216);                //延时初始化
	Init_AD9959();
 while(1)
    {
        
    }	
}
