/*该芯片现实适用于逻辑芯片 74HC4051D*/
#include "displaytube.h"
uint8_t tube_flag =0;

static void TUBE_Cmd(TUBE_TYPE TUBE,FunctionalState NewState)
{
	switch(TUBE)
	{
		case TUBE_1:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE1_CTRL_PIN);  //设为高电平，使能数码管1
			else
				GPIO_ResetBits(TUBE_PORT, TUBE1_CTRL_PIN);  
			break;
		case TUBE_2:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE2_CTRL_PIN);  //设为高电平，使能数码管2
			else
				GPIO_ResetBits(TUBE_PORT, TUBE2_CTRL_PIN);
			break;
		case TUBE_3:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE3_CTRL_PIN);  //设为高电平，使能数码管3
			else
				GPIO_ResetBits(TUBE_PORT, TUBE3_CTRL_PIN);
			break;
		case TUBE_4:
			if(NewState == ENABLE)
				GPIO_SetBits(TUBE_PORT, TUBE4_CTRL_PIN);  //设为高电平，使能数码管4
			else
				GPIO_ResetBits(TUBE_PORT, TUBE4_CTRL_PIN);
			break;
		default:
			break;
	}
}
/*单个数码管控制,输入0-9*/
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
		default : //默认输出 0
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_A);			//A Low,B Low,C Low,D Low
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_B);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_C);
			GPIO_ResetBits(TUBE_PORT, TUBE_SET_D);
			break;
	}
	return ret;
}

/*显示一位数*/
static void TUBE_Displayer_One(uint16_t Num)
{
	TUBE_Cmd(TUBE_1,ENABLE);
	TUBE_Cmd(TUBE_2,DISABLE);
	TUBE_Cmd(TUBE_3,DISABLE);
	TUBE_Cmd(TUBE_4,DISABLE);
	TUBE_Set(Num);
}
/*显示两位数*/
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
/*显示三位数*/
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
/*显示四位数*/
static void TUBE_Displayer_Four(uint16_t Num)
{
	uint8_t count1 = 0,count2 = 0,count3 = 0,count4 = 0;
	count1 = Num% 10;         //个
	count2 = (Num/10) % 10;   //十
	count3 = (Num/100) % 10;  //百
	count4 = Num / 1000;      //千
	
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
  * @param  数字
  * @retval 返回显示的位数
  * @brief  显示管设置数字 
  */
uint16_t TUBE_DisplayNum(uint16_t Num)
{
	uint16_t ret = 0;
	if(Num >= 1000)  		    //四位数
	{
		TUBE_Displayer_Four(Num);	
		ret = 4;
	}else if(Num >= 100) 	    //三位数
	{
		TUBE_Displayer_Three(Num);	
		ret = 3;
	}else if(Num >=10)  		//两位数
	{
		TUBE_Displayer_Two(Num);	
		ret = 2;
	}else{    					//一位数
		TUBE_Displayer_One(Num);	
		ret = 1;
	}
	return ret;
}

/*数码管初始化*/
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

