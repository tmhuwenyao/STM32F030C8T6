#include "bsp_dac.h"

/**
  * @name  ADC1_InitConfig
  * @param  None
  * @retval None
  * @brief  初始化DAC
  */
void DAC_InitConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	
	/* 使能DAC时钟 */	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	  /* DAC的GPIO配置，模拟输出 PA4 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  /* 配置DAC 通道1 */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;	//使用TIM2作为触发源
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//不使用DAC输出缓冲
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	DAC_Cmd(DAC_Channel_1,ENABLE);
}


void DAC_VolOutput(float value)
{
	float set_voltage = 0;
	set_voltage = (value / 3.3)*4096;
	DAC_SetChannel1Data(DAC_Align_12b_R, set_voltage);  //12bit 右对齐
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
}

