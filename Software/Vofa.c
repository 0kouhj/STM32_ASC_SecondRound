#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
extern int32_t Set_Speed_1;
extern int32_t Set_Speed_2;
extern int32_t Get_Speed_1;
extern int32_t Get_Speed_2;
extern int16_t Set_Position_1;
extern int16_t Set_Position_2;
extern int16_t Get_Position_1;
extern int16_t Get_Position_2;
extern int8_t Motor_Mode;
void Serial_PrintToVofa(void)
{
	if (Motor_Mode == 0)
	{
		Serial_Printf("%d,%d,%d,%d\n",Set_Speed_1,Get_Speed_1,Set_Speed_2,Get_Speed_2);
	}
	else
	{
		Serial_Printf("%d,%d\n",Get_Position_1,Get_Position_2);
	}
}
