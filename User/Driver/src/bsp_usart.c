#include "bsp_usart.h"
#include "internalmodbus.h"
/* ����ÿ�����ڽṹ����� */
UART_T g_tUart1;
static uint8_t g_TxBuf1[TX_BUF_SIZE];		/* ���ͻ����� */
static uint8_t g_RxBuf1[RX_BUF_SIZE];		/* ���ջ����� */
static void UartVarInit(void);
static void RS485_RecieveNew(uint8_t ch);
/**
  * @name  USART_GPIO_Init
  * @param  None
  * @retval None
  * @brief  ��ʼ������
  */
void USART_GPIO_Init(uint8_t UART_PORT,uint32_t BAUTRATE)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
	/*Initialize UART1*/
	if((UART_PORT == UART_PORT1) && (USART1_EN == 1))
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
		/*PB12 low enable*/
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			//Configure USART1 pins:  Rx and Tx ----------------------------
		GPIO_InitStructure.GPIO_Pin =  USART1_Pin_Tx | USART1_Pin_Rx;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(USART1_PORT, &GPIO_InitStructure);

		USART_InitStructure.USART_BaudRate = BAUTRATE;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		/*ʹ�ܴ���1*/
		USART_Cmd(USART1,ENABLE);
		
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	}
	NVIC_UsartConfig();// �����жϺ�������
	UartVarInit();
	
}
/*
*********************************************************************************************************
*	�� �� ��: UartVarInit
*	����˵��: ��ʼ��������صı���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void UartVarInit(void)
{
	g_tUart1.uart = USART1;						/* STM32 �����豸 */
	g_tUart1.pTxBuf = g_TxBuf1;					/* ���ͻ�����ָ�� */
	g_tUart1.pRxBuf = g_RxBuf1;					/* ���ջ�����ָ�� */
	g_tUart1.usTxBufSize = TX_BUF_SIZE;			/* ���ͻ�������С */
	g_tUart1.usRxBufSize = RX_BUF_SIZE;			/* ���ջ�������С */
	g_tUart1.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart1.usTxRead = 0;						/* ����FIFO������ */
	g_tUart1.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart1.usRxRead = 0;						/* ����FIFO������ */
	g_tUart1.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart1.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart1.ReciveNew = RS485_RecieveNew;		/* ���յ������ݺ�Ļص����� */
}

void NVIC_UsartConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* ʹ�ܴ���1�ж� */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
#if 0
/*�ض��򴮿����������ʹ��printf����*/
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET)
	{
	}
	return ch;
} 
//stdin
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
}
#endif

//���һ���ַ�
static void USART_Putchar(UART_T *_pUart,uint8_t c)
{
	USART_SendData(_pUart->uart, c);
	while(USART_GetFlagStatus(_pUart->uart, USART_FLAG_TC)!=SET);
}
//���һ���ַ���
void USART_Senddata(UART_T *_pUart,uint8_t * str,uint16_t str_len)
{
	uint8_t i = 0;
	for(i = 0;i < str_len ;i++)
	{
		USART_Putchar(_pUart,*(str + i));
	}
}

/*RS485 SEND*/
uint8_t RS485_SendData(UART_T *_pUart,uint8_t * str,uint16_t str_len)
{
	uint8_t ret =0;
	/*ʹ�ܷ���*/
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	USART_Senddata(_pUart,str,str_len);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	
	return ret;
}

/*RS485 RECV*/
static void RS485_RecieveNew(uint8_t ch)
{
	MODS_ReceieveNew(ch);
}



void UartIRQ(UART_T *_pUart)
{
	uint8_t ch = 0;
	if (USART_GetITStatus(_pUart->uart, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(_pUart->uart,USART_IT_RXNE);
		ch = USART_ReceiveData(_pUart->uart);
		_pUart->pRxBuf[_pUart->usRxWrite ++] = ch;

		_pUart->ReciveNew(ch);
		
	}
}
