#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
extern int32_t Speed;
void Serial_PrintToVofa(void)
{
	Serial_Printf("%d,%d\n",Speed,(int)Encoder_Get());
}
