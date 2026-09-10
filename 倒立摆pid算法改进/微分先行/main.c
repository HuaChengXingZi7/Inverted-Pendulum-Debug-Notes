#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "TIMER.h"
#include "key.h"
#include "RP.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include "AD.h"
#include "PID.h"

#define CENTER_ANGEL	2064
#define CENTER_RANGE	500

PID_t AngelPID = {
	.Target = CENTER_ANGEL,
	.Kp = 0.350,
	.Ki = 0.006,
	.Kd = 0.307,
	.OutMax = 100,
	.OutMin = -100,

};

PID_t LocationPID = {
	.Target = 0,
	.Kp = 0.314,
	.Ki = 0.003,
	.Kd = 3.590,
	.OutMax = 100,
	.OutMin = -100,

};


uint8_t KeyNum;
uint8_t RunState;
uint16_t Angel;
int16_t Speed,Location;
int main(void)
{
	OLED_Init();
	LED_Init();
	Key_Init();
	RP_Init();
	Motor_Init();
	Encoder_Init();
	Serial_Init();
	AD_Init();
	Timer_Init();
	
	while (1)
	{	
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			RunState = !RunState;	
		}
		
		if(RunState)
		{
			LED_ON();
		
		}
		else
		{
			LED_OFF();
		}
		
//		AngelPID.Kp =RP_GetValue(1) / 4095.0 * 1 ; 
//		AngelPID.Ki =RP_GetValue(2) / 4095.0 * 1 ; 
//		AngelPID.Kd =RP_GetValue(3) / 4095.0 * 1 ; 
		
//		LocationPID.Kp =RP_GetValue(1) / 4095.0 * 1 ; 
//		LocationPID.Ki =RP_GetValue(2) / 4095.0 * 1 ; 
//		LocationPID.Kd =RP_GetValue(3) / 4095.0 * 9 ; 
		
		OLED_Printf(0, 0, OLED_6X8,"Angel");
		OLED_Printf(0, 12, OLED_6X8,"kp:%05.3f",AngelPID.Kp);
		OLED_Printf(0, 20, OLED_6X8,"ki:%05.3f",AngelPID.Ki);
		OLED_Printf(0, 28, OLED_6X8,"kd:%05.3f",AngelPID.Kd);
		OLED_Printf(0, 40, OLED_6X8,"Tar:%04.0f",AngelPID.Target);
		OLED_Printf(0, 48, OLED_6X8,"Act:%04d",Angel);
		OLED_Printf(0, 56, OLED_6X8,"Out:%+04.0f",AngelPID.Out);
		
		OLED_Printf(64, 0, OLED_6X8,"Location");
		OLED_Printf(64, 12, OLED_6X8,"kp:%05.3f",LocationPID.Kp);
		OLED_Printf(64, 20, OLED_6X8,"ki:%05.3f",LocationPID.Ki);
		OLED_Printf(64, 28, OLED_6X8,"kd:%05.3f",LocationPID.Kd);
		OLED_Printf(64, 40, OLED_6X8,"Tar:%+05.0f",LocationPID.Target);
		OLED_Printf(64, 48, OLED_6X8,"Act:%+05d",Location);
		OLED_Printf(64, 56, OLED_6X8,"Out:%+04.0f",LocationPID.Out);
		OLED_Update();
		
	}
}
void TIM1_UP_IRQHandler(void)
{
	static uint16_t Count1, Count2;
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		Key_Tick();
		
		Speed = Encoder_Get();
		Location += Speed;
		Angel = AD_GetValue();
		
		if(!(Angel > CENTER_ANGEL - CENTER_RANGE && Angel < CENTER_ANGEL + CENTER_RANGE))
		{
			RunState = 0;
		}
	
		if(RunState)
		{
			Count1++;
			if(Count1 >= 4)
			{
				Count1 = 0;
				AngelPID.Actual = Angel;
				PID_Update(&AngelPID);
				Motor_SetPWM(AngelPID.Out);
			}
			
			Count2++;
			if(Count2 >= 90)
			{
				Count2 = 0;
				LocationPID.Actual = Location;
				PID_Update(&LocationPID);
				AngelPID.Target = CENTER_ANGEL - LocationPID.Out;
			
			}
			
		}
		else
		{
			Motor_SetPWM(0);
		
		
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
//uint8_t KeyNum;
//int16_t PWM;
//int main()
//{
//	
//	OLED_Init();
//	Key_Init();
//	Motor_Init();
//	Timer_Init();
//	while(1)
//	{
//		KeyNum=Key_GetNum();
//		if(KeyNum==1)
//		{
//			PWM+=10;
//			if(PWM>100) {PWM=100;}				
//		}		
//		if(KeyNum==2)
//		{
//			PWM-=10;
//			if(PWM<-100) {PWM=-100;}
//		}		
//		if(KeyNum==3)
//		{
//			PWM=0;
//		}		

//		Motor_SetPWM(PWM);
//		
//		OLED_Printf(0, 0, OLED_8X16, "PWM:%+04d",PWM);

//		OLED_Update();

//	}

//}
//void TIM1_UP_IRQHandler(void)
//{						
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
//	{

//		Key_Tick();
//		
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	}
//}
