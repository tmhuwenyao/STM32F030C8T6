#ifndef __BSP_H
#define __BSP_H

#include "stm32f0xx.h"
#include <stdio.h>
/*****************°æ±¾ºÅ£¬¼ÇµÃÐÞ¸Ä±¸·*************************/
#define VERSION_MAIN	100
#define VERSION_SIDE	100
#define VERSION_DEVP	1
/*************************************************************/

#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_timer.h"
#include "bsp_dac.h"
#include "displaytube.h"
#include "infrareceive.h"
#include "74hc595.h"

void BSP_Init(void);

#endif

