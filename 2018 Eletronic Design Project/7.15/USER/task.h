#ifndef __TASK_H
#define __TASK_H	
#include "sys.h" 
#include "delay.h"  
#include "usart.h"  
#include "lcd.h"
#include "math.h" 
#include "arm_math.h" 
#include "adc.h"
#include "control.h"
#define FFT_LENGTH 4096
extern float fft_outputbuf[FFT_LENGTH];
extern float fft_inputbuf[FFT_LENGTH*2];
extern u16 Fs;
extern u16 idx[10];
void InitTask(void);
void ADCTestTask(void);
void FFTTask(void);
void LCDTask(void);
#endif 
