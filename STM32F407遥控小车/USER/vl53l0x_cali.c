#include "vl53l0x_cali.h"

//////////////////////////////////////////////////////////////////////////////////	 
//?????????,??????,??????????
//ALIENTEK ???STM32F407???
//VL53L0X-???? ????	   
//????@ALIENTEK
//????:www.openedv.com
//????:2017/7/1
//??:V1.0
//????,?????
//Copyright(C) ????????????? 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

_vl53l0x_adjust Vl53l0x_adjust; //????24c02????(?????????????24c02)
_vl53l0x_adjust Vl53l0x_data;   //????24c02????(?????????24C02????)

#define adjust_num 5//??????

//VL53L0X????
//dev:??I2C?????
VL53L0X_Error vl53l0x_adjust(VL53L0X_Dev_t *dev)
{
	
	VL53L0X_DeviceError Status = VL53L0X_ERROR_NONE;
	uint32_t refSpadCount = 7;
	uint8_t  isApertureSpads = 0;
	uint32_t XTalkCalDistance = 100;
	uint32_t XTalkCompensationRateMegaCps;
	uint32_t CalDistanceMilliMeter = 100<<16;
	int32_t  OffsetMicroMeter = 30000;
	uint8_t VhvSettings = 23;
	uint8_t PhaseCal = 1;
	u8 i=0;

	VL53L0X_StaticInit(dev);//??????,?????????
    LED1=0;
	//SPADS??----------------------------
	spads:
	delay_ms(10);
	printf("The SPADS Calibration Start...\r\n");
	Status = VL53L0X_PerformRefSpadManagement(dev,&refSpadCount,&isApertureSpads);//????Spad??
	if(Status == VL53L0X_ERROR_NONE)
	{
	    printf("refSpadCount = %d\r\n",refSpadCount);
	    Vl53l0x_adjust.refSpadCount = refSpadCount;
	    printf("isApertureSpads = %d\r\n",isApertureSpads);	
	    Vl53l0x_adjust.isApertureSpads = isApertureSpads;
        printf("The SPADS Calibration Finish...\r\n\r\n");		
	    i=0;
	}
	else
	{
	    i++;
	    if(i==adjust_num) return Status;
	    printf("SPADS Calibration Error,Restart this step\r\n");
	    goto spads;
	}
	//??????---------------------------------------------------
	ref:
	delay_ms(10);
	printf("The Ref Calibration Start...\r\n");
	Status = VL53L0X_PerformRefCalibration(dev,&VhvSettings,&PhaseCal);//Ref????
	if(Status == VL53L0X_ERROR_NONE)
	{
		printf("VhvSettings = %d\r\n",VhvSettings);
		Vl53l0x_adjust.VhvSettings = VhvSettings;
		printf("PhaseCal = %d\r\n",PhaseCal);
		Vl53l0x_adjust.PhaseCal = PhaseCal;
		printf("The Ref Calibration Finish...\r\n\r\n");
		i=0;
	}
	else
	{
		i++;
		if(i==adjust_num) return Status;
		printf("Ref Calibration Error,Restart this step\r\n");
		goto ref;
	}
	//????------------------------------------------------
	offset:
	delay_ms(10);
	printf("Offset Calibration:need a white target,in black space,and the distance keep 100mm!\r\n");
	printf("The Offset Calibration Start...\r\n");
	
	Status = VL53L0X_PerformOffsetCalibration(dev,CalDistanceMilliMeter,&OffsetMicroMeter);//????
	if(Status == VL53L0X_ERROR_NONE)
	{
		printf("CalDistanceMilliMeter = %d mm\r\n",CalDistanceMilliMeter);
		Vl53l0x_adjust.CalDistanceMilliMeter = CalDistanceMilliMeter;
		printf("OffsetMicroMeter = %d mm\r\n",OffsetMicroMeter);	
		Vl53l0x_adjust.OffsetMicroMeter = OffsetMicroMeter;
		printf("The Offset Calibration Finish...\r\n\r\n");
		i=0;
	}
	else
	{
		i++;
		if(i==adjust_num) return Status;
		printf("Offset Calibration Error,Restart this step\r\n");
		goto offset;
	}
	//????-----------------------------------------------------
	xtalk:
	delay_ms(20);
	printf("Cross Talk Calibration:need a grey target\r\n");
	printf("The Cross Talk Calibration Start...\r\n");	
	Status = VL53L0X_PerformXTalkCalibration(dev,XTalkCalDistance,&XTalkCompensationRateMegaCps);//????
	if(Status == VL53L0X_ERROR_NONE)
	{
		printf("XTalkCalDistance = %d mm\r\n",XTalkCalDistance);
		Vl53l0x_adjust.XTalkCalDistance = XTalkCalDistance;
		printf("XTalkCompensationRateMegaCps = %d\r\n",XTalkCompensationRateMegaCps);	
		Vl53l0x_adjust.XTalkCompensationRateMegaCps = XTalkCompensationRateMegaCps;
		printf("The Cross Talk Calibration Finish...\r\n\r\n");
		i=0;
	}
	else
	{
		i++;
		if(i==adjust_num) return Status;
		printf("Cross Talk Calibration Error,Restart this step\r\n");
		goto xtalk;
	}
	LED1=1;
	printf("All the Calibration has Finished!\r\n");
	printf("Calibration is successful!!\r\n");

	Vl53l0x_adjust.adjustok = 0xAA;//????
	AT24CXX_Write(0,(u8*)&Vl53l0x_adjust,sizeof(_vl53l0x_adjust));//????????24c02
	memcpy(&Vl53l0x_data,&Vl53l0x_adjust,sizeof(_vl53l0x_adjust));
	return Status;
}

//vl53l0x????
//dev:??I2C?????
void vl53l0x_calibration_test(VL53L0X_Dev_t *dev)
{  
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	u8 key=0;
	u8 i=0;
	
	LCD_Fill(30,170,320,300,WHITE);
	POINT_COLOR=RED;//??????? 
	LCD_ShowString(30,170,300,16,16,"need a white target,and ");
	LCD_ShowString(30,190,250,16,16,"the distance keep 100mm.");
	POINT_COLOR=BLUE;//??????? 
	LCD_ShowString(30,220,200,16,16,"KEY_UP: Return menu");
	LCD_ShowString(30,240,200,16,16,"KEY1:   Calibration");
	while(1)
	{
		key = KEY_Scan(0);
		if(key==KEY1_PRES)
		{
			POINT_COLOR=RED;//??????? 
			LCD_ShowString(30,260,200,16,16,"Start calibration...");
			status = vl53l0x_adjust(dev);//????
			if(status!=VL53L0X_ERROR_NONE)//????
			{ 
				 printf("Calibration is error!!\r\n");
				 i=3;
				 while(i--)
				 {
					  delay_ms(500);
					  LCD_ShowString(30,260,200,16,16,"                    ");
					  delay_ms(500);
					  LCD_ShowString(30,260,200,16,16,"Calibration is error");
				 }
			}
			else
				 LCD_ShowString(30,260,200,16,16,"Calibration is complete!");
			delay_ms(500);

			break;
				
		 }
		 else if(key==WKUP_PRES)
		 {
			 LED1=1;
			 break;//??????
		 }		 
		 delay_ms(200);
		 LED0=!LED0;
		
	}
		
}
