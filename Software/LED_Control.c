#include "stm32f10x.h"
#include "stdint.h"

int8_t Light_Num = 1;

/**
  * @brief  控制LED的速度和方向，每次调用点亮下一个LED
  * @param  LED_Direct 1 正转；0 反转
  */
void LED_Light(int8_t LED_Direct)
{
    if (LED_Direct == 1) // 正向：1→2→3→4→1循环
    {
        switch(Light_Num)
        {
            case 1:
                GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
                GPIO_ResetBits(GPIOB, GPIO_Pin_12);
                Light_Num = 2;
                break;
            case 2:
                GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
                GPIO_ResetBits(GPIOB, GPIO_Pin_13);
                Light_Num = 3;
                break;
            case 3:
                GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);
                GPIO_ResetBits(GPIOB, GPIO_Pin_14);
                Light_Num = 4;
                break;
            case 4:
                GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
                GPIO_ResetBits(GPIOB, GPIO_Pin_15);
                Light_Num = 1;
                break;
            default:
                Light_Num = 1; // 防止异常
                break;
        }
    }
    else  // 反向：4→3→2→1→4循环
    {
        switch(Light_Num)
        {
            case 1:
                GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
                GPIO_ResetBits(GPIOB, GPIO_Pin_12);
                Light_Num = 4;
                break;
            case 2:
                GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
                GPIO_ResetBits(GPIOB, GPIO_Pin_13);
                Light_Num = 1;
                break;
            case 3:
                GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);
                GPIO_ResetBits(GPIOB, GPIO_Pin_14);
                Light_Num = 2;
                break;
            case 4:
                GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
                GPIO_ResetBits(GPIOB, GPIO_Pin_15);
                Light_Num = 3;
                break;
            default:
                Light_Num = 1; // 安全恢复
                break;
        }
    }
}
