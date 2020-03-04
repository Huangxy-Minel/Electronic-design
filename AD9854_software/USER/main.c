/*
    程序修改自惠特例程C51例程
    作者：gentalk
    邮箱：gentalk@163.com
    修改过的程序已在STM32,430,DSP28335,C51上测试过，比原程序在时序上的兼容性更好。
    在不同平台上的移植要注意codetab.h中数组的定义，oled.c中OLED_GPIO_Init()对IO口初始化的移植，以及oled.h中接口的定义。
*/

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "bmp.h"
//const unsigned char gImage_1[960];
#include "myimage.h"
#include "dds.h"
#include "exti.h"
#include "key.h"



int main()
{
    delay_init(); //延时初始化
    OLED_GPIO_Init();
    OLED_Init();
	
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	
		KEY_Init();
		EXTIX_Init();
	  pin_Init();
		//Init_9854();		
		WR = 1;
		UD = 1;
		MRST = 1;
		RD = 1;
	  A0=1;
	  A1=1;
	  A2=1;
	  A3=1;
	  A4=1;
	  A5=1;
	while(1)
	{
//				OLED_P16x16Ch(24,0,1);
//				OLED_P16x16Ch(40,0,2);
//				OLED_P16x16Ch(57,0,3);
//				OLED_P16x16Ch(74,0,4);
//				OLED_P16x16Ch(91,0,5);
//				for(i=0; i<8; i++)//通过点整显示汉字 -- i表示字表数组的位置
//				{
//					OLED_P16x16Ch(i*16,0,i);
//				 	OLED_P16x16Ch(i*16,2,i+8);
//				 	OLED_P16x16Ch(i*16,4,i+16);
//				 	OLED_P16x16Ch(i*16,6,i+24);
//				}
				
//              
//				OLED_CLS();//清屏

//				OLED_P8x16Str(0,0,"HelTec");//第一行 -- 8x16的显示单元显示ASCII码
//				OLED_P8x16Str(0,2,"OLED Display");
//				OLED_P8x16Str(0,4,"www.heltec.cn");
//				OLED_P6x8Str(0,6,"cn.heltec@gmail.com");
//				OLED_P6x8Str(0,7,"heltec.taobao.com");
//				delay_ms(1000);
//           
//			OLED_CLS();

				OLED_P6x8Str(0,2,"AD9854_CL_08");
				OLED_P6x8Str(0,4,"Fre(Ch1):");
			
				OLED_P6x8Str(100,4,"MHz");
				OLED_P6x8Str(0,6,"Fre(Ch2):");
				OLED_P6x8Str(100,6,"MHz");
				//OLED_Set_Pos(0,0);
				//OLED_WrDat(0xff);
				//OLED_P8x16Str(0,0,"HelTec");
		
           

	}

        
}
