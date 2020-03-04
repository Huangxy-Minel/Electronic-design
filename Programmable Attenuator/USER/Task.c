#include "key.h"
#include "can.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
u8 Init_Task()
{
	u8 data[4]={0,1,6,0};
	delay_init(48);
	KEY_Init(); 				//按键初始化  
	LED_Init();	
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_4tq,CAN_BS1_5tq,48,CAN_Mode_Normal);//CAN初始化环回模式,波特率100Kbps 
	return 0;
}
//static void dectobin(u8 n,u8 *data)
//{
//	u8 i,temp,j=7;
//	temp=n;
//	while(temp)
//	{
//		i=temp%2;
//		data[j]=i;
//		j--;
//		temp=temp/2;
//	}
//}
u8 Can_Send()
{
	u8 key,i;
	u8 canbuf[8]={0};
	u8 mode=0;

	key=KEY_Scan(0);
	if(key==3)
	{

		key=0;
		mode++;
		if(mode==64)
			mode=0;
	
	  mode=5;
	  mode*=5;
		canbuf[0]=0;
		canbuf[1]=mode%100;
		mode-=canbuf[1]*100;
		canbuf[2]=mode%10;
		mode-=canbuf[2]*10;
		canbuf[3]=mode;
//	dectobin(mode+1,canbuf);
	i=CAN1_Send_Msg(canbuf,4);
	if(i==0)
		LED0=!LED0;
  }
	return 0;
}
