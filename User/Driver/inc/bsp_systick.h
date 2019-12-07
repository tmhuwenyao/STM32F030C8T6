#ifndef	__BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f0xx.h"
#include <stdio.h>

void SystickConfig(uint8_t SYSCLK);
void Delay_ms(uint32_t nTime);
void Delay_us(uint32_t nTime);
	

#endif

