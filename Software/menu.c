#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "KEY.h"
#include "Motor.h"
#include "Serial.h"

extern int8_t kp;
extern int8_t ki;
extern int8_t kd;
extern int8_t Motor_Mode;

void menu1(void)
{
	uint8_t CurLine_Num = 1;
	uint8_t Flag_E =0;
	OLED_ShowString(1,2,"CurMode");
	OLED_ShowString(2,2,"KP");
	OLED_ShowString(3,2,"KI");
	OLED_ShowString(4,2,"KD");
	while(1)
	{
		//Motor_SetSpeed(kp);
		Serial_SendByte(kp);
		OLED_ShowNum(1,14,Motor_Mode,1);
		OLED_ShowSignedNum(2,6,kp,3);
		OLED_ShowSignedNum(3,6,ki,3);
		OLED_ShowSignedNum(4,6,kd,3);
		
		for (int j =1;j<=4;j++)
		{
			if (j==CurLine_Num) OLED_ShowChar(j,1,'>');
			else OLED_ShowChar(j,1,' ');
		}
		if (Flag_E)
		{
			OLED_ShowChar(CurLine_Num,15,'E');
			switch (CurLine_Num)
			{
				case 1:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_2,KEY_SINGLE)) Motor_Mode = !Motor_Mode;
					break;
				case 2:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_1,KEY_REPEAT)) kp--;
					if (Key_Check(KEY_2,KEY_SINGLE)||Key_Check(KEY_2,KEY_REPEAT)) kp++;
					break;
				case 3:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_1,KEY_REPEAT)) ki--;
					if (Key_Check(KEY_2,KEY_SINGLE)||Key_Check(KEY_2,KEY_REPEAT)) ki++;
					break;
				case 4:
					if (Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_1,KEY_REPEAT)) kd--;
					if (Key_Check(KEY_2,KEY_SINGLE)||Key_Check(KEY_2,KEY_REPEAT)) kd++;
					break;
			}
			if (Key_Check(KEY_3,KEY_SINGLE)) Flag_E = !Flag_E;
		}
		else
		{
			for (int i = 1;i<=4;i++)
			{
				OLED_ShowChar(i,15,' ');
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
