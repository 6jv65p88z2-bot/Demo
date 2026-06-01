#ifndef __WK_SYSTEM_H
#define __WK_SYSTEM_H

#include "at32f435_437_crm.h"
#include "at32f435_437.h"


void wk_timebase_init(void);
void wk_delay_ms(uint32_t delay);
void wk_timebase_handler(void);

#endif
