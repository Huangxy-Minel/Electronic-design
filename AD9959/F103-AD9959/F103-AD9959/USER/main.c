#include "stm32f10x.h"  
#include "delay.h"
#include "sys.h"
#include "oled.h"
//#include "adc.h"
#include "ad9959.h"

double fdds;

int main(void) 
{    
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear()  	; 		
	OLED_ShowString(1,0,"hI");
	
	AD9959_Init();//9959 ��ʼ��

	fdds=100000.f;//Ƶ�� 10M	

	AD9959_Set_Fre(AD9959_CH0,fdds);	
	AD9959_Set_Fre(AD9959_CH1,fdds);	
	AD9959_Set_Fre(AD9959_CH2,fdds);
	AD9959_Set_Fre(AD9959_CH3,fdds);
	AD9959_Update();
	
	AD9959_Set_Pha(AD9959_CH0,0);
	AD9959_Set_Pha(AD9959_CH1,90);
	AD9959_Set_Pha(AD9959_CH2,0);
	AD9959_Set_Pha(AD9959_CH3,0);
	AD9959_Update();
	
	AD9959_Set_Amp(AD9959_CH0,1023);//���ȷ�Χ  1-1023
	AD9959_Set_Amp(AD9959_CH1,1023);//���ȷ�Χ  1-1023
	AD9959_Set_Amp(AD9959_CH2,1023);//���ȷ�Χ  1-1023
	AD9959_Set_Amp(AD9959_CH3,1023);//���ȷ�Χ  1-1023
	AD9959_Update();
			
	while(1)
	{

	}
}

