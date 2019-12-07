#include "bsp_led.h"
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_LED, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  LED_PIN_GREEN | LED_PIN_RED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}
/**
  * @name  LED_SetStatus
  * @param  �Ƶ��ͺţ�״̬
  * @retval �ɹ�/ʧ��
  * @brief  LED״̬����
  */
uint8_t LED_SetStatus(LED_TYPE LED,uint8_t Status)
{
	uint8_t ret = FAIL;
	switch(LED)
	{
		case GREEN:
			if(Status == LED_OFF)
				GPIO_SetBits(LED_PORT, LED_PIN_GREEN);  //��Ϊ�ߵ�ƽ���ر�LED��
			else if(Status == LED_ON)
				GPIO_ResetBits(LED_PORT, LED_PIN_GREEN);
			else if(Status == LED_TOGGLE)
				LED_PORT->ODR ^= LED_PIN_GREEN;    //��ƽ��ת 
			ret = TRUE;
			break;
		case RED:
			if(Status == LED_OFF)
				GPIO_SetBits(LED_PORT, LED_PIN_RED);  //��Ϊ�ߵ�ƽ���ر�LED��
			else if(Status == LED_ON)
				GPIO_ResetBits(LED_PORT, LED_PIN_RED);
			else if(Status == LED_TOGGLE)
				LED_PORT->ODR ^= LED_PIN_RED;    //��ƽ��ת 
			ret = TRUE;
			break;
		default :
			break;
	}
	return ret;
}

/*DO���*/
void DO_InitConfig()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
}
void DO_Output(uint8_t status)
{
	if(status == ON)
	{
		GPIO_SetBits(GPIOF, GPIO_Pin_4);  //��Ϊ�ߵ�ƽ
	}else if(status == OFF)
	{
		GPIO_ResetBits(GPIOF, GPIO_Pin_4);  //��Ϊ�͵�ƽ
	}
}

