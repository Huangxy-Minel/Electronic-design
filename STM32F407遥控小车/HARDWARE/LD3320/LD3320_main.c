/************************************************************************************
**	��Ȩ���У�Copyright (c) 2005 - 2010 ICRoute INC.
** Ӳ��˵����STM32f103vet6  8MHZ  �ڲ�ʱ��Ϊ72MHZ 
** 					 LD3320 ��Դ���� 12MHZ  ��ͬ�ľ������޸�LDChip.h �еĶ���ֵ����define CLK_IN  12��
** ���˵�������ж�д�Ĵ�����ʽ�������������ʽ���޸�Reg_RW.c �ļ����ɣ�
** �޸���:  http://shop64790118.taobao.com/
** ʱ�䣺2011.10.15
** 
************************************************************************************/

#include  <stm32f10x_conf.h>
#include  <stm32f10x.h>

#include "LDchip.h"
#include "Reg_RW.h"

#include "delay.h"
#include  "gui_include.h"

/************************************************************************************/
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
/***********************************************************************************/
uint8 nAsrStatus=0;	

#define DEMO_SOUND_SIZE 1235

void LD3320_Init(void);

uint8 RunASR(void);
void ProcessInt0(void);
void LD3320_EXTI_Cfg(void);
void LD3320_NVIC_Cfg(void);

u8 ld3320_exti=0;	 //�жϱ�־�źţ�Ϊ1�Ǵ����жϲ��������²��ò�ѯ��ʽ��
/************************************************************************************/
//	���ʾ�������ǻ���STC10L08XE����������أ�����ִ�еĳ���
//	ʵ���˴������в��ŵĹ���
//  
//  verygood_withHead.mp3(verygood_withoutHead)��һ��MP3��ʽ�������ļ�����������ΪӢ�ĵ���"very good"
//	demosound.h �ж��������� bpDemoSound[]��
//  ��������ݾ��� verygood_withHead.mp3(verygood_withoutHead)�ļ�������
//  �û�������16�����Ķ��������� UltraEdit ����verygood_withHead.mp3�ļ��� bpDemoSound ���������
//
//	��������MP3�ļ��Ĳ��죺  
//	������MP3�ļ�ֻ����û��ID3�ļ�ͷ��MP3�����ݶ���һ���ģ�
//	ID3�ļ�ͷ����LDоƬ���Ӱ�첥��
//  ��Windows�Դ���MediaPlayer����û��ID3ͷ��vertygood_withoutHead.mp3 �󣬻��Զ�����ID3�ļ�ͷ
//  PlayDemoSound_Once/PlayDemoSound_Continue �������ǰ� bpDemoSound�����е��������δ���LD3320оƬ���в���
//
//  ��LD3320оƬ�йصĺ������ܣ�����"�����ֲ�.pdf"������ϸ˵��
//	�뿪���߶���"�����ֲ�.pdf���Ķ�
//	
//	��������ѧϰLD3320��ʼʱ������ֱ�Ӱ������main�����������Լ���Ƭ���б�������
//	
//	��Ȼ���û�Ҫ�����Լ�ʵ�ʵĵ�Ƭ��ȥ�޸� mcu_init ���Լ���Ӧ�Ĺܽ����ӵĶ��壬�ж϶���
/************************************************************************************/

void  LD3320_main(void)
{

	nAsrStatus = LD_ASR_NONE;		//	��ʼ״̬��û������ASR
	while(1)
	{
 	switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
												break;
			case LD_ASR_NONE:

											nAsrStatus=LD_ASR_RUNING;
											if (RunASR()==0)	//	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����
											{		
												nAsrStatus = LD_ASR_ERROR;
											}
											break;

			case LD_ASR_FOUNDOK:

											LD_GetResult();	//	һ��ASRʶ�����̽�����ȥȡASRʶ����				
											nAsrStatus = LD_ASR_NONE;
											break;
			
			case LD_ASR_FOUNDZERO:
			default:
								nAsrStatus = LD_ASR_NONE;
								break;
			}
	
	  if(ld3320_exti !=0) {	/*���ò�ѯ��ʽ�����жϴ���*/

		 ld3320_exti =0;
		 ProcessInt0();		
		}

		  OSTimeDlyHMSM(0,0,0,50);
	
	
	}// while

}
/************************************************************************
���������� 
���ú����� 
��ڲ����� 
���غ����� 
**************************************************************************/
void LD3320_Init(void)
{
	LD3320_GPIO_config();	
	LD3320_EXTI_Cfg();
  LD3320_NVIC_Cfg();
	LD_reset();
}
/************************************************************************
���������� 
���ú����� 
��ڲ����� 
���غ����� 
**************************************************************************/
 void  LD3320_delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	for (j=0;j<5;j++)
	{
		for (g=0;g<uldata;g++)
		{
			delay_us(120);
		}
	}
}

/*********************************************************************
//Ϊ����������ʱ�� ���� *** WARNING L15: MULTIPLE CALL TO SEGMENT
//�����жϺ�������Ҫ���õĺ������¸��Ʋ�����
//�������� Warning L15�����ұ������ں���������ܴ���������Bug
*********************************************************************/
 void  LD3320_delay_2(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	for (j=0;j<5;j++)
	{
		for (g=0;g<uldata;g++)
		{
			delay_us(120);
		}
	}
}


/************************************************************************************/
//	RunASR()����ʵ����һ��������ASR����ʶ������
//	LD_AsrStart() ����ʵ����ASR��ʼ��
//	LD_AsrAddFixed() ����ʵ������ӹؼ����ﵽLD3320оƬ��
//	LD_AsrRun()	����������һ��ASR����ʶ������
//
//	�κ�һ��ASRʶ�����̣�����Ҫ�������˳�򣬴ӳ�ʼ����ʼ����
/************************************************************************************/

uint8 RunASR(void)
{
	uint8 i=0;
	uint8 asrflag=0;
	for (i=0; i<5; i++)			//	��ֹ����Ӳ��ԭ����LD3320оƬ����������������һ������5������ASRʶ������
	{
		LD_AsrStart();			//��ʼ��ASR
		LD3320_delay(100);
		if (LD_AsrAddFixed()==0)	//��ӹؼ����ﵽLD3320оƬ��
		{
			LD_reset();			//	LD3320оƬ�ڲ����ֲ���������������LD3320оƬ
			LD3320_delay(50);			//	���ӳ�ʼ����ʼ����ASRʶ������
			continue;
		}

		LD3320_delay(10);

		if (LD_AsrRun() == 0)
		{
			LD_reset();			//	LD3320оƬ�ڲ����ֲ���������������LD3320оƬ
			LD3320_delay(50);			//	���ӳ�ʼ����ʼ����ASRʶ������
			continue;
		}

		asrflag=1;
		break;					//	ASR���������ɹ����˳���ǰforѭ������ʼ�ȴ�LD3320�ͳ����ж��ź�
	}

	return asrflag;
}

/************************************************************************
���������� 		STM32 Ƕ���ж����� 
���ú����� 
��ڲ����� 
���غ����� 
**************************************************************************/
void LD3320_NVIC_Cfg(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
    
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}
/************************************************************************
���������� 	STM32 �ⲿ�жϺ� IO�����ã������ⲿ�ж���1
���ú����� 
��ڲ����� 
���غ����� 
**************************************************************************/
void LD3320_EXTI_Cfg(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(EXTI_Line1);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_1);

}


/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!= RESET ) 
	{

			
			ld3320_exti=1;//�����жϱ�־ LD3320
						 
				EXTI_ClearFlag(EXTI_Line1);
				EXTI_ClearITPendingBit(EXTI_Line1);

		}
}
