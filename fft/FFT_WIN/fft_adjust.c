#include "fft_adjust.h"
#include "main.h"
extern float FFT_1024_INPUT[];
//奇次谐波位置
extern const  u16 Odd_position[];
//偶次谐波位置
extern const  u16 Even_position[];
//nuttall系数
const float nuttall[4]=
{
	0.338946,-0.481973,0.161054,-0.018027
};

void fft_adjust_by_power(float * powerinput,float*fftinput,float k,u16 n,float* outdata )
{
	float K=k;
	float Powersum,power[20];
	float f;//归一化频率
	float angle;
	angle=atan2(fftinput[2*n+1],fftinput[2*n]);
	//计算功率 和相位
	power[0]=pow(powerinput[n-2],2);
	power[1]=pow(powerinput[n-1],2);
	power[2]=pow(powerinput[n],2);
	power[3]=pow(powerinput[n+1],2);
	power[4]=pow(powerinput[n+2],2);
	power[5]=pow(powerinput[n-3],2);
	power[6]=pow(powerinput[n+3],2);
	
  Powersum=power[0]+power[1]+power[2]+power[3]+power[4]+power[5]+power[6];
  f=((n-2)*power[0]+(n-1)*power[1]+n*power[2]+(n+1)*power[3]+(n+2)*power[4]+(n+3)*power[6]+(n-3)*power[5])/Powersum;
	Powersum=sqrt(Powersum*K);
	outdata[0]=Powersum;
	outdata[1]=angle+PI*((float)n-f);

	
	outdata[1]=fmod(outdata[1],2*PI);

	if(outdata[1]>PI) outdata[1]-=2*PI;
	else if(outdata[1]<-PI) outdata[1]+=2*PI;
  
	
}




void cmplx_pharse(float* input,float* output,u16 length)
{
	u16 i;
	for(i=0;i<length;i++)
	{
		output[i]=atan2(input[2*i+1],input[2*i]);
	}
		
}


void caculate_powerfactor(float* eleinput,float*volinput,float *pharseinput,float ele_dc,float vol_dc,float *dataout)
{
	float p;
	float s;
	float i2;
	float v2;
	float power;
	float I=0;
	float U=0;
	float THD=0;
	u16 i;
	float K=1024;
	for(i=0;i<HARMONIC;i++)
	{
		p+=eleinput[2*i]*volinput[2*i]*arm_cos_f32(pharseinput[i])*0.5;
		v2+=volinput[i*2]*volinput[2*i]*0.5;
		i2+=eleinput[2*i]*eleinput[2*i]*0.5;
	}
	THD=(sqrt(v2-pow(volinput[0],2)*0.5))/volinput[0]*sqrt(2);//畸变率
	I=sqrt(i2+ele_dc*ele_dc)/1028000;//电流有效值
	
	U=sqrt(v2)/10000-10;//电压有效值
	if(U<0)U=0;
	p=U*I;
	s=sqrt((v2+vol_dc*vol_dc)*(ele_dc*ele_dc+i2));
	
	power=p/s;//功率因数
  dataout[0]=p;
	dataout[1]=power;
	dataout[2]=I;
	dataout[3]=U;
	dataout[4]=THD;
	
}

