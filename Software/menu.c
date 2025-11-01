#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "KEY.h"
#include "Motor.h"
extern int8_t kp;
extern int8_t ki;
extern int8_t kd;
extern int8_t Motor_Mode;

void menu1(void)
{
	uint8_t CurLine_Num = 1;
	uint8_t Flag_E =0;
	OLED_ShowString(20,0,"CurMode",OLED_8X16);
	OLED_ShowString(20,16,"KP",OLED_8X16);
	OLED_ShowString(20,32,"KI",OLED_8X16);
	OLED_ShowString(20,48,"KD",OLED_8X16);
	while(1)
	{
		//Motor_SetSpeed(kp);
		OLED_Update();
		OLED_ShowNum(104,0,Motor_Mode,1,OLED_8X16);
		OLED_ShowSignedNum(80,16,kp,3,OLED_8X16);
		OLED_ShowSignedNum(80,32,ki,3,OLED_8X16);
		OLED_ShowSignedNum(80,48,kd,3,OLED_8X16);
		
		for (int j =0;j<4;j++)
		{
			if (j==CurLine_Num-1) OLED_ShowChar(0,j*16,'>',OLED_8X16);
			else OLED_ShowChar(0,j*16,' ',OLED_8X16);
		}
		if (Flag_E)
		{
			OLED_ShowChar(120,(CurLine_Num-1)*16,'E',OLED_8X16);
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
			for (int i = 0;i<3;i++)
			{
				OLED_ShowChar(120,i*16,' ',OLED_8X16);
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
