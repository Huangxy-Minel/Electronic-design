#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
extern u8 state;//ȫ�ֱ�����״̬�б�
extern u32 adc_ch;
extern u8 adc_state;
//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��
        
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;               //PC13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;				//����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    

    
    //�ж���0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���1
    HAL_NVIC_SetPriority(EXTI1_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);             //ʹ���ж���1
    
    //�ж���2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //ʹ���ж���2
		
		 //�ж���3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,3);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //ʹ���ж���3
		
		//�ж���4
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,4);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ4
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);             //ʹ���ж���4
    
    //�ж���5
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,5);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ5
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);         //ʹ���ж���5  
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);   //�����жϴ����ú���
}

void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);   //�����жϴ����ú���
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);   //�����жϴ����ú���
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);   //�����жϴ����ú���
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);   //�����жϴ����ú���
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);  //�����жϴ����ú���
}

//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static u8 led0sta=1,led1sta=1;
    delay_ms(100);      //����
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
