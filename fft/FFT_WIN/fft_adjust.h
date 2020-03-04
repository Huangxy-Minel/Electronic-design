#ifndef _FFT_ADJUST_H
#define _FFT_ADJUST_H
#include "math.h" 
#include "arm_math.h" 

#include "sys.h"

#define K_hann 2.666667        //�������ָ�ϵ��
#define K_rectangle 1          //���δ��ָ�ϵ��
#define K_hamming 2.51635     //�������ָ�ϵ��
#define K_blackman 3.28299   //���������ָ�ϵ��

void fft_adjust_by_power(float * powerinput,float*fftinput,float k,u16 n,float* outdata );


void cmplx_pharse(float* input,float* output,u16 length);

void caculate_powerfactor(float* eleinput,float*volinput,float *pharseinput,float ele_dc,float vol_dc,float *dataout);
#endif
