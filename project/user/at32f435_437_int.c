#include "at32f435_437_int.h"

/**
  * @brief  provides a tick value in millisecond.
  * @param  none
  * @retval tick value
  */

void SysTick_Handler(void)
{
	wk_timebase_handler();    // 处理时间基定时器中断
}