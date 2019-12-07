/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  Hu Wenyao 
  * @version V1.0.0
  * @date    18-May-2019
  * @brief   Main program body
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/*时间标志位*/
uint8_t tim2_1s_flag = 0;  //定时器2  1s中断标志
uint16_t tube_num = 1234;
float DO_Voltage = 0;  //输出电压值
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{

//	RS485_SendData(&g_tUart1,"hello,this is a demo\n\r", 22);
  /* Infinite loop */
while (1)
{

}


}
