#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "stm32f0xx.h"
#include <stdio.h>

#define LED_PORT 	GPIOC
#define LED_PIN_GREEN 	GPIO_Pin_10
#define LED_PIN_RED		GPIO_Pin_13
#define RCC_LED		RCC_AHBPeriph_GPIOC

typedef enum LED{
	GREEN = 0,
	RED,
}LED_TYPE;

enum{
	LED_OFF = 0,
	LED_ON,
	LED_TOGGLE,  //·­×ª
};

enum{
	FAIL = 0,
	TRUE = 1,
};

enum{
	OFF = 0,
	ON,
};
extern uint8_t LED_SetStatus(LED_TYPE LED,uint8_t Status);
extern void LED_Init(void);

extern void DO_InitConfig(void);
extern void DO_Output(uint8_t status);
	

#endif

