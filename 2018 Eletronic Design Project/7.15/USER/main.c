#include "sys.h"
#include "task.h"
float fft_inputbuf[FFT_LENGTH*2];	//FFT��������
float fft_outputbuf[FFT_LENGTH];	//FFT�������
float xielv[10];
u16 idx[10];
u16 Fs = 64500;   //����Ƶ��
int main(void)
{
	u16 i;
	InitTask();
	arm_cfft_radix4_instance_f32 scfft;//��ʼ��FFT�㷨
	arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);
	while(1)
	{
		for(i=0;i<4096;i++)
		{
			fft_inputbuf[i*2]=Get_Adc(ADC_Channel_0)*3300.f/4096.f;
			fft_inputbuf[i*2+1]=0;
			delay_us(7);
		}
		//�Ӵ�
		for(i=0;i<4096;i++)
			fft_inputbuf[i*2]*=0.5f*(1-cos(2*PI*((float)i)/(4096-1)));
		
		arm_cfft_radix4_f32(&scfft,fft_inputbuf);
		arm_cmplx_mag_f32(fft_inputbuf,fft_outputbuf,FFT_LENGTH);//��FFT	
		FFTTask();
		LCDTask();
		//ADCTestTask();
		delay_ms(500);
		LCD_Clear(WHITE);

	}
}
