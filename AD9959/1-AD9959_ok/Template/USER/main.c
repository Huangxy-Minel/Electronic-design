#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "exti.h"
#include "math.h"
#include "oled.h"
#include "touch.h"
#include "arm_math.h"
#include "math.h"
#include "adc.h"
#include "ad9959.h"

double fdds1,fdds2;


int main(void)
{
		Cache_Enable();                 //打开L1-Cache
    HAL_Init();				        //初始化HAL库
    Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
    delay_init(216);                //延时初始化
		LCD_Init();
	  uart_init(115200);		        //串口初始化
    LED_Init();                     //初始化LED                    
	  POINT_COLOR=BLACK; 
		EXTI_Init();                    //外部中断初始化
		MY_ADC_Init();
		AD9959_Init();//9959 初始化
		fdds1=100000.f;//频率 10M	
		fdds2=200000.f;
	
		AD9959_Set_Fre(AD9959_CH0,fdds1);	
		AD9959_Set_Fre(AD9959_CH1,fdds1);	
		AD9959_Set_Fre(AD9959_CH2,fdds2);
		AD9959_Set_Fre(AD9959_CH3,fdds2);
		AD9959_Update();
		
		AD9959_Set_Pha(AD9959_CH0,0);
		AD9959_Set_Pha(AD9959_CH1,90);
		AD9959_Set_Pha(AD9959_CH2,0);
		AD9959_Set_Pha(AD9959_CH3,120);
		AD9959_Update();
		
		AD9959_Set_Amp(AD9959_CH0,1023);//幅度范围  1-1023
		AD9959_Set_Amp(AD9959_CH1,1023);//幅度范围  1-1023
		AD9959_Set_Amp(AD9959_CH2,1023);//幅度范围  1-1023
		AD9959_Set_Amp(AD9959_CH3,1023);//幅度范围  1-1023
		AD9959_Update();
		while(1)
				{
						
				}
		return 0;
}
