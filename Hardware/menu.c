#include "stm32f10x.h"                  // Device header
#include "stdint.h"
#include "OLED.h"
#include "stdio.h"
#include "KEY.h"
extern int8_t LED_Speed;
extern int8_t LED_Direct;
extern int8_t LED_Speed_Count;
extern float kp;
extern float ki;
extern float kd;
uint8_t PID_Choose_Line =2;
int8_t menu1(void)
{
	OLED_ShowString(1,2,"LED Control");
	OLED_ShowString(2,2,"PID");
	OLED_ShowString(3,2,"Image");
	OLED_ShowString(4,2,"Angel");
	OLED_ShowChar(1,1,'>');
	
	uint8_t menu_cur_line =1;
	while(1)
	{
		if (Key_Check(KEY_1, KEY_SINGLE))
		{
			if (menu_cur_line!=1) menu_cur_line--;
			else menu_cur_line = 4;
		}
		if (Key_Check(KEY_2, KEY_SINGLE))
		{
			if (menu_cur_line!=4) menu_cur_line++;
			else menu_cur_line = 1;
		}
		if (Key_Check(KEY_3, KEY_SINGLE))
		{
			OLED_Clear();
			return menu_cur_line;
		}
		if (Key_Check(KEY_4, KEY_SINGLE))
		{
			OLED_Clear();
			return 0;
		}
		switch(menu_cur_line)
		{
			case 1:
			{
				OLED_ShowChar(1,1,'>');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			case 2:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,'>');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			case 3:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
				OLED_ShowChar(4,1,' ');
			}break;
			case 4:
			{
				OLED_ShowChar(1,1,' ');
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,'>');
			}break;
		}
	}
}
int8_t menu2_LED(void)
{
	uint8_t Choose_Num=0;
	uint8_t menu_cur_line=1;
	OLED_ShowString(1,1,"LED Control");
	OLED_ShowString(2,2,"LED_speed");
	OLED_ShowString(3,2,"LED_dir");
	while(1)
	{
		OLED_ShowNum(2,12,LED_Speed*100,3);
		if (LED_Direct)
		{
			OLED_ShowChar(3,12,'R');
		}
		else 
		{
			OLED_ShowChar(3,12,'L');
		}
		if (Choose_Num>0)
		{
			OLED_ShowChar(1,13,'E');
		}
		if (Key_Check(KEY_1, KEY_SINGLE))
		{
			switch (Choose_Num)
			{
				case 0:
					if (menu_cur_line==1) 
					{
						menu_cur_line=2;
					}
					else
					{
						menu_cur_line=1;
					}
					break;
				case 1:
					switch (LED_Speed)
					{
						case 5:
							LED_Speed=1;
							break;
						case 2:
							LED_Speed=5;
							break;
						case 1:
							LED_Speed=2;
							break;
					}
					LED_Speed_Count = 0;
					break;
				case 2:
					switch (LED_Direct)
					{
						case 1:
							LED_Direct=0;
							break;
						case 0:
							LED_Direct=1;
							break;
					}break;
			}
		}
		if (Key_Check(KEY_2, KEY_SINGLE))
		{
			switch (Choose_Num)
			{
				case 0:
					if (menu_cur_line==1) 
					{
						menu_cur_line=2;
					}
					else
					{
						menu_cur_line=1;
					}
					break;
				case 1:
					switch (LED_Speed)
					{
						case 5:
							LED_Speed=2;
							break;
						case 2:
							LED_Speed=1;
							break;
						case 1:
							LED_Speed=5;
							break;
					}
					LED_Speed_Count = 0;
					break;
				case 2:
					switch (LED_Direct)
					{
						case 1:
							LED_Direct=0;
							break;
						case 0:
							LED_Direct=1;
							break;
					}break;
			}
		}
		if (Key_Check(KEY_3, KEY_SINGLE))
		{
			if (Choose_Num>0)
			{
				Choose_Num=0;
				OLED_ShowChar(1,13,' ');
			}
			else
			{
				Choose_Num = menu_cur_line;
			}
		}
		if (Key_Check(KEY_4, KEY_SINGLE))
		{
			OLED_Clear();
			return 0;
		}
		switch(menu_cur_line)
		{
			case 1:
			{
				OLED_ShowChar(2,1,'>');
				OLED_ShowChar(3,1,' ');
			}break;
			case 2:
			{
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
			}break;
		}
	}
}

