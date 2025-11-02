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
int8_t kp = 10;
int8_t ki = 0;
int8_t kd = 0;
int8_t Motor_Mode =1;
int32_t Speed = 0;
uint16_t Motor_Speed_Get_Count=50;

int main()
{
	OLED_Init();
	Motor_Init();
	//KEY_Init();
	//Timer_Init();TIM3,与Encoder重复
	Serial_Init();
	Encoder_Init();
	while(1)
	{
		menu1();
	}
}
