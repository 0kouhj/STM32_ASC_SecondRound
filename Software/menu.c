#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "KEY.h"
#include "Motor.h"
#include "Motor_Control.h"
#include "Vofa.h"
#include "stdlib.h"
extern double kp;
extern double ki;
extern double kd;
extern int8_t Motor_Mode;
extern uint16_t Motor_Speed_Get_Count;


void menu1(void)
{
	uint8_t CurLine_Num = 2;
	uint8_t Flag_E =0;
	OLED_ShowString(9,0,"CurMode",OLED_8X16);
	OLED_ShowString(9,16,"KP",OLED_8X16);
	OLED_ShowString(9,32,"KI",OLED_8X16);
	OLED_ShowString(9,48,"KD",OLED_8X16);
	while(1)
	{
		Serial_PrintToVofa();							//打印串口信息到vofa
		Serial_MotorSpeedControl();						//获取串口命令
		
		OLED_ShowNum(96,0,Motor_Mode,1,OLED_8X16);
		OLED_ShowFloatNum(64,16,kp,1,2,OLED_8X16);
		OLED_ShowFloatNum(64,32,ki,1,2,OLED_8X16);
		OLED_ShowFloatNum(64,48,kd,1,2,OLED_8X16);
		
		OLED_Update();
		
		for (int j =1;j<=4;j++)							//光标这一块
		{
			if (j==CurLine_Num) OLED_ShowChar(0,(j-1)*16,'>',OLED_8X16);
			else OLED_ShowChar(0,(j-1)*16,' ',OLED_8X16);
		}
		if (Flag_E)
		{
			OLED_ShowChar(112,8*(CurLine_Num-1),'E',OLED_8X16);
			switch (CurLine_Num)
			{
				case 1:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_2,KEY_SINGLE)) Motor_Mode = !Motor_Mode;
					break;
				case 2:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_1,KEY_REPEAT)) kp-=0.01;
					if (Key_Check(KEY_2,KEY_SINGLE)||Key_Check(KEY_2,KEY_REPEAT)) kp+=0.01;
					break;
				case 3:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_1,KEY_REPEAT)) ki-=0.01;
					if (Key_Check(KEY_2,KEY_SINGLE)||Key_Check(KEY_2,KEY_REPEAT)) ki+=0.01;
					break;
				case 4:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_1,KEY_REPEAT)) kd-=0.01;
					if (Key_Check(KEY_2,KEY_SINGLE)||Key_Check(KEY_2,KEY_REPEAT)) kd+=0.01;
					break;
			}
			if (Key_Check(KEY_3,KEY_SINGLE)) Flag_E = !Flag_E;
		}
		else
		{
			for (int i = 0;i<4;i++)
			{
				OLED_ShowChar(112,i*8,' ',OLED_8X16);
			}
			if (Key_Check(KEY_1,KEY_SINGLE))
			{
				if (CurLine_Num!=1) CurLine_Num--;
				else CurLine_Num = 4;
			}
			if (Key_Check(KEY_2,KEY_SINGLE))
			{
				if (CurLine_Num!=4) CurLine_Num++;
				else CurLine_Num = 1;
			}
			if (Key_Check(KEY_3,KEY_SINGLE)) Flag_E = !Flag_E;
		}
	}
}
