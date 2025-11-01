#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "KEY.h"
#include "Timer.h"
#include "Motor.h"
uint16_t Angle =50;
int8_t kp = 0;
int8_t ki = 0;
int8_t kd = 0;
int8_t Motor_Mode =1;

int main()
{
	OLED_Init();
	Motor_Init();
	KEY_Init();
	Timer_Init();
	while(1)
	{
		menu1();
	}
}
