#include "bsp.h"
static void Show_Info_Product(void)
{
	printf("this is infrared product\n\r");
	printf("the develop number is :%d - %d -%d\n\r",VERSION_MAIN,VERSION_SIDE,VERSION_DEVP);
}

void BSP_Init(void)
{
	SystickConfig(48);    //初始化滴答定时器
	TIM2_InitConfig();    //初始化定时器
	USART_GPIO_Init(UART_PORT1,115200); //初始化串口1
//	USART_GPIO_Init(UART_PORT2,115200); //初始化串口2
	LED_Init();			//初始化LED灯
	DO_InitConfig();
//	TUBE_InitConfig();  //初始化数码管
	HC595Init();
	DAC_InitConfig();
	Infra_Init(); 
	
	/*版本号信息*/
	Show_Info_Product();
}


