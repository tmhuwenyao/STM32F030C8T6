/*��оƬ��ʵ�������߼�оƬ 74HC4051D*/
#include "displaytube.h"
uint8_t tube_flag =0;

static void TUBE_Cmd(TUBE_TYPE TUBE,FunctionalState NewState)
{
	switch(TUBE)
	{
		case TUBE_1:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE1_CTRL_PIN);  //��Ϊ�ߵ�ƽ��ʹ�������1
			else
				GPIO_ResetBits(TUBE_PORT, TUBE1_CTRL_PIN);  
			break;
		case TUBE_2:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE2_CTRL_PIN);  //��Ϊ�ߵ�ƽ��ʹ�������2
			else
				GPIO_ResetBits(TUBE_PORT, TUBE2_CTRL_PIN);
			break;
		case TUBE_3:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE3_CTRL_PIN);  //��Ϊ�ߵ�ƽ��ʹ�������3
			else
				GPIO_ResetBits(TUBE_PORT, TUBE3_CTRL_PIN);
			break;
		case TUBE_4:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE4_CTRL_PIN);  //��Ϊ�ߵ�ƽ��ʹ�������4
			else
				GPIO_ResetBits(TUBE_PORT, TUBE4_CTRL_PIN);
			break;
		default:
			break;
	}
}
/*��������ܿ���,����0-9*/
static uint8_t TUBE_Set(uint8_t Num)
{
	uint8_t ret = 0;
	switch(Num)
	{
		case 0 :   
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_A);			//A Low,B Low,C Low,D Low
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 0;
			break;
		case 1 :
			GPIO_SetBits(TUBE_PORT, TUBE_SET_A);			//A High,B Low,C Low,D Low
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 1;
			break;
		case 2 :
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_A);			//A Low,B High,C Low,D Low
			GPIO_SetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 2;
			break;
		case 3 :
			GPIO_SetBits(TUBE_PORT, TUBE_SET_A);			//A High,B High,C Low,D Low
			GPIO_SetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 3;
			break;
		case 4 :
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_A);			//A Low,B Low,C High,D Low
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_SetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 4;
			break;
		case 5 :
			GPIO_SetBits(TUBE_PORT, TUBE_SET_A);			//A High,B Low,C High,D Low
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_SetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 5;
			break;
		case 6 :
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_A);			//A Low,B High,C High,D Low
			GPIO_SetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_SetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 6;
			break;
		case 7 :
			GPIO_SetBits(TUBE_PORT, TUBE_SET_A);			//A High,B High,C High,D Low
			GPIO_SetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_SetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			ret = 7;
			break;
		case 8 :
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_A);			//A Low,B Low,C Low,D High
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_SetBits(TUBE_PORT, TUBE_SET_D);
			ret = 8;
			break;
		case 9 :
			GPIO_SetBits(TUBE_PORT, TUBE_SET_A);			//A High,B Low,C Low,D High
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_SetBits(TUBE_PORT, TUBE_SET_D);
			ret =9;
			break;
		default : //Ĭ����� 0
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_A);			//A Low,B Low,C Low,D Low
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			break;
	}
	return ret;
}

