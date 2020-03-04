#include "sys.h"

#define D0 PAout(0)
#define D1 PAout(1)
#define D2 PAout(2)
#define D3 PAout(3)
#define D4 PAout(4)
#define D5 PAout(5)
#define D6 PAout(6)
#define D7 PAout(7)

#define A0 PBout(3)
#define A1 PBout(4)
#define A2 PBout(5)
#define A3 PBout(6)
#define A4 PBout(7)
#define A5 PBout(8)


#define MRST PBout(0)

#define WR PBout(12)

#define RD PBout(13)

//#define SK PBout(15)

//#define FSK PCout(14)

#define UD PAout(15)

extern unsigned long Frequence[2];

void pin_Init(void);
void Init_9854(void);
void write_9854(unsigned char address,unsigned char data);
void write_fre(int channel,unsigned long x);
void write_amp(int channel,unsigned int Ampli);
