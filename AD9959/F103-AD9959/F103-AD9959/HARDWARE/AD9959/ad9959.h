#ifndef __AD9959_H
#define __AD9959_H

#include "sys.h"


#define Crystal  25000000
#define FRE_REF    8.5904963602764   //Ƶ�ʲο�
#define PHA_REF    45.511111111111   //��λ�ο�

#define AD9959_CH0	0x10
#define AD9959_CH1	0x20
#define AD9959_CH2	0x40
#define AD9959_CH3	0x80

//port
#define AD9959_SDIO0    PBout(12)
//#define AD9959_SDIO1    PAout(3)
//#define AD9959_SDIO2    PBout(11)
#define AD9959_SDIO3    PAout(2)

//#define AD9959_P0       PAout(0)
//#define AD9959_P1       PAout(6)
//#define AD9959_P2       PBout(15)
//#define AD9959_P3       PAout(5)



#define AD9959_UP       PBout(14)
#define AD9959_CS       PAout(4)
#define AD9959_SCK      PBout(13)
#define AD9959_RST      PBout(10)
#define AD9959_PWDN     PAout(1)

#define CSR  0x00    
#define FR1  0x01   
#define CFTW0 0x04   
#define CPOW 0x05

void AD9959_Init(void);
void AD9959_Reset(void);
void AD9959_Update(void);
void AD9959_WRrg(u8 reg, u32 data,u8 temp);
void AD9959_Set_Fre(u8 Channel,double Freq);
void AD9959_Set_Amp(u8 Channel,u16 amp);
void AD9959_Set_Pha(u8 Channel,double pha);

#endif

















