#ifndef _DISPLAY_TUBE_H_
#define _DISPLAY_TUBE_H_
#include "stm32f0xx.h"
#define TUBE_PORT 			GPIOB
#define TUBE1_CTRL_PIN 		GPIO_Pin_0
#define TUBE2_CTRL_PIN		GPIO_Pin_1
#define TUBE3_CTRL_PIN 		GPIO_Pin_2
#define TUBE4_CTRL_PIN 		GPIO_Pin_10

#define TUBE_SET_A			GPIO_Pin_8
#define TUBE_SET_B			GPIO_Pin_5
#define TUBE_SET_C			GPIO_Pin_6
#define TUBE_SET_D			GPIO_Pin_7

typedef enum TUBE{
	TUBE_1 = 0,
	TUBE_2 ,
	TUBE_3 ,
	TUBE_4 ,
}TUBE_TYPE;

extern uint16_t TUBE_DisplayNum(uint16_t Num);
extern void TUBE_InitConfig(void);


#endif



