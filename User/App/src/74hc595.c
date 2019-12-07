/*该程序适用于逻辑芯片 74HC595，驱动数码管*/
#include "74hc595.h"
#include "bsp_systick.h"

uint8_t tube_flag = 0;
//引脚初始化
void HC595Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_CLK_HC595, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  HC595_CLK_PIN | HC595_RCK_PIN | HC595_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(RCC_HC595_PORT, &GPIO_InitStructure);
}
void HC595Send(uint8_t data)
{
	uint8_t i;
	for(i=8;i > 0;i--)
	{
		if(data & 0x80)
			HC595_DATA_H;
		else
			HC595_DATA_L;
		HC595_CLK_L;  //上升沿发生位移
		Delay_ms(1);
		data <<= 1;
		HC595_CLK_H;
		Delay_ms(1);	
	}
	
}

void HC595Load(void)
{
	HC595_RCK_L;
	HC595_RCK_H;
}
void LED_RowOn(uint8_t row7_0,uint8_t row15_8,uint8_t row31_24,uint8_t row16_23)
{
	HC595Send(row7_0);
	HC595Send(row15_8);
	HC595Send(row31_24);
	HC595Send(row16_23);
	HC595Load();
}
void LED_RowOut(uint32_t data)
{
	HC595Send(data >> 24);
	HC595Send(data >> 16);
	HC595Send(data >> 8);
	HC595Send(data >> 0);
	HC595Load();
}
/*驱动数码管现实数字*/
void TUBE_ShowData(uint32_t data)
{
	
}

