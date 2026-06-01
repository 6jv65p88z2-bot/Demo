/* add user code begin Header */
/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f435_437_wk_config.h"
#include "wk_adc.h"
#include "wk_exint.h"
#include "wk_i2c.h"
#include "wk_sdio.h"
#include "wk_spi.h"
#include "wk_tmr.h"
#include "wk_usart.h"
#include "wk_usb_otgfs.h"
#include "wk_dma.h"
#include "wk_gpio.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "wk_system.h"
#include "configure.h"
#include "motherboard.h"
#include "marlin.h"
#include "memu_gui.h"
#include "planner.h"
#include "stepper.h"
#include "heater.h"
#include "poweroff.h"
#include "sdio_sdcard.h"

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */
extern volatile uint16_t ADC_ConvertedValue[8][4]; // ADC转换值数组
extern volatile uint32_t adc_complete_flag; // ADC转换完成标志
extern uint32_t tmr7_ovf_flag; // 定时器7溢出标志
extern volatile uint32_t curr_time_cnt; // 当前时间计数
extern volatile uint8_t step_status; // 步进电机状态
uint32_t last_tmr7_ovf_flag = 0; // 上次定时器7溢出标志

uint8_t read_data = 0; // 接收数据完成标志位
/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */
extern void StopPrintHandle(void);
extern void poweroff_setup_handler(void);
extern void poweroff_startup(void);
extern void Printing_pause_control(void);              //Pause Build
/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */
void para_reset(bool hard_reset) 
{
	Board_reset(hard_reset);
}
/* add user code end 0 */

/**
  * @brief main function.
  * @param  none
  * @retval none
  */
int main(void)
{
	/* add user code begin 1 */

	/* add user code end 1 */

	/* system clock config. */
	wk_system_clock_config();

	/* config periph clock. */
	wk_periph_clock_config();

	/* nvic config. */
	wk_nvic_config();

	/* timebase config. */
	wk_timebase_init();

	//  /* init dma1 channel1 */
	//  wk_dma1_channel1_init();
	//  /* config dma channel transfer parameter */
	//  /* user need to modify define values DMAx_CHANNELy_XXX_BASE_ADDR and DMAx_CHANNELy_BUFFER_SIZE in at32xxx_wk_config.h */
	//  wk_dma_channel_config(DMA1_CHANNEL1, 
	//                        (uint32_t)&ADC1->odt, 
	//                        DMA1_CHANNEL1_MEMORY_BASE_ADDR, 
	//                        DMA1_CHANNEL1_BUFFER_SIZE);
	//  dma_channel_enable(DMA1_CHANNEL1, TRUE);

	/* init dma1 channel2 */
	wk_dma1_channel2_init();
	/* config dma channel transfer parameter */
	/* user need to modify define values DMAx_CHANNELy_XXX_BASE_ADDR and DMAx_CHANNELy_BUFFER_SIZE in at32xxx_wk_config.h */
	wk_dma_channel_config(DMA1_CHANNEL2, 
							(uint32_t)&USART2->dt, 
							DMA1_CHANNEL2_MEMORY_BASE_ADDR, 
							DMA1_CHANNEL2_BUFFER_SIZE);
	dma_channel_enable(DMA1_CHANNEL2, TRUE);

	/* init dma1 channel3 */
	wk_dma1_channel3_init();
	/* config dma channel transfer parameter */
	/* user need to modify define values DMAx_CHANNELy_XXX_BASE_ADDR and DMAx_CHANNELy_BUFFER_SIZE in at32xxx_wk_config.h */
	wk_dma_channel_config(DMA1_CHANNEL3, 
							(uint32_t)&TMR2->c2dt, 
							DMA1_CHANNEL3_MEMORY_BASE_ADDR, 
							DMA1_CHANNEL3_BUFFER_SIZE);
	dma_channel_enable(DMA1_CHANNEL3, TRUE);
	

	/* init usart1 function. */
	wk_usart1_init();

	/* init usart2 function. */
	wk_usart2_init();

	/* init usb_otgfs1 function. */
	wk_usb_otgfs1_init();

	/* init spi2 function. */
	wk_spi2_init();

	/* init i2c2 function. */
	wk_i2c2_init();

	//  /* init adc-common function. */
	//  wk_adc_common_init();

	/* init adc1 function. */
	wk_adc1_init();

	/* init exint function. */
	wk_exint_config();

	/* init sdio1 function. */
	wk_sdio1_init();

	/* init gpio function. */
	wk_gpio_config();

	/* init tmr2 function. */
	wk_tmr2_init();

	/* init tmr3 function. */
	wk_tmr3_init();

	/* init tmr4 function. */
	wk_tmr4_init();

	/* init tmr5 function. */
	wk_tmr5_init();

	/* init tmr7 function. */
	wk_tmr7_init();

	/* add user code begin 2 */
	//	delay_init();
	tmr_counter_enable(TMR3, TRUE);
	tmr_counter_enable(TMR4, TRUE);
	tmr_period_value_set(TMR5, 1999);

	lcd_t300spro_init(); // 初始化T300SPRO LCD显示屏
	eeprom_Init(); // 初始化EEPROM
	para_reset(true); // 参数硬重置
	Board_init(); // 板级初始化
	UI_Data_Init(); // UI数据初始化
	Heater_reset(&Extruder_One, EX1); // 重置喷头1加热器
	CoolingFan_reset(&Extruder_One.Fan); // 重置喷头1冷却风扇
	Heater_reset(&Platform, HBP); // 重置平台加热器
	setup(); // Marlin固件初始化
	poweroff_startup(); // 断电启动处理
	Set_Fan_Power(0,0);	//设置风扇速度
	/* add user code end 2 */

	//tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, 255);		//关闭EX1PWM输出
	while(1) // 主循环
	{
		/* add user code begin 3 */
		//	USBH_Process(&USB_OTG_Core, &USB_Host);

		poweroff_setup_handler(); 	// 断电设置处理
		runBoardSlice(); 			// 运行板级任务切片
		StopPrintHandle(); 			// 停止打印处理
		loop(); 					// Marlin固件主循环

		if(UI_Page_info.Current_Page_Id != PAGE_TIPS_SUSPEND_PRINT_ID)
		{
			UI_Data_handle(); 			// UI数据处理
		}
		if(UI_Page_info.print_pause_flag == 1) // 如果打印暂停标志为1
		{
			UI_Page_info.print_pause_flag = 0; // 清除暂停标志
			Printing_pause_control(); // 执行打印暂停控制
		}
		//Panel_LED_Display(); // 面板LED显示
	}

//	if(wk_timebase_get()%1000 == 0)
//	{
//		printf("sys runing x:%d, y:%d z:%d\r\n",READ(X_MIN_PIN),READ(Y_MIN_PIN),READ(Z_MIN_PIN));
//	}

//	if(tmr7_ovf_flag > last_tmr7_ovf_flag)
//	{
//		last_tmr7_ovf_flag = tmr7_ovf_flag;
//		printf("t:%d %d\r\n",curr_time_cnt,step_status);
//	}
	
    /* add user code end 3 */
}

  /* add user code begin 4 */

  /* add user code end 4 */
