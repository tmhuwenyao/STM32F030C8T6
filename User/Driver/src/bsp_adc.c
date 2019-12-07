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
	/*GPIO口配置*/
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*ADC配置*/
	ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
	ADC_DMACmd(ADC1, ENABLE);    // 使能ADC DMA 功能
  
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //不使用外部触发转换
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   //持续扫描模式
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //采集数据右对齐
	ADC_Init(ADC1,&ADC_InitStructure);
  
	ADC_ChannelConfig(ADC1, ADC_Channel_11, ADC_SampleTime_239_5Cycles);
	ADC_GetCalibrationFactor(ADC1);
  
	ADC_Cmd(ADC1, ENABLE);
  
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN))
	{
	}
	/* 由于没有采用外部触发，所以使用软件触发ADC转换 */ 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	/*开始ADC转换*/
	  ADC_StartOfConversion(ADC1);
	//ADC_StopOfConversion(ADC1);  //停止ADC转换
    
}

static void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1);
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC_DR_Address; //ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_Buffer; //内存地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为半字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     //数据宽度为16位
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;      //外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;            // 内存地址递增
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;         //循环传输
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = ADC_BUFFER_SIZE;     //采集通道的数据大小
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
	DMA_Cmd(DMA1_Channel1, ENABLE);   // DMA使能 通道1
}

void ADC1_InitConfig()
{
	DMA_Config();
	ADC1_Config();
}


/*
**函数功能：获取X通道AD值（0~4096）
**参数    ：channel---模拟口通道号
**参数取值：	默认通道11
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
**函数功能：获取采集电压值
**公	式：V(sample) = V(REF) * Value/(0x0FFF + 1)
**说明：参考电压为3.3V
****************************************/
float Get_AdcMath(uint16_t ADC_Value)
{
	float Value;

	Value = (float)ADC_Value * (3.3 / 4096);
//	ADC_ConvertedVoltage = (float)(ADC_ConvertedData * 2980) / 0xFFF + 0.5;
	return Value;
}

