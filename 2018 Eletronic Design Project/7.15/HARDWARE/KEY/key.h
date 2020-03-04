#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
#define C4		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) //PE3        
#define C3 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)	//PE4 
#define C2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) //PE5
#define C1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) //PE6

#define K1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9) //PA9
#define K2 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10) //PA10
#define K3 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) //PA11
#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
#define WK_UP 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0

//#define R1 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0) //PF0
//#define R2 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1) //PF1
//#define R3 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2) //PF2
//#define R4 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3) //PF3
//void KEY_Init(void);	//IO初始化
//int KEY_Scan();  		//按键扫描函数	

#endif
