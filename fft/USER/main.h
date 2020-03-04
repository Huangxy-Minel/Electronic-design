#ifndef _MAIN_H
#define _MAIN_H
#include "sys.h"
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

#include "lcd.h"
#include "spi_flash.h"
#include "w25q128.h"
#include "text.h"
#include "fontupd.h"
#include "win.h"

#include "adc.h"


#include "math.h" 
#include "arm_math.h"  
#include "fft_win.h"
#include "fft_adjust.h"

#define FFT_LENGTH  4096 //��֧��4096���ϵĳ���
#define IFFT_FLAG 0 //���任
#define PI 3.14159265358979f
#define Fs 1000.0f //Sampling Rate: 1kHz
#define ONE_POINT_F 0.6103f     //Ƶ�ʷֱ���

extern float FFT_INPUT[FFT_LENGTH];
extern float FFT_OUTPUT[FFT_LENGTH*2];
extern float FFT_MAGNITUDE[FFT_LENGTH];

#endif
