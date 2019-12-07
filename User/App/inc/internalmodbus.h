#ifndef _INTERNAL_MODBUS_H_
#define	_INTERNAL_MODBUS_H_
#include "stm32f0xx.h"

#define SLAVE_ADDRESS		1
#define S_RX_BUF_SIZE		255
#define S_TX_BUF_SIZE		255

/* RTU Ӧ����� */
#define RSP_OK				0		/* �ɹ� */
#define RSP_ERR_CMD			0x01	/* ��֧�ֵĹ����� */
#define RSP_ERR_REG_ADDR	0x02	/* �Ĵ�����ַ���� */
#define RSP_ERR_VALUE		0x03	/* ����ֵ����� */
#define RSP_ERR_WRITE		0x04	/* д��ʧ�� */

#define ERR_DATA			0Xffff //��������

typedef struct
{
	uint8_t RxBuf[S_RX_BUF_SIZE];
	uint8_t RxCount;
	uint8_t RxStatus;
	uint8_t RxNewFlag;

	uint8_t RspCode;

	uint8_t TxBuf[S_TX_BUF_SIZE];
	uint8_t TxCount;
}MODS_T;


typedef enum  PARAMETER{
	REG1 = 0,
	REG2,
	REG3,
	REG4,
	REG5,
	REG6,
	REG7,
	REG8,
	REG9,
	REG10,
	REG_NUM,
}MODS_PARA;


void MODS_ReceieveNew(uint8_t ch);
void MODS_CommProcess(void);

extern MODS_T g_tModS;


#endif
