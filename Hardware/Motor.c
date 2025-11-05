#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * 函    数：直流电机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	PWM_Init();													//初始化直流电机的底层PWM
}

/**
  * 函    数：直流电机设置速度
  * 参    数：Speed 要设置的速度，范围：-100~100
  * 返 回 值：无
  */
void Motor_SetSpeed_1(int8_t Speed)
{
    if (Speed > 100) Speed = 100;
    if (Speed < -100) Speed = -100;

    if (Speed >= 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);
        PWM_SetCompare3(Speed);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        GPIO_SetBits(GPIOB, GPIO_Pin_13);
        PWM_SetCompare3(-Speed);
    }
}

void Motor_SetSpeed_2(int8_t Speed)
{
    if (Speed > 100) Speed = 100;
    if (Speed < -100) Speed = -100;

    if (Speed >= 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_14);
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);
        PWM_SetCompare4(Speed);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);
        GPIO_SetBits(GPIOB, GPIO_Pin_15);
        PWM_SetCompare4(-Speed);
    }
}

