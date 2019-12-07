#include "bsp.h"
static void Show_Info_Product(void)
{
	printf("this is infrared product\n\r");
	printf("the develop number is :%d - %d -%d\n\r",VERSION_MAIN,VERSION_SIDE,VERSION_DEVP);
}

void BSP_Init(void)
{
	SystickConfig(48);    //��ʼ���δ�ʱ��
	TIM2_InitConfig();    //��ʼ����ʱ��
	USART_GPIO_Init(UART_PORT1,115200); //��ʼ������1
//	USART_GPIO_Init(UART_PORT2,115200); //��ʼ������2
	LED_Init();			//��ʼ��LED��
	DO_InitConfig();
//	TUBE_InitConfig();  //��ʼ�������
	HC595Init();
	DAC_InitConfig();
	Infra_Init(); 
	
	/*�汾����Ϣ*/
	Show_Info_Product();
}


