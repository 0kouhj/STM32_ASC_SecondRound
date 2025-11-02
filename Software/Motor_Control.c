#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Motor.h"
#include "string.h"
extern int32_t Speed;
void Serial_MotorSpeedControl(void)
{
    if (Serial_RxFlag == 1)
    {
        if (sscanf(Serial_RxPacket, "Speed%d", &Speed) == 1)
        {
			Motor_SetSpeed(Speed);
        }
        else 
        {
            Serial_Printf("NO - Invalid format\r\n");
        }
        Serial_RxFlag = 0;
    }
}
