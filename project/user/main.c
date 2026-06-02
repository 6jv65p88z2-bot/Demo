#include "Delay.h"
#include "wk_usart.h"
#include "wk_system.h"
#include "at32f435_437_wk_config.h"
#include "wk_gpio.h"


int main(void)
{
	wk_periph_clock_config();
	wk_timebase_init();         // 必须在 NVIC 配置之后调用
	wk_gpio_config();						//所有GPIO引脚初始化
	wk_usart1_init();
	//TurnOnLed();
	TurnOffLed();
	printf("TEST");
	
	//printf("C\r\n");
	while(1)
	{
//		printf("A");	
//		wk_delay_ms(500);
		
		TurnReverse();
	}
}

	