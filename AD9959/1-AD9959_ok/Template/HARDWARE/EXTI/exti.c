#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
extern u8 state;//全局变量：状态列表。
extern u32 adc_ch;
extern u8 adc_state;
//外部中断初始化
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟
        
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;               //PC13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;				//上拉
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    

    
    //中断线0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0
    
    //中断线1
    HAL_NVIC_SetPriority(EXTI1_IRQn,2,1);       //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);             //使能中断线1
    
    //中断线2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,2);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //使能中断线2
		
		 //中断线3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,3);       //抢占优先级为2，子优先级为3
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //使能中断线3
		
		//中断线4
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,4);       //抢占优先级为2，子优先级为4
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);             //使能中断线4
    
    //中断线5
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,5);   //抢占优先级为2，子优先级为5
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);         //使能中断线5  
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);   //调用中断处理公用函数
}

void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);   //调用中断处理公用函数
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);   //调用中断处理公用函数
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);   //调用中断处理公用函数
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);   //调用中断处理公用函数
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);  //调用中断处理公用函数
}

//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static u8 led0sta=1,led1sta=1;
    delay_ms(100);      //消抖
    switch(GPIO_Pin)
    {
        case GPIO_PIN_5:
					
            break;
						
        case GPIO_PIN_1:
					
						break;
						
        case GPIO_PIN_2:
     
						break;
											
        case GPIO_PIN_3:
    
            break;
				
				case GPIO_PIN_4:
					
            break;
						
				case GPIO_PIN_0:

            break;
						
					 
    }
}
