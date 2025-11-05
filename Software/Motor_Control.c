#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Motor.h"
#include "string.h"
#include "Encoder.h"
#include "KEY.h"

extern int8_t Motor_Mode;
extern int32_t Set_Speed_1;
extern int32_t Get_Speed_1;
extern int32_t Set_Speed_2;
extern int32_t Get_Speed_2;
extern uint16_t Motor_Speed_Get_Count;

double kp = 0.3;
double ki = 0.2;
double kd = 0;
double kp_ = 0.3;
double ki_ = 0;
double kd_ = 0;
float Error0,Error1,Error2,ErrorInt;
float Error0_,Error1_,Error2_,ErrorInt_;
float Out;

int16_t Set_Position_1;
int16_t Get_Position_1;
int16_t Set_Position_2;
int16_t Get_Position_2;

void Serial_MotorSpeedControl(void)
{
    if (Serial_RxFlag == 1)
    {
        if (sscanf(Serial_RxPacket, "Speed_L%d", &Set_Speed_1) == 1);
        else if (sscanf(Serial_RxPacket, "Position_L%hd", &Set_Position_1) == 1);
        else if (sscanf(Serial_RxPacket, "Speed_R%d", &Set_Speed_2) == 1);
        else if (sscanf(Serial_RxPacket, "Position_R%hd", &Set_Position_2) == 1);
		Error0 = Error1 = Error2 = ErrorInt = Out = 0;
        Serial_RxFlag = 0;
    }
}


void TIM1_UP_IRQHandler(void)  // 修正中断函数名
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
		Key_Tick();
        static uint16_t Count;
        Count++;
        if (Count >= Motor_Speed_Get_Count)
        {    
            Count = 0;  // 清零计数器

			//PID Control
			if (Motor_Mode==0)//Speed
			{
				Get_Speed_1 = Encoder_Get_1();
				Get_Speed_2 = Encoder_Get_2();
				
				Error1 = Error0;
				Error0 = Set_Speed_1 - Get_Speed_1;
				
				ErrorInt += Error0;
				
				Out = kp * Error0 + ki * ErrorInt +kd * (Error0-Error1);
				if (Out >100) {Out=100;}
				if (Out <-100) {Out=-100;}
				
				Motor_SetSpeed_1(Out);
			}
//			else if (Motor_Mode==1)//Speed
//			{
//				Get_Speed_1 = Encoder_Get_1();
//				
//				Error2 = Error1;
//				Error1 = Error0;
//				Error0 = Set_Speed_1 - Get_Speed_1;
//				
//				ErrorInt += Error0;
//				
//				Out += kp * (Error0 - Error1) + ki * Error0 + kd * (Error0 - 2 * Error1 + Error2);
//				if (Out >100) {Out=100;}
//				if (Out <-100) {Out=-100;}
//				
//				Motor_SetSpeed_1(Out);
//			}
			else // Position Sync Mode
			{
				Get_Position_1 += -Encoder_Get_1();   
				Get_Position_2 += Encoder_Get_2();  
				
				Set_Position_2 = Get_Position_1;    // 同步目标 = 主电机位置

				Error1_ = Error0_;
				Error0_ = Set_Position_2 - Get_Position_2;
				ErrorInt_ += Error0_;

				Out = kp_ * Error0_ + ki_ * ErrorInt_ + kd_ * (Error0_ - Error1_);

				if (ErrorInt > 1000)  ErrorInt_ = 1000;
				if (ErrorInt < -1000) ErrorInt_ = -1000;
				if (Out > 100)  Out = 100;
				if (Out < -100) Out = -100;
				Motor_SetSpeed_2(Out);
			}
        }
		// 积分项限幅
		if (ErrorInt > 1000)  ErrorInt = 1000;
		if (ErrorInt < -1000) ErrorInt = -1000;

		// 输出限幅
		if (Out > 100)  Out = 100;
		if (Out < -100) Out = -100;

        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}
