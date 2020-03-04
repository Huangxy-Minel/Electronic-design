#include "sys.h"
#include "task.h"
static u16 adcinput[800];
float k1 = 19.686373f;
float k2 = 12.665644f;
void InitTask(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LCD_Init();         //初始化LCD接口
	Adc_Init();         //初始化ADC
	POINT_COLOR=BLACK;
}

void ADCTestTask(void)
{
	u8 adcx;
	float temp;
	adcx = Get_Adc_Average(ADC_Channel_0,10);
	LCD_ShowString(30,30,200,16,16,"OriginalADC:");
	LCD_ShowxNum(150,25,adcx,1,16,1);
	temp=(float)adcx*(3.3/4096);
	LCD_ShowString(30,60,200,16,16,"FinalADC:");
	adcx=temp;
	LCD_ShowxNum(150,55,adcx,1,16,1);
	temp-=adcx;
	temp*=1000;
	LCD_ShowxNum(165,55,adcx,3,16,0x80);
}

void FFTTask(void)
{
	u16 i,j,n,k=2,adcx;
	float r,a,Am1,Am2,Sum1,Sum2;
	float f,temp=0;
	for(i=0;i<10;i++)
		idx[i]=0;
	//寻找基波以及谐波
	//寻找基波角标
	fft_outputbuf[1]=0;
	for(i=2;i<=2048;i++)
	{
		if(fft_outputbuf[i]/2048.0>150)
		{
			if(fft_outputbuf[i] > fft_outputbuf[i+1] && fft_outputbuf[i] > fft_outputbuf[i-1])
				idx[1]=i;
			else
			{
				if(fft_outputbuf[i+1] > fft_outputbuf[i-1])
					idx[1]=i+1;
				else
					idx[1]=i-1;
			}
			break;
		}
	}
	  for(i=idx[1]*3;i<=2048;i*=3)//寻找谐波角标
		{
			for(j=i-k-7;j<i+k+7;j++)
			{
				if(fft_outputbuf[j]/2048.0>(50/k) && fft_outputbuf[j]>temp)
				{
					temp=fft_outputbuf[j];
					n=j;
				}
			}
			if(temp/2048.0>(50/k))
			{
				idx[k]=n;
				k++;
				temp=0;
			}
		}
	//计算基波谐波频率并显示
	n=idx[1];
	f=n*Fs/4096.0;
	temp=fft_outputbuf[idx[1]];
			if(1 < fft_outputbuf[idx[1]] && fft_outputbuf[idx[1]] < 4096/2-1 )
			{
				for(i=1;i<=2;i++)
				{
						temp+=fft_outputbuf[idx[1]+i]+fft_outputbuf[idx[1]-i];
				}
			}
			
			f+=(fft_outputbuf[idx[1]+2]-fft_outputbuf[idx[1]-2])*k2/temp + (fft_outputbuf[idx[1]+1]-fft_outputbuf[idx[1]-1])*k1/temp;

	adcx=f;
	LCD_ShowxNum(50,90,f,5,24,1);
	f=(n*Fs-adcx)*100/4096;
	LCD_ShowString(110,93,200,16,16,".");
	LCD_ShowxNum(115,90,f,3,24,0x80);
		
	n=idx[2];
	f=n*Fs/4096.0;
	adcx=f;
	LCD_ShowxNum(50,120,f,5,24,1);
	f=(n*Fs-adcx)*100/4096;
	LCD_ShowString(110,123,200,16,16,".");
	LCD_ShowxNum(115,120,f,3,24,0x80);
	
	n=idx[3];
	f=n*Fs/4096.0;
	adcx=f;
	LCD_ShowxNum(50,150,f,5,24,1);
	f=(n*Fs-adcx)*100/4096;
	LCD_ShowString(110,153,200,16,16,".");
	LCD_ShowxNum(115,150,f,3,24,0x80);
	
	n=idx[4];
	f=n*Fs/4096.0;
	adcx=f;
	LCD_ShowxNum(50,180,f,5,24,1);
	f=(n*Fs-adcx)*100/4096;
	LCD_ShowString(110,183,200,16,16,".");
	LCD_ShowxNum(115,180,f,3,24,0x80);
	
	Sum1=0;
	for(i=0;i<4;i++)
		{Sum1+=fft_outputbuf[idx[1]+i]+fft_outputbuf[idx[1]-i];
		 Sum2+=fft_outputbuf[idx[2]+i]+fft_outputbuf[idx[2]-i];
		}
	Am1=0.0007f*Sum1-2.0604f;
	Am2=0.0007f*Sum2-2.0604f;
	//计算信号幅值
	LCD_ShowxNum(50,270,fft_outputbuf[idx[1]],7,24,0x80);
	LCD_ShowxNum(50,300,idx[1],2,24,0x80);
//	
//	Sum1=fft_outputbuf[idx[1]]+fft_outputbuf[idx[1]+1]+fft_outputbuf[idx[1]-1];
//	Sum2=fft_outputbuf[idx[1]+1]+fft_outputbuf[idx[1]+2]+fft_outputbuf[idx[1]];

//	a=Sum1/Sum2;
//	r=(3-2*a)/(1+a);
//	Am=2*PI*fft_outputbuf[idx[1]]*r*(1-r*r)*(4-r*r)/2/sin(r*PI);
	LCD_ShowxNum(50,330,Am1-70,7,24,0x80);
//	LCD_ShowxNum(50,360,Am1-70,7,24,0x80);
	//判断波形
	//temp=Am/1000000;
	if(Am1<1500)
	{if(Am1>1250)
		LCD_ShowString(70,210,200,16,16,"square signal");
	else if(Am1>950)
		LCD_ShowString(70,210,200,16,16,"sin signal");
	else
		LCD_ShowString(70,210,200,16,16,"triangle signal");}
	else
		if(Am1>2400)
		LCD_ShowString(70,210,200,16,16,"square signal");
	else if(Am1>1900)
		LCD_ShowString(70,210,200,16,16,"sin signal");
	else
		LCD_ShowString(70,210,200,16,16,"triangle signal");
		
}
void LCDTask(void)
{
	u32 i,temp;
	temp=fft_outputbuf[0]/4096;
//	LCD_ShowString(30,60,200,16,16,"MAX_DC:");
//	LCD_ShowxNum(85,55,temp/1000,1,24,1);
//	LCD_ShowString(95,60,200,16,16,".");
//	LCD_ShowxNum(100,55,temp%1000,3,24,0x80);//显示偏置电压数值
//	LCD_ShowString(30,60,200,16,16,":");
//	LCD_ShowString(30,90,200,16,16,"Harmonic Wave_1:");
	for(i=0;i<800;i++)
		adcinput[i]=Get_Adc(ADC_Channel_0)*3300/4096;
//	for(i=0;i<800;i++)
//		{
//			 if(idx[2]*Fs/4096<50)
//			{
//				LCD_ShowString(70,210,200,16,16,"sin signal");
//				break;
//			}
//			 if(idx[3]*Fs/4096<50)
//			{
//				LCD_ShowString(70,210,200,16,16,"square signal");
//				break;
//			}
//			else
//			{
//				LCD_ShowString(70,210,200,16,16,"triangle signal");
//				break;
//			}
//		}
	for(i=0;i<800;i++)
		{
			LCD_DrawLine(fft_outputbuf[i]/15000+20,i+20,20,i+20);
			LCD_DrawLine(adcinput[i]/20+300,i+100,adcinput[i+1]/20+300,i+101);	
		} 
}