/*��ʾһλ��*/
static void TUBE_Displayer_One(uint16_t Num)
{
	TUBE_Cmd(TUBE_1,ENABLE);
	TUBE_Cmd(TUBE_2,DISABLE);
	TUBE_Cmd(TUBE_3,DISABLE);
	TUBE_Cmd(TUBE_4,DISABLE);
	TUBE_Set(Num);
}
/*��ʾ��λ��*/
static void TUBE_Displayer_Two(uint16_t Num)
{
	uint8_t count1 = 0 ,count2 = 0;
	count1 = Num % 10;
	count2 = Num / 10;
	TUBE_Cmd(TUBE_3,DISABLE);
	TUBE_Cmd(TUBE_4,DISABLE);
	if(tube_flag == 1)
	{
		TUBE_Cmd(TUBE_1,ENABLE);
		TUBE_Cmd(TUBE_2,DISABLE);
		TUBE_Set(count1);
	}else if(tube_flag == 2)
	{
		TUBE_Cmd(TUBE_2,ENABLE);
		TUBE_Cmd(TUBE_1,DISABLE);
		TUBE_Set(count2);
	}
	
}
/*��ʾ��λ��*/
static void TUBE_Displayer_Three(uint16_t Num)
{
	uint8_t count1 =0,count2 =0,count3 =0;
	count1 = Num % 10;
	count2 = (Num/10)%10;
	count3 = Num % 100;
	TUBE_Cmd(TUBE_4,DISABLE);
	
	if(tube_flag == 1)
	{
		TUBE_Cmd(TUBE_1,ENABLE);
		TUBE_Cmd(TUBE_2,DISABLE);
		TUBE_Cmd(TUBE_3,DISABLE);
		TUBE_Set(count1);
	}else if(tube_flag == 2)
	{
		TUBE_Cmd(TUBE_2,ENABLE);
		TUBE_Cmd(TUBE_1,DISABLE);
		TUBE_Cmd(TUBE_3,DISABLE);
		TUBE_Set(count2);
	}else if(tube_flag == 3)
	{
		TUBE_Cmd(TUBE_3,ENABLE);
		TUBE_Cmd(TUBE_1,DISABLE);
		TUBE_Cmd(TUBE_2,DISABLE);
		TUBE_Set(count3);
	}
	
}
/*��ʾ��λ��*/
static void TUBE_Displayer_Four(uint16_t Num)
{
	uint8_t count1 = 0,count2 = 0,count3 = 0,count4 = 0;
	count1 = Num% 10;         //��
	count2 = (Num/10) % 10;   //ʮ
	count3 = (Num/100) % 10;  //��
	count4 = Num / 1000;      //ǧ
	
	if(tube_flag == 1)
	{
		TUBE_Cmd(TUBE_1,ENABLE);
		TUBE_Cmd(TUBE_2,DISABLE);
		TUBE_Cmd(TUBE_3,DISABLE);
		TUBE_Cmd(TUBE_4,DISABLE);
		TUBE_Set(count4);
	}else if(tube_flag == 2)
	{
		TUBE_Cmd(TUBE_2,ENABLE);
		TUBE_Cmd(TUBE_1,DISABLE);
		TUBE_Cmd(TUBE_3,DISABLE);
		TUBE_Cmd(TUBE_4,DISABLE);
		TUBE_Set(count3);
	}else if(tube_flag == 3)
	{
		TUBE_Cmd(TUBE_3,ENABLE);
		TUBE_Cmd(TUBE_1,DISABLE);
		TUBE_Cmd(TUBE_2,DISABLE);
		TUBE_Cmd(TUBE_4,DISABLE);
		TUBE_Set(count2);
	}else if(tube_flag == 4)
	{
		TUBE_Cmd(TUBE_4,ENABLE);
		TUBE_Cmd(TUBE_1,DISABLE);
		TUBE_Cmd(TUBE_2,DISABLE);
		TUBE_Cmd(TUBE_3,DISABLE);
		TUBE_Set(count1);
	}
	
}
/**
  * @name  TUBE_DisplayNum
  * @param  ����
  * @retval ������ʾ��λ��
  * @brief  ��ʾ���������� 
  */
uint16_t TUBE_DisplayNum(uint16_t Num)
{
	uint16_t ret = 0;
	if(Num >= 1000)  		    //��λ��
	{
		TUBE_Displayer_Four(Num);	
		ret = 4;
	}else if(Num >= 100) 	    //��λ��
	{
		TUBE_Displayer_Three(Num);	
		ret = 3;
	}else if(Num >=10)  		//��λ��
	{
		TUBE_Displayer_Two(Num);	
		ret = 2;
	}else{    					//һλ��
		TUBE_Displayer_One(Num);	
		ret = 1;
	}
	return ret;
}

/*����ܳ�ʼ��*/
void TUBE_InitConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  TUBE1_CTRL_PIN | TUBE2_CTRL_PIN |TUBE3_CTRL_PIN |TUBE4_CTRL_PIN |   
								   TUBE_SET_A |TUBE_SET_B|TUBE_SET_C |TUBE_SET_D;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(TUBE_PORT, &GPIO_InitStructure);
}

