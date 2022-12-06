#include "stm32f10x.h"

uint16_t button=0;

void gpioConfig()
{
	GPIO_InitTypeDef  GPIOInitStrucutre;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIOInitStrucutre.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStrucutre.GPIO_Pin=GPIO_Pin_5;
	GPIOInitStrucutre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStrucutre);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOInitStrucutre.GPIO_Mode=GPIO_Mode_IPD;
	GPIOInitStrucutre.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIOInitStrucutre);
	
}

int main()
{
gpioConfig();
	while(1)
	{
		button=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
		if(button==0)
		{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		}
		else{GPIO_ResetBits(GPIOB,GPIO_Pin_5);}
		
	}

	


}
