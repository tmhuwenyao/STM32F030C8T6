#ifndef __HC_595_H
#define	__HC_595_H
#include "stm32f0xx.h"

#define	HC595_CLK_PIN	GPIO_Pin_4  //PB4
#define HC595_RCK_PIN	GPIO_Pin_5  //PB5
#define	HC595_DATA_PIN  GPIO_Pin_8  //PB8
#define RCC_CLK_HC595	RCC_AHBPeriph_GPIOB   //¶¼ÊÇGPIOBÒý½Å
#define RCC_HC595_PORT	GPIOB

#define HC595_CLK_H		GPIOB->BSRR = HC595_CLK_PIN
#define HC595_CLK_L		GPIOB->BRR  = HC595_CLK_PIN

#define HC595_RCK_H		GPIOB->BSRR = HC595_RCK_PIN
#define HC595_RCK_L		GPIOB->BRR  = HC595_RCK_PIN

#define HC595_DATA_H	GPIOB->BSRR = HC595_DATA_PIN
#define HC595_DATA_L	GPIOB->BRR  = HC595_DATA_PIN

extern void HC595Send(uint8_t data);
extern void HC595Init(void);
extern void HC595Load(void);
extern void LED_RowOn(uint8_t row7_0,uint8_t row15_8,uint8_t row31_24,uint8_t row16_23);
extern void LED_RowOut(uint32_t data);
extern void TUBE_ShowData(uint32_t data);

#endif

