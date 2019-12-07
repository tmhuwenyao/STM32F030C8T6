#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f0xx.h"
#include <stdio.h>
/*
*��·���ڣ���һ·�����뷢������ͨ�ţ����������ڶ�·���ڶ������modbusͨ�ţ����ӻ���
*����1 PA9(TX) PA10(RX) USART1
*����2 PA2(TX) PA3(RX)  USART2
*/
#define USART1_PORT 		GPIOA
#define USART1_Pin_Tx 		GPIO_Pin_9
#define USART1_Pin_Rx 		GPIO_Pin_10
#define USART1_GPIO_CLK 	RCC_APB2Periph_GPIOA

#define USART2_PORT 		GPIOA
#define USART2_Pin_Tx 		GPIO_Pin_2
#define USART2_Pin_Rx 		GPIO_Pin_3
#define USART2_GPIO_CLK 	RCC_APB2Periph_GPIOA
/*����1 ����2ʹ��*/
#define USART1_EN			1
//#define USART2_EN 			1
/*���ڻ�������С*/
#define TX_BUF_SIZE			256
#define RX_BUF_SIZE			256

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

typedef enum {
	UART_PORT1 = 0,
	UART_PORT2,
}UART_PORT_NUM;

/* �����豸�ṹ�� */
typedef struct
{
	USART_TypeDef *uart;		/* STM32�ڲ������豸ָ�� */
	uint8_t *pTxBuf;			/* ���ͻ����� */
	uint8_t *pRxBuf;			/* ���ջ����� */
	uint16_t usTxBufSize;		/* ���ͻ�������С */
	uint16_t usRxBufSize;		/* ���ջ�������С */
	__IO uint16_t usTxWrite;			/* ���ͻ�����дָ�� */
	__IO uint16_t usTxRead;			/* ���ͻ�������ָ�� */
	__IO uint16_t usTxCount;			/* �ȴ����͵����ݸ��� */

	__IO uint16_t usRxWrite;			/* ���ջ�����дָ�� */
	__IO uint16_t usRxRead;			/* ���ջ�������ָ�� */
	__IO uint16_t usRxCount;			/* ��δ��ȡ�������ݸ��� */

	void (*SendBefor)(void); 	/* ��ʼ����֮ǰ�Ļص�����ָ�루��Ҫ����RS485�л�������ģʽ�� */
	void (*SendOver)(void); 	/* ������ϵĻص�����ָ�루��Ҫ����RS485������ģʽ�л�Ϊ����ģʽ�� */
	void (*ReciveNew)(uint8_t _byte);	/* �����յ����ݵĻص�����ָ�� */
}UART_T;


void USART_GPIO_Init(uint8_t UART_PORT,uint32_t BAUTRATE);
int fputc(int ch, FILE *f);
//void USART1_Senddata(char * str);
void NVIC_UsartConfig(void);
void UartIRQ(UART_T *_pUart);


uint8_t RS485_SendData(UART_T *_pUart,uint8_t * str,uint16_t str_len);

extern UART_T g_tUart1;

#endif


