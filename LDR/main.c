#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adcValue=0;
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStrucutre;
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//LED CONFIG
	GPIOInitStrucutre.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStrucutre.GPIO_Pin=GPIO_Pin_1;
	GPIOInitStrucutre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOInitStrucutre);
	
	//LDR CONFIG
	GPIOInitStrucutre.GPIO_Mode=GPIO_Mode_AIN;
	GPIOInitStrucutre.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIOInitStrucutre);
	
	
}

void adcConfig(){
	ADC_InitTypeDef ADCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADCInitStructure.ADC_ContinuousConvMode=ENABLE;
	ADCInitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADCInitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADCInitStructure.ADC_Mode=ADC_Mode_Independent;
	ADCInitStructure.ADC_NbrOfChannel=1;
	ADCInitStructure.ADC_ScanConvMode=DISABLE;
	
	ADC_Init(ADC1,&ADCInitStructure);
	ADC_Cmd(ADC1,ENABLE);
	
}

uint16_t adcRead(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);


}




int main(){
	gpioConfig();
	adcConfig();
	while(1){
		adcValue=adcRead();
		
		if(adcValue<1000){
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		}
		else{	
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
	}

}
