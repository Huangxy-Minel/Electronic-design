#ifndef ADS1274_H
#define ADS1274_H

#include "sys.h"
extern u8 flag;
void ADS1274_Init(void);
void ADS1274_ReadData(void);
float ADS1274_Transform(int data);
#endif
