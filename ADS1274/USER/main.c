#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "myspi.h"
#include "lcd.h"
    
int main(void)
	{
	u32 adc_buf[4] = {0};
	float adc_res[4] = {0};
	u32 i;
	float res;
	u32 adcx;
	Cache_Enable();
	HAL_Init();
  Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 	
	delay_init(216);                //延时初始化
	uart_init(115200);		        //串口初始化
	LCD_Init();                     //初始化LCD
	SPI_Init();
	POINT_COLOR=RED;
	while(1)
	{
		res = 0;
		//LCD_ShowString(10,40,260,32,32,"Apollo STM32F7"); 
//		for(i=0;i<100;i++)
//			adc_buf[i] = Get_Adc(1);
		Get_Adc(adc_buf);
//		for(i=0;i<100;i++)
//			LCD_DrawLine(i+100,adc_buf[i]/1000000+300,i+101,adc_buf[i+1]/10000000+300);
//		for(i=0;i<4;i++)
//		{
//			adc_res[i] = adc_buf[i] *2.5f /0x7FFFFF;
//			res += adc_res[i];
//		}
			for(i=0;i<4;i++)
		{
			adc_res[i] = adc_buf[i] *2.5f /0x7FFFFF;
		}
		res = adc_res[0];
		adcx = res;
		LCD_ShowxNum(134,150,adcx,1,16,0);    //显示电压值的整数部分，3.1111的话，这里就是显示3
		res -= adcx;
		res *= 10000000;
		LCD_ShowxNum(150,150,res,8,16,0X80); //显示小数部分（前面转换为了整形显示），这里显示的就是111.
		
		res = adc_res[1];
		adcx = res;
		LCD_ShowxNum(134,180,adcx,1,16,0);    //显示电压值的整数部分，3.1111的话，这里就是显示3
		res -= adcx;
		res *= 10000000;
		LCD_ShowxNum(150,180,res,8,16,0X80); //显示小数部分（前面转换为了整形显示），这里显示的就是111.
		
		res = adc_res[2];
		adcx = res;
		LCD_ShowxNum(134,210,adcx,1,16,0);    //显示电压值的整数部分，3.1111的话，这里就是显示3
		res -= adcx;
		res *= 10000000;
		LCD_ShowxNum(150,210,res,8,16,0X80); //显示小数部分（前面转换为了整形显示），这里显示的就是111.
		
		res = adc_res[3];
		adcx = res;
		LCD_ShowxNum(134,230,adcx,1,16,0);    //显示电压值的整数部分，3.1111的话，这里就是显示3
		res -= adcx;
		res *= 10000000;
		LCD_ShowxNum(150,230,res,8,16,0X80); //显示小数部分（前面转换为了整形显示），这里显示的就是111.
		//LCD_ShowxNum(10,80,adc_buf[50],10,32,0);
		delay_ms(100);
//		res = 2.5f - (adc_buf-0x800000) /8388608.f * 2.5f;
//		temp = (int)res;
//		LCD_ShowxNum(10,80,temp,10,32,0);
//		temp = (res-temp)*10000000;
//		LCD_ShowxNum(10,110,temp,10,32,0);
	}
}
