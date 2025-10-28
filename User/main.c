#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "KEY.h"
#include "Timer.h"
#include "Motor.h"
uint16_t Angle =50;


int main()
{
	OLED_Init();
	Motor_Init();
	OLED_ShowString(1,1,"Speed=");
	Motor_SetSpeed(50);
	while(1)
	{
		
	}
}
