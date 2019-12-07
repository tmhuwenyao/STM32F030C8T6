#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f0xx.h"
#include <stdio.h>
/*
*两路串口，第一路用于与发射板进行通信（保留），第二路用于对外进行modbus通信，当从机用
*串口1 PA9(TX) PA10(RX) USART1
*串口2 PA2(TX) PA3(RX)  USART2
*/
#define USART1_PORT 		GPIOA
#define USART1_Pin_Tx 		GPIO_Pin_9
#define USART1_Pin_Rx 		GPIO_Pin_10
#define USART1_GPIO_CLK 	RCC_APB2Periph_GPIOA

#define USART2_PORT 		GPIOA
#define USART2_Pin_Tx 		GPIO_Pin_2
#define USART2_Pin_Rx 		GPIO_Pin_3
#define USART2_GPIO_CLK 	RCC_APB2Periph_GPIOA
/*串口1 串口2使能*/
#define USART1_EN			1
//#define USART2_EN 			1
/*串口缓冲区大小*/
#define TX_BUF_SIZE			256
#define RX_BUF_SIZE			256

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

typedef enum {
	UART_PORT1 = 0,
	UART_PORT2,
}UART_PORT_NUM;

/* 串口设备结构体 */
typedef struct
{
	USART_TypeDef *uart;		/* STM32内部串口设备指针 */
	uint8_t *pTxBuf;			/* 发送缓冲区 */
	uint8_t *pRxBuf;			/* 接收缓冲区 */
	uint16_t usTxBufSize;		/* 发送缓冲区大小 */
	uint16_t usRxBufSize;		/* 接收缓冲区大小 */
	__IO uint16_t usTxWrite;			/* 发送缓冲区写指针 */
	__IO uint16_t usTxRead;			/* 发送缓冲区读指针 */
	__IO uint16_t usTxCount;			/* 等待发送的数据个数 */

	__IO uint16_t usRxWrite;			/* 接收缓冲区写指针 */
	__IO uint16_t usRxRead;			/* 接收缓冲区读指针 */
	__IO uint16_t usRxCount;			/* 还未读取的新数据个数 */

	void (*SendBefor)(void); 	/* 开始发送之前的回调函数指针（主要用于RS485切换到发送模式） */
	void (*SendOver)(void); 	/* 发送完毕的回调函数指针（主要用于RS485将发送模式切换为接收模式） */
	void (*ReciveNew)(uint8_t _byte);	/* 串口收到数据的回调函数指针 */
}UART_T;


void USART_GPIO_Init(uint8_t UART_PORT,uint32_t BAUTRATE);
int fputc(int ch, FILE *f);
//void USART1_Senddata(char * str);
void NVIC_UsartConfig(void);
void UartIRQ(UART_T *_pUart);


uint8_t RS485_SendData(UART_T *_pUart,uint8_t * str,uint16_t str_len);

extern UART_T g_tUart1;

#endif


