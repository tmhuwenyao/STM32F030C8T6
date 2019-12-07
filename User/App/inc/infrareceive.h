#ifndef _INFRA_RECEIVE_H_
#define _INFRA_RECEIVE_H_

#include "stm32f0xx.h"
#include <stdio.h>
#define ARRAY_NUM			1 //接收灯的标志位，8 * ARRAY_NUM 为灯的数量
#define LIGHT_NUM			(8*ARRAY_NUM)

#define INFRA_DETECT_PORT   GPIOB
#define INFRA_DETECT_PIN	GPIO_Pin_11
/*74逻辑芯片控制引脚*/
#define HC_PORT1	GPIOA
#define HC_PIN1		GPIO_Pin_0
#define HC_PORT2	GPIOA
#define HC_PIN2		GPIO_Pin_1
#define HC_PORT3	GPIOF
#define HC_PIN3		GPIO_Pin_5


//板子的编号
typedef enum BOARD{
	BOARD_1 = 0,
	BOARD_2,
	BOARD_3,
	BOARD_4,
	BOARD_5,
	BOARD_6,
	BOARD_7,
	BOARD_8,
	BOARD_9,
	BOARD_10,
	BOARD_NUM,
}BOARD_ID;

//板子上灯的编号
typedef enum LIGHT{
	LIGHT_1 = 0,
	LIGHT_2,
	LIGHT_3,
	LIGHT_4,
	LIGHT_5,
	LIGHT_6,
	LIGHT_7,
	LIGHT_8,
}LIGHT_ID;

extern void Infra_Init(void);
extern void InfraRecvProcess(void);

extern uint16_t infra_time_flag;
extern uint8_t infra_led_mark[ARRAY_NUM];

#endif
