#include "main.h"
#include "timer.h"
#include <stdlib.h>

float FFT_INPUT[FFT_LENGTH];
float FFT_OUTPUT[FFT_LENGTH*2];
float FFT_MAGNITUDE[FFT_LENGTH];
float MAX_VOL;
u32   MAX_INDEX;
const float TURN_A = 6279.f;
const float TURN_B = 0.075f;
	
u8 flag;
u16 count;
void systemInit(void);//系统初始化

void systemInit(void) {
	delay_init(84);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	uart_init(115200);
	LCD_Init();
	Adc_Init();
	TIM3_Int_Init(400-1,84-1);    // 2.5k采样率

}



int main(void) {
	int i,j,m[20],mm;
	char str;
	float temp;
	arm_rfft_fast_instance_f32 S;
	
	systemInit();
	arm_rfft_fast_init_f32(&S, FFT_LENGTH); //初始化结构体S中的参数

    while(1) {
		if(flag==1) { //如果获取到FFT_LENGTH个数据则开始处理
//			printf("in = [");
//			for(i=0;i<FFT_LENGTH;i++)
//				printf("%f ",FFT_INPUT[i]);
//			printf("];\r\n");
			
			for(i=0;i<FFT_LENGTH;i++)   FFT_INPUT[i] *= win[i];
			
			arm_rfft_fast_f32(&S, FFT_INPUT, FFT_OUTPUT, IFFT_FLAG); //FFT计算
			
			arm_cmplx_mag_f32(FFT_OUTPUT, FFT_MAGNITUDE, FFT_LENGTH);	//把运算结果复数求模得幅值
//			printf("mag = [");
//			for(i=0;i<FFT_LENGTH/2;i++)
//				printf("%f ",FFT_MAGNITUDE[i]);
//			printf("];\r\n\r\n");
			for(i=0;i<8;i++)    FFT_MAGNITUDE[i] = 0;
			arm_max_f32(FFT_MAGNITUDE,FFT_LENGTH/2,&MAX_VOL,&MAX_INDEX);
		//	for(i=MAX_INDEX-10;i<MAX_INDEX+10;i++)   MAX_VOL += FFT_MAGNITUDE[i];
			
			temp = (MAX_VOL/(FFT_LENGTH/2))*TURN_A+TURN_B/10;
			LCD_Clear(WHITE);
			 
			sprintf(&str,"%4.4f",temp);
			LCD_ShowString(10,50,100,24,24,"Cpp:");
			LCD_ShowString(100,50,100,24,24,&str);
			LCD_ShowString(230,50,100,24,24,"mA");			

			temp = (float) MAX_INDEX*ONE_POINT_F;
			sprintf(&str,"%4.4f",temp);
			LCD_ShowString(10,100,100,24,24,"Fre:");
			LCD_ShowString(100,100,100,24,24,&str);
			LCD_ShowString(190,100,100,24,24,"Hz");			
			
			for(i=0;i<21;i++)
			{
				if(temp*(i+2)>1000)
					break;
				mm=temp*(i+2)/ONE_POINT_F;
				m[i]=mm;
				for(j=0;j<20;j++)
				{
					if(FFT_MAGNITUDE[m[i]]<FFT_MAGNITUDE[mm+j])  m[i]=mm+j;					
				}
				for(j=0;j<20;j++)
				{
					if(FFT_MAGNITUDE[m[i]]<FFT_MAGNITUDE[mm-j])  m[i]=mm+j;
				}
			}

			LCD_ShowString(10,150,100,24,24,"Cpp1:");
			LCD_ShowxNum(100,150,FFT_MAGNITUDE[m[0]],5,24,1);
			LCD_ShowString(230,150,100,24,24,"mA");	
			

			LCD_ShowString(10,200,100,24,24,"Cpp2:");
			LCD_ShowxNum(100,200,FFT_MAGNITUDE[m[1]],5,24,1);
			LCD_ShowString(230,200,100,24,24,"mA");	
			
			LCD_ShowString(10,250,100,24,24,"Cpp3:");
			LCD_ShowxNum(100,250,FFT_MAGNITUDE[m[2]],5,24,1);
			LCD_ShowString(230,250,100,24,24,"mA");	
			

			LCD_ShowString(10,300,100,24,24,"Cpp4:");
			LCD_ShowxNum(100,300,FFT_MAGNITUDE[m[3]],5,24,1);
			LCD_ShowString(230,300,100,24,24,"mA");	
			

			LCD_ShowString(10,350,100,24,24,"Cpp5:");
			LCD_ShowxNum(100,350,FFT_MAGNITUDE[m[4]],5,24,1);
			LCD_ShowString(230,350,100,24,24,"mA");	
			
			LCD_ShowString(310,50,100,24,24,"Cpp6:");
			LCD_ShowxNum(400,50,FFT_MAGNITUDE[m[5]],5,24,1);
			LCD_ShowString(530,50,100,24,24,"mA");	
			
			LCD_ShowString(310,100,100,24,24,"Cpp7:");
			LCD_ShowxNum(400,100,FFT_MAGNITUDE[m[6]],5,24,1);
			LCD_ShowString(530,100,100,24,24,"mA");

			LCD_ShowString(310,150,100,24,24,"Cpp8:");
			LCD_ShowxNum(400,150,FFT_MAGNITUDE[m[7]],5,24,1);
			LCD_ShowString(530,150,100,24,24,"mA");
			
			//delay_ms(1000);
			flag=0; //开始下一次计算
		}
	}
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	u16 adcx;
	u16 temp;
	float vol;
    u8 i;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		if(flag == 0)
		{

		   adcx = ADC1->DR;
		   FFT_INPUT[count] = adcx*3.3f/4096.f;
		  
	        count ++;
			if(count == FFT_LENGTH)  
			{ 
			   count = 0;
				flag = 1;
			
			}
		}
	}
	
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
	
}



