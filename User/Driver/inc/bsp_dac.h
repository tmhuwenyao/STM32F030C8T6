#ifndef __BSP_DAC_H
#define __BSP_DAC_H

#include "stm32f0xx.h"
#include <stdio.h>

void DAC_InitConfig(void);
void DAC_VolOutput(float value);
#endif

