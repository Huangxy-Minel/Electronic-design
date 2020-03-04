#include "decline.h"
#include "string.h"
#include "delay.h"
#include "usart.h"

extern u8 USART_SE_BUF[10];
u8 c =45,c1=0,c2=45/*c3=16*/;
void set_coff()
{
			if(c<63)
				{
					c2 = c;
					c1 = 0;
				}else
				{
					c2 = 63;
					c1 = c -63;
				}
			//c3 = c/3+c%3;
			USART_SE_BUF[0] = 0x0C;
			USART_SE_BUF[1] = 0x0C;
			USART_SE_BUF[2] = 0x0B;
			USART_SE_BUF[3] = c1;
			USART_SE_BUF[4] = 0x0d;
			USART_SE_BUF[5] = 0x0a;
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_SE_BUF,6,1000);	//发送接收到的数据
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);	//等待发送结束
			delay_ms(10);
			
			USART_SE_BUF[2] = 0x0C;
			USART_SE_BUF[3] = c2;
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_SE_BUF,6,1000);	//发送接收到的数据
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);	//等待发送结束
			delay_ms(10);
		
			/*USART_SE_BUF[2] = 0x0D;
			USART_SE_BUF[3] = c3;
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_SE_BUF,6,1000);	//发送接收到的数据
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);	//等待发送结束*/
			memset(USART_SE_BUF,'\0',6);
			delay_ms(10);
}