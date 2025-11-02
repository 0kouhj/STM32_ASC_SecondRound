#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Motor.h"
#include "string.h"
void Serial_MotorSpeedControl(void)
{
    if (Serial_RxFlag == 1)
    {
        int32_t speed = 0;
        if (sscanf(Serial_RxPacket, "Speed%d", &speed) == 1)
        {
            Serial_Printf("Motor_Speed_Set: %d\r\n", speed);
			Motor_SetSpeed(speed);
        }
        else 
        {
            Serial_Printf("NO - Invalid format\r\n");
        }
        Serial_RxFlag = 0;
    }
}
