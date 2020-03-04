#include "key.h"
#include "delay.h" 
//按键初始化函数
void KEY_Init(void)
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//GPIOE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//下拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE3,4,5,6

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//GPIOE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE3,4,5,6
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//GPIOF时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOF1,2,3,4
  GPIO_SetBits(GPIOF,GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4);
  GPIO_ResetBits(GPIOE,GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6);
}

//int KEY_Scan1()//独立按键检测
//{
//if(K1==0)
//	return 0;
//else if(K2==1)
//	return 1;
//else if(K3==1)
//	return 2;
//}
//按键处理函数
//返回按键值
//int KEY_Scan()
//{	 	 
//	   PFout(0)=0;//R1为零
//	   if(C4==0||C3==0||C2==0||C1==0)
//		{
//			delay_ms(100);//去抖动 
//			if(C1==0)
//			{
//				PFout(0)=1;//R1恢复
//				return 1;
//			}
//			else if(C2==0)			
//			{
//				PFout(0)=1;//R1恢复
//				return 2;
//			}
//			else if(C3==0)
//			{
//				PFout(0)=1;//R1恢复
//				return 3;
//			}
//			else if(C4==0)
//			{
//				PFout(0)=1;//R1恢复
//				return 4;
//			}
//		    else if(C1==1&&C2==1&&C3==1&&C4==1) 	    
//			{
//				PFout(0)=1;//R1恢复
//				return 0;
//			}
//		}

//	   PFout(1)=0;//R2为零
//	   if(C4==0||C3==0||C2==0||C1==0)
//		{
//			delay_ms(100);//去抖动 
//			if(C1==0)
//			{
//				PFout(1)=1;//R2恢复
//				return 5;
//			}
//			else if(C2==0)			
//			{
//				PFout(1)=1;//R2恢复
//				return 6;
//			}
//			else if(C3==0)
//			{
//				PFout(1)=1;//R2恢复
//				return 7;
//			}
//			else if(C4==0)
//			{
//				PFout(1)=1;//R2恢复
//				return 8;
//			}
//		    else if(C1==1&&C2==1&&C3==1&&C4==1) 	    
//			{
//				PFout(1)=1;//R2恢复
//				return 0;
//			}
//         }

//  
//	   PFout(2)=0;//R3为零
//	   if((C4==0||C3==0||C2==0||C1==0))
//		{
//			delay_ms(100);//去抖动 
//			if(C1==0)
//			{
//				PFout(2)=1;//R3恢复
//				return 9;
//			}
//			else if(C2==0)			
//			{
//				PFout(2)=1;//R3恢复
//				return 10;
//			}
//			else if(C3==0)
//			{
//				PFout(2)=1;//R3恢复
//				return 11;
//			}
//			else if(C4==0)
//			{
//				PFout(2)=1;//R3恢复
//				return 12;
//			}
//		    else if(C1==1&&C2==1&&C3==1&&C4==1) 	    
//			{
//				PFout(2)=1;//R3恢复
//				return 0;
//			}
//         }

//	   PFout(3)=0;//R4为零
//	   if((C4==0||C3==0||C2==0||C1==0))
//		{
//			delay_ms(100);//去抖动 
//			if(C1==0)
//			{
//				PFout(3)=1;//R4恢复
//				return 13;
//			}
//			else if(C2==0)			
//			{
//				PFout(3)=1;//R4恢复
//				return 14;
//			}
//			else if(C3==0)
//			{
//				PFout(3)=1;//R4恢复
//				return 15;
//			}
//			else if(C4==0)
//			{
//				PFout(3)=1;//R4恢复
//				return 16;
//			}
//		    else if(C1==1&&C2==1&&C3==1&&C4==1) 	    
//			{
//				PFout(3)=1;//R4恢复
//				return 0;
//			}
//         
//		}

//}




















