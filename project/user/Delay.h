#ifndef __DELAY_H__
#define __DELAY_H__

#include "at32f435_437.h"

void delay_Init(void);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

#endif
