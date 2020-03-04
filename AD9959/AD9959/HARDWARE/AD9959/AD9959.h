#ifndef __AD9959_H 
#define __AD9959_H 
#include "sys.h"

#define CSR_ADD   0x00   //CSR ͨ��ѡ��Ĵ���
#define FR1_ADD   0x01   //FR1 ����ѡ��Ĵ���1
#define FR2_ADD   0x02   //FR2 ����ѡ��Ĵ���2
#define CFR_ADD   0x03   //CFR ͨ�����ܼĴ���
#define CFTW0_ADD 0x04   //CTW0 ͨ��Ƶ��ת���ּĴ���
#define CPOW0_ADD 0x05   //CPW0 ͨ����λת���ּĴ���
#define ACR_ADD   0x06   //ACR ���ȿ��ƼĴ���
#define LSRR_ADD  0x07   //LSR ͨ������ɨ��Ĵ���
#define RDW_ADD   0x08   //RDW ͨ����������ɨ��Ĵ���
#define FDW_ADD   0x09   //FDW ͨ����������ɨ��Ĵ���

#define AD9959_CH0	0x10
#define AD9959_CH1	0x20
#define AD9959_CH2	0x40
#define AD9959_CH3	0x80

#define CS(n)           (n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_RESET))
#define SCLK(n)					(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET))
#define UPDATE(n)  			(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_RESET))
#define PS0(n)  				(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET))
#define PS1(n) 					(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET))
#define PS2(n) 					(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,GPIO_PIN_RESET))
#define PS3(n) 					(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET))
#define SDIO0(n)     		(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_RESET))
#define SDIO1(n) 				(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET))
#define SDIO2(n) 				(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_RESET))
#define SDIO3(n)  			(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_RESET))
//#define AD9959_PWR	PAout(9)
#define Reset(n) 				(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET))

/**
 * ???????
 */
#define AD9959SYS_CLK 500 //��λM��ȡֵ25��������25-500

void Init_AD9959(void);
void InitIO_9959(void);
void InitReset(void);
void IO_Update(void);
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp);
void Write_frequence(u8 Channel,u32 Freq);
void Write_Amplitude(u8 Channel, u16 Ampli);
void Write_Phase(u8 Channel,u16 Phase);

#endif /* AD9959_H */ 
