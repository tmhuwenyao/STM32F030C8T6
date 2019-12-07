#include "bsp_dac.h"

/**
  * @name  ADC1_InitConfig
  * @param  None
  * @retval None
  * @brief  ��ʼ��DAC
  */
void DAC_InitConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	
	/* ʹ��DACʱ�� */	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	  /* DAC��GPIO���ã�ģ����� PA4 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  /* ����DAC ͨ��1 */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;	//ʹ��TIM2��Ϊ����Դ
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//��ʹ��DAC�������
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	DAC_Cmd(DAC_Channel_1,ENABLE);
}


void DAC_VolOutput(float value)
{
	float set_voltage = 0;
	set_voltage = (value / 3.3)*4096;
	DAC_SetChannel1Data(DAC_Align_12b_R, set_voltage);  //12bit �Ҷ���
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
}

