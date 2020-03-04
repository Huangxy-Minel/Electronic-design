#include "fontupd.h"
#include "w25q128.h" 
#include "lcd.h"  
#include "string.h"
#include "delay.h"
#include "usart.h"



//字库区域占用的总扇区数大小(3个字库+unigbk表+字库信息=3238700字节,约占791个W25QXX扇区)
#define FONTSECSIZE	 	791
//字库存放起始地址 
#define FONTINFOADDR 	1024*1024*0 		//字库存放首地址
//定义各个字库的大小
#define UNIGBK         171*1024        //171KB
#define GBK12_FONSIZE  562*1024        //562KB
#define GBK16_FONSIZE  749*1024			   //749KB
#define GBK24_FONSIZE  1684*1024       //1684KB

//用来保存字库基本信息，地址，大小等
_font_info ftinfo;


//初始化字体
//返回值:0,字库完好.
//		 其他,字库丢失
u8 font_init(void)
{		
	u8 t=0;
	W25QXX_Init();  
	while(t<10)//连续读取10次,都是错误,说明确实是有问题,得更新字库了
	{
		t++;
		W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//读出ftinfo结构体数据
		if(ftinfo.fontok==0XAA)break;
		delay_ms(20);
	}
	if(ftinfo.fontok!=0XAA)return 1;
	return 0;		    
}

void ftinfo_init(void)//字库地址初始化
{
		ftinfo.ugbkaddr=FONTINFOADDR+sizeof(ftinfo);
	  ftinfo.ugbksize=UNIGBK;
	
  	ftinfo.f12addr=ftinfo.ugbkaddr+ftinfo.ugbksize;	//UNIGBK之后，紧跟GBK12字库
	  ftinfo.gbk12size=GBK12_FONSIZE;					//GBK12字库大小
	
		ftinfo.f16addr=ftinfo.f12addr+ftinfo.gbk12size;	//GBK12之后，紧跟GBK16字库
		ftinfo.gbk16size=GBK16_FONSIZE;					//GBK16字库大小
	
		ftinfo.f24addr=ftinfo.f16addr+ftinfo.gbk16size;	//GBK16之后，紧跟GBK24字库
	  ftinfo.gkb24size=GBK24_FONSIZE;					//GBK24字库大小
	
}

























