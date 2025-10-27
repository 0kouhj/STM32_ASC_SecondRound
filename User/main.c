#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "menu.h"
#include "key.h"
#include "LED.h"
#include "Timer.h"
#include "Encoder.h"
#include "LED.h"
#include "LED_Control.h"
int8_t led_update_flag=1;
int8_t menu2;
int8_t LED_Speed =5;
int8_t LED_Direct = 1;
int16_t LED_Speed_Count = 0;
float kp =0.1;
float ki =0.2;
float kd =0.3;

int main(void)
{
	Encoder_Init();
	Timer_Init();
	OLED_Init();
	KEY_Init();
	LED_Init();
	while (1)
	{
		menu2 = menu1();
		if (menu2==1) menu2_LED();
		if (menu2==2) menu2_PID();
		if (menu2==3) menu2_Image();
		if (menu2==4) menu2_Angle();
	}
}
