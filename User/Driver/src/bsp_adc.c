#include "bsp_adc.h"

/* Private define ------------------------------------------------------------*/
#define ADC_DR_Address                  0x40012440   //&ADC1->DR
#define ADC_BUFFER_SIZE                 100

/* Private variables ---------------------------------------------------------*/
__IO uint16_t ADC_Buffer[ADC_BUFFER_SIZE];
__IO uint32_t ADC_ConvertedData_Sum;
__IO uint16_t ADC_ConvertedData;
__IO uint16_t ADC_ConvertedVoltage;
static void  ADC1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_DeInit(ADC1);
	GPIO_DeInit(GPIOC);
	/*GPIO������*/
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*ADC����*/
	ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
	ADC_DMACmd(ADC1, ENABLE);    // ʹ��ADC DMA ����
  
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //��ʹ���ⲿ����ת��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   //����ɨ��ģʽ
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //�ɼ������Ҷ���
	ADC_Init(ADC1,&ADC_InitStructure);
  
	ADC_ChannelConfig(ADC1, ADC_Channel_11, ADC_SampleTime_239_5Cycles);
	ADC_GetCalibrationFactor(ADC1);
  
	ADC_Cmd(ADC1, ENABLE);
  
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN))
	{
	}
	/* ����û�в����ⲿ����������ʹ���������ADCת�� */ 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	/*��ʼADCת��*/
	  ADC_StartOfConversion(ADC1);
	//ADC_StopOfConversion(ADC1);  //ֹͣADCת��
    
}

static void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1);
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC_DR_Address; //ADC��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_Buffer; //�ڴ��ַ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;      //�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;            // �ڴ��ַ����
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;         //ѭ������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = ADC_BUFFER_SIZE;     //�ɼ�ͨ�������ݴ�С
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
	DMA_Cmd(DMA1_Channel1, ENABLE);   // DMAʹ�� ͨ��1
}

void ADC1_InitConfig()
{
	DMA_Config();
	ADC1_Config();
}


/*
**�������ܣ���ȡXͨ��ADֵ��0~4096��
**����    ��channel---ģ���ͨ����
**����ȡֵ��	Ĭ��ͨ��11
*/
uint16_t Get_Adc()
{
	uint16_t i = 0;
	for(i = 0;i < ADC_BUFFER_SIZE; i++)
	{
		ADC_ConvertedData_Sum = ADC_Buffer[i];
	}
	ADC_ConvertedData = ADC_ConvertedData_Sum / ADC_BUFFER_SIZE;
	return 	ADC_ConvertedData;	  	
}


/***************************************
**�������ܣ���ȡ�ɼ���ѹֵ
**��	ʽ��V(sample) = V(REF) * Value/(0x0FFF + 1)
**˵�����ο���ѹΪ3.3V
****************************************/
float Get_AdcMath(uint16_t ADC_Value)
{
	float Value;

	Value = (float)ADC_Value * (3.3 / 4096);
//	ADC_ConvertedVoltage = (float)(ADC_ConvertedData * 2980) / 0xFFF + 0.5;
	return Value;
}