int8_t menu2_PID(void)
{
	uint8_t Choose_Num=0;
	//uint8_t keynum;
	char str_kp[4];
	char str_ki[4];
	char str_kd[4];
	OLED_ShowString(1,1,"PID");
	OLED_ShowString(2,2,"kp");
	OLED_ShowString(3,2,"ki");
	OLED_ShowString(4,2,"kd");
	while(1)
	{
		//keynum = Key_GetNum();
		sprintf(str_kp, "%.1f",kp); 
		sprintf(str_ki, "%.1f",ki); 
		sprintf(str_kd, "%.1f",kd); 
		
		OLED_ShowString(2,14,str_kp);
		OLED_ShowString(3,14,str_ki);
		OLED_ShowString(4,14,str_kd);
		if (Choose_Num>0)
		{
			OLED_ShowChar(1,13,'E');
			
			switch (Choose_Num)
			{
				case 2:
					if((Key_Check(KEY_1, KEY_SINGLE) || Key_Check(KEY_1, KEY_REPEAT))&& kp>=0.1) kp-=0.1;
					if(Key_Check(KEY_2, KEY_SINGLE) || Key_Check(KEY_2, KEY_REPEAT)) kp+=0.1;
					break;
				case 3:
					if((Key_Check(KEY_1, KEY_SINGLE) || Key_Check(KEY_1, KEY_REPEAT))&& ki>=0.1) ki-=0.1;
					if(Key_Check(KEY_2, KEY_SINGLE) || Key_Check(KEY_2, KEY_REPEAT)) ki+=0.1;
					break;
				case 4:
					if((Key_Check(KEY_1, KEY_SINGLE) || Key_Check(KEY_1, KEY_REPEAT))&& kd>=0.1) kd-=0.1;
					if(Key_Check(KEY_2, KEY_SINGLE) || Key_Check(KEY_2, KEY_REPEAT)) kd+=0.1;
					break;
			}
		}
		else
		{
			if (Key_Check(KEY_1, KEY_SINGLE))
			{
				if (PID_Choose_Line!=2) PID_Choose_Line--;
				else PID_Choose_Line = 4;
			}
			if (Key_Check(KEY_2, KEY_SINGLE))
			{
				if (PID_Choose_Line!=4) PID_Choose_Line++;
				else PID_Choose_Line = 2;
			}
		}
		
		if (Key_Check(KEY_3, KEY_SINGLE))
		{
			if (Choose_Num>0)
			{
				Choose_Num=0;
				OLED_ShowChar(1,13,' ');
			}
			else
			{
				Choose_Num = PID_Choose_Line;
			}
		}
		if (Key_Check(KEY_4, KEY_SINGLE)&&Choose_Num==0)
		{
			OLED_Clear();
			return 0;
		}
		switch(PID_Choose_Line)
		{
			case 2:
			{
				OLED_ShowChar(2,1,'>');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,' ');
			}break;
			case 3:
			{
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,'>');
				OLED_ShowChar(4,1,' ');
			}break;
			case 4:
			{
				OLED_ShowChar(2,1,' ');
				OLED_ShowChar(3,1,' ');
				OLED_ShowChar(4,1,'>');
			}break;
		}
	}
}

int8_t menu2_Image(void)
{
	OLED_ShowString(1,1,"Image");
	OLED_ShowString(2,1,">Image");
	while (1)
	{
		if (Key_Check(KEY_4, KEY_SINGLE))
		{
			OLED_Clear();
			return 0;
		}
	}
}

int8_t menu2_Angle(void)
{
	OLED_ShowString(1,1,"Angle");
	OLED_ShowString(2,1,">Angle");
	while (1)
	{
		if (Key_Check(KEY_4, KEY_SINGLE))
		{
			OLED_Clear();
			return 0;
		}
	}
}
