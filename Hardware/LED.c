#include "stm32f10x.h"                  // Device header
#include "LED_Control.h"
#include "KEY.h"
extern int8_t LED_Speed;
extern int8_t LED_Direct;
extern int16_t LED_Speed_Count;

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Key_Tick();
		LED_Speed_Count++;
		if (LED_Speed_Count>=LED_Speed*100)
		{
			LED_Light(LED_Direct);
			LED_Speed_Count=0;
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
