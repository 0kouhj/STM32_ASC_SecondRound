#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "KEY.h"
#include "Timer.h"
#include "Motor.h"
#include "Serial.h"
#include "Encoder.h"
uint16_t Angle =50;
int8_t Motor_Mode =0;//0,1为速度任务,不是0 or 1为位置任务
int32_t Set_Speed_1 = 0;
int32_t Get_Speed_1 = 0;
int32_t Set_Speed_2 = 0;
int32_t Get_Speed_2 = 0;
uint16_t Motor_Speed_Get_Count=2;

int main()
{
	OLED_Init();
	Motor_Init();
	KEY_Init();
	Timer_Init();
	Serial_Init();
	Encoder_Init();
	while(1)
	{
		menu1();
	}
}
