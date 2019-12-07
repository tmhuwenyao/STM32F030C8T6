#include "infrareceive.h"

uint16_t infra_time_flag = 0;  //���ܵƵı�־λ
uint8_t infra_led_mark[ARRAY_NUM] = {0}; //���յƵ��źſ��ر�־λ
/*
*������źŽ��մ���
*/
static void Infra_RecvConfig()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
	/*������������ PB11*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	/*74HC4501DоƬʹ�� PA7*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
}
static void TIM3_InitConfig(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInitStruct.TIM_Prescaler = 4799; //Ԥ��Ƶϵ��������Ƶ��48MHz/(4799+1) = 10Khz
	TIM_TimeBaseInitStruct.TIM_Period = 9;  //��ʱ1ms�ļ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����TIM3�ж�
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//����¼����±�־λ
	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority =1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void Infra_Init(void)
{
	Infra_RecvConfig();
	TIM3_InitConfig();
}
void BoardLightEnable(BOARD_ID board,LIGHT_ID light)
{
	if(board == BOARD_1)
	{
		switch(light)
		{
			case LIGHT_1:	//Y0  -Z
				GPIO_ResetBits(HC_PORT1,HC_PIN1);
				GPIO_ResetBits(HC_PORT2,HC_PIN2);
				GPIO_ResetBits(HC_PORT3,HC_PIN3);
				break;
			case LIGHT_2:	//Y1  -Z
				GPIO_SetBits(HC_PORT1,HC_PIN1);
				GPIO_ResetBits(HC_PORT2,HC_PIN2);
				GPIO_ResetBits(HC_PORT3,HC_PIN3);
				break;
			case LIGHT_3:	//Y2  -Z
				GPIO_ResetBits(HC_PORT1,HC_PIN1);
				GPIO_SetBits(HC_PORT2,HC_PIN2);
				GPIO_ResetBits(HC_PORT3,HC_PIN3);
				break;
			case LIGHT_4:   // Y3  -Z
				GPIO_SetBits(HC_PORT1,HC_PIN1);
				GPIO_SetBits(HC_PORT2,HC_PIN2);
				GPIO_ResetBits(HC_PORT3,HC_PIN3);
				break;
			case LIGHT_5:	//Y4  -Z
				GPIO_ResetBits(HC_PORT1,HC_PIN1);
				GPIO_ResetBits(HC_PORT2,HC_PIN2);
				GPIO_SetBits(HC_PORT3,HC_PIN3);
				break;
			case LIGHT_6:  //Y5  -Z
				GPIO_SetBits(HC_PORT1,HC_PIN1);
				GPIO_ResetBits(HC_PORT2,HC_PIN2);
				GPIO_SetBits(HC_PORT3,HC_PIN3);
				break;
			case LIGHT_7:	//Y6  -Z
				GPIO_ResetBits(HC_PORT1,HC_PIN1);
				GPIO_SetBits(HC_PORT2,HC_PIN2);
				GPIO_SetBits(HC_PORT3,HC_PIN3);
				break;
			case LIGHT_8:	//Y7  -Z
				GPIO_SetBits(HC_PORT1,HC_PIN1);
				GPIO_SetBits(HC_PORT2,HC_PIN2);
				GPIO_SetBits(HC_PORT3,HC_PIN3);
				break;
			default:
				break;
		}
	}
}
/*
*********************************************************************************************************
*	�� �� ��: InfraRecvProcess
*	����˵��: �����������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void InfraRecvProcess(void)
{
	BoardLightEnable(BOARD_1,(LIGHT_ID)infra_time_flag);
}

