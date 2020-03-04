#include "key.h"
#include "can.h"
u8 Init_Task()
{
	KEY_Init(); 				//按键初始化  
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_4tq,CAN_BS1_5tq,48,CAN_Mode_Normal);//CAN初始化环回模式,波特率100Kbps 
	return 0;
}
static void dectobin(u8 n,u8 *data)
{
	u8 i,temp,j=7;
	temp=n;
	while(temp)
	{
		i=temp%2;
		data[j]=i;
		j--;
		temp=temp/2;
	}
}
u8 Can_Send()
{
	u8 key,i;
	u8 cny=0;
	u8 canbuf[8]={0};
	u8 mode=0;
	key=KEY_Scan(0);
	if(key==1)
	{
		key=0;
		mode++;
		if(mode==64)
			mode=0;
	}
	i=mode*5;
	canbuf[1]=i%100;
	i-=canbuf[1]*100;
	canbuf[2]=i%10;
	i-=canbuf[2]*10;
	canbuf[3]=i;
//	dectobin(mode+1,canbuf);
	CAN1_Send_Msg(canbuf,4);
	return 0;
}
