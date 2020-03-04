#include "fontupd.h"
#include "w25q128.h" 
#include "lcd.h"  
#include "string.h"
#include "delay.h"
#include "usart.h"



//�ֿ�����ռ�õ�����������С(3���ֿ�+unigbk��+�ֿ���Ϣ=3238700�ֽ�,Լռ791��W25QXX����)
#define FONTSECSIZE	 	791
//�ֿ�����ʼ��ַ 
#define FONTINFOADDR 	1024*1024*0 		//�ֿ����׵�ַ
//��������ֿ�Ĵ�С
#define UNIGBK         171*1024        //171KB
#define GBK12_FONSIZE  562*1024        //562KB
#define GBK16_FONSIZE  749*1024			   //749KB
#define GBK24_FONSIZE  1684*1024       //1684KB

//���������ֿ������Ϣ����ַ����С��
_font_info ftinfo;


//��ʼ������
//����ֵ:0,�ֿ����.
//		 ����,�ֿⶪʧ
u8 font_init(void)
{		
	u8 t=0;
	W25QXX_Init();  
	while(t<10)//������ȡ10��,���Ǵ���,˵��ȷʵ��������,�ø����ֿ���
	{
		t++;
		W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//����ftinfo�ṹ������
		if(ftinfo.fontok==0XAA)break;
		delay_ms(20);
	}
	if(ftinfo.fontok!=0XAA)return 1;
	return 0;		    
}

void ftinfo_init(void)//�ֿ��ַ��ʼ��
{
		ftinfo.ugbkaddr=FONTINFOADDR+sizeof(ftinfo);
	  ftinfo.ugbksize=UNIGBK;
	
  	ftinfo.f12addr=ftinfo.ugbkaddr+ftinfo.ugbksize;	//UNIGBK֮�󣬽���GBK12�ֿ�
	  ftinfo.gbk12size=GBK12_FONSIZE;					//GBK12�ֿ��С
	
		ftinfo.f16addr=ftinfo.f12addr+ftinfo.gbk12size;	//GBK12֮�󣬽���GBK16�ֿ�
		ftinfo.gbk16size=GBK16_FONSIZE;					//GBK16�ֿ��С
	
		ftinfo.f24addr=ftinfo.f16addr+ftinfo.gbk16size;	//GBK16֮�󣬽���GBK24�ֿ�
	  ftinfo.gkb24size=GBK24_FONSIZE;					//GBK24�ֿ��С
	
}

























