#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "AD9959.h"


int main(void)
{
  HAL_Init();				        //��ʼ��HAL��
	Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz
	delay_init(216);                //��ʱ��ʼ��
	Init_AD9959();
 while(1)
    {
        
    }	
}
