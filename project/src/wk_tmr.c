/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_tmr.c
  * @brief    work bench config program
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
#include "wk_tmr.h"

/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief  init tmr2 function.
  * @param  none
  * @retval none
  */
void wk_tmr2_init(void)
{
  /* add user code begin tmr2_init 0 */

  /* add user code end tmr2_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_output_config_type tmr_output_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr2_init 1 */

  /* add user code end tmr2_init 1 */

  /* configure the CH2 pin */
  gpio_pin_mux_config(RGB_DRV_GPIO_PORT, GPIO_PINS_SOURCE3, GPIO_MUX_1);
  gpio_init_struct.gpio_pins = RGB_DRV_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(RGB_DRV_GPIO_PORT, &gpio_init_struct);

  /* configure counter settings */
  tmr_base_init(TMR2, 143, 0);
  tmr_cnt_dir_set(TMR2, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR2, TMR_CLOCK_DIV1);
  tmr_period_buffer_enable(TMR2, FALSE);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR2, FALSE);
  tmr_primary_mode_select(TMR2, TMR_PRIMARY_SEL_RESET);

  /* configure one cycle mode */
  tmr_one_cycle_mode_enable(TMR2, TRUE);

  /* configure channel 2 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR2, TMR_SELECT_CHANNEL_2, &tmr_output_struct);
  tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_2, 0);
  tmr_output_channel_buffer_enable(TMR2, TMR_SELECT_CHANNEL_2, FALSE);

  tmr_output_channel_immediately_set(TMR2, TMR_SELECT_CHANNEL_2, TRUE);


  /* configure dma ch2 */
  tmr_dma_request_enable(TMR2, TMR_C2_DMA_REQUEST, TRUE);
  tmr_counter_enable(TMR2, TRUE);

  /**
   * Users need to configure TMR2 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding TMR2 interrupt.
   *     --tmr_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void TMR2_GLOBAL_IRQHandler(void)
   */

  /* add user code begin tmr2_init 2 */

  /* add user code end tmr2_init 2 */
}

/**
  * @brief  init tmr3 function.
  * @param  none
  * @retval none
  */
void wk_tmr3_init(void)
{
  /* add user code begin tmr3_init 0 */

  /* add user code end tmr3_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_output_config_type tmr_output_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr3_init 1 */

  /* add user code end tmr3_init 1 */

  /* configure the CH1 pin */
  gpio_pin_mux_config(TM3_CH1_HOT_E1_GPIO_PORT, GPIO_PINS_SOURCE4, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = TM3_CH1_HOT_E1_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(TM3_CH1_HOT_E1_GPIO_PORT, &gpio_init_struct);
  gpio_bits_reset(GPIOB, TM3_CH1_HOT_E1_PIN);

  /* configure the CH2 pin */
  gpio_pin_mux_config(TM3_CH2_HOT_E0_GPIO_PORT, GPIO_PINS_SOURCE5, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = TM3_CH2_HOT_E0_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(TM3_CH2_HOT_E0_GPIO_PORT, &gpio_init_struct);

  /* configure counter settings */
  tmr_base_init(TMR3, 255, 11299);
  tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);
  tmr_period_buffer_enable(TMR3, FALSE);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR3, FALSE);
  tmr_primary_mode_select(TMR3, TMR_PRIMARY_SEL_RESET);

  /* configure channel 1 output settings */     //EX1PWM输出
 tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
 tmr_output_struct.oc_output_state = TRUE;
 tmr_output_struct.occ_output_state = FALSE;
 tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
 tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
 tmr_output_struct.oc_idle_state = FALSE;
 tmr_output_struct.occ_idle_state = FALSE;
 tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
 tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, 0);
 tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_1, FALSE);

 tmr_output_channel_immediately_set(TMR3, TMR_SELECT_CHANNEL_1, TRUE);

  /* configure channel 2 output settings */     //EX0PWM输出(当前只有这一个被使用)
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_2, &tmr_output_struct);
  tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, 0);
  tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_2, FALSE);

  tmr_output_channel_immediately_set(TMR3, TMR_SELECT_CHANNEL_2, TRUE);

  tmr_counter_enable(TMR3, TRUE);

  /**
   * Users need to configure TMR3 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding TMR3 interrupt.
   *     --tmr_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void TMR3_GLOBAL_IRQHandler(void)
   */

  /* add user code begin tmr3_init 2 */

  /* add user code end tmr3_init 2 */
}

/**
  * @brief  init tmr4 function.
  * @param  none
  * @retval none
  */
void wk_tmr4_init(void)
{
  /* add user code begin tmr4_init 0 */

  /* add user code end tmr4_init 0 */

  gpio_init_type gpio_init_struct;
  tmr_output_config_type tmr_output_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin tmr4_init 1 */

  /* add user code end tmr4_init 1 */

  /* configure the CH1 pin */
  gpio_pin_mux_config(TM4_CH1_HOT_BED_GPIO_PORT, GPIO_PINS_SOURCE6, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = TM4_CH1_HOT_BED_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(TM4_CH1_HOT_BED_GPIO_PORT, &gpio_init_struct);

  /* configure the CH3 pin */
  gpio_pin_mux_config(TM4_CH3_FAN0_GPIO_PORT, GPIO_PINS_SOURCE8, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = TM4_CH3_FAN0_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(TM4_CH3_FAN0_GPIO_PORT, &gpio_init_struct);

  /* configure the CH4 pin */
  gpio_pin_mux_config(TM4_CH4_FAN1_GPIO_PORT, GPIO_PINS_SOURCE9, GPIO_MUX_2);
  gpio_init_struct.gpio_pins = TM4_CH4_FAN1_PIN;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(TM4_CH4_FAN1_GPIO_PORT, &gpio_init_struct);

  /* configure counter settings */
  tmr_base_init(TMR4, 255, 11299);
  tmr_cnt_dir_set(TMR4, TMR_COUNT_UP);
  tmr_clock_source_div_set(TMR4, TMR_CLOCK_DIV1);
  tmr_period_buffer_enable(TMR4, FALSE);

  /* configure primary mode settings */
  tmr_sub_sync_mode_set(TMR4, FALSE);
  tmr_primary_mode_select(TMR4, TMR_PRIMARY_SEL_RESET);

  /* configure channel 1 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR4, TMR_SELECT_CHANNEL_1, &tmr_output_struct);
  tmr_channel_value_set(TMR4, TMR_SELECT_CHANNEL_1, 0);
  tmr_output_channel_buffer_enable(TMR4, TMR_SELECT_CHANNEL_1, FALSE);

  tmr_output_channel_immediately_set(TMR4, TMR_SELECT_CHANNEL_1, FALSE);

  /* configure channel 3 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR4, TMR_SELECT_CHANNEL_3, &tmr_output_struct);
  tmr_channel_value_set(TMR4, TMR_SELECT_CHANNEL_3, 0);
  tmr_output_channel_buffer_enable(TMR4, TMR_SELECT_CHANNEL_3, FALSE);

  tmr_output_channel_immediately_set(TMR4, TMR_SELECT_CHANNEL_3, FALSE);

  /* configure channel 4 output settings */
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.occ_output_state = FALSE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
  tmr_output_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct.oc_idle_state = FALSE;
  tmr_output_struct.occ_idle_state = FALSE;
  tmr_output_channel_config(TMR4, TMR_SELECT_CHANNEL_4, &tmr_output_struct);
  tmr_channel_value_set(TMR4, TMR_SELECT_CHANNEL_4, 0);
  tmr_output_channel_buffer_enable(TMR4, TMR_SELECT_CHANNEL_4, FALSE);

  tmr_output_channel_immediately_set(TMR4, TMR_SELECT_CHANNEL_4, FALSE);


  tmr_counter_enable(TMR4, TRUE);

  /**
   * Users need to configure TMR4 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding TMR4 interrupt.
   *     --tmr_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void TMR4_GLOBAL_IRQHandler(void)
   */

  /* add user code begin tmr4_init 2 */

  /* add user code end tmr4_init 2 */
}


/**
  * @brief  init tmr5 function.
  * @param  none
  * @retval none
  */
void wk_tmr5_init(void)
{
	/* add user code begin tmr5_init 0 */

	/* add user code end tmr5_init 0 */


	/* add user code begin tmr5_init 1 */

	/* add user code end tmr5_init 1 */

	/* configure counter settings */
	tmr_base_init(TMR5, 1638, 175);
	tmr_cnt_dir_set(TMR5, TMR_COUNT_UP);
	tmr_clock_source_div_set(TMR5, TMR_CLOCK_DIV1);
	tmr_period_buffer_enable(TMR5, FALSE);

	/* configure primary mode settings */
	tmr_primary_mode_select(TMR5, TMR_PRIMARY_SEL_RESET);

	tmr_counter_enable(TMR5, TRUE);

	/**
	* Users need to configure TMR5 interrupt functions according to the actual application.
	* 1. Call the below function to enable the corresponding TMR5 interrupt.
	*     --tmr_interrupt_enable(...)
	* 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
	*     --void TMR5_GLOBAL_IRQHandler(void)
	*/

	/* add user code begin tmr5_init 2 */
	tmr_interrupt_enable(TMR5, TMR_OVF_INT, TRUE);
	
	// 重新开启计数器
	tmr_counter_enable(TMR5, TRUE);

	/* add user code begin tmr5_init 2 */
	// 可选：清除初始中断标志（避免上电就触发无效中断）
	tmr_flag_clear(TMR5, TMR_OVF_FLAG);
	/* add user code end tmr5_init 2 */
}

/**
  * @brief  init tmr7 function.
  * @param  none
  * @retval none
  */
void wk_tmr7_init(void)
{
  /* add user code begin tmr7_init 0 */

  /* add user code end tmr7_init 0 */

  /* add user code begin tmr7_init 1 */

  /* add user code end tmr7_init 1 */

  /* configure counter settings */
  tmr_base_init(TMR7, 16384, 143);
  tmr_cnt_dir_set(TMR7, TMR_COUNT_UP);
  tmr_period_buffer_enable(TMR7, FALSE);

  /* configure primary mode settings */
  tmr_primary_mode_select(TMR7, TMR_PRIMARY_SEL_RESET);

  tmr_counter_enable(TMR7, TRUE);

  /**
   * Users need to configure TMR7 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding TMR7 interrupt.
   *     --tmr_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void TMR7_GLOBAL_IRQHandler(void)
   */

  /* add user code begin tmr7_init 2 */
	tmr_interrupt_enable(TMR7, TMR_OVF_INT, TRUE);
  /* add user code end tmr7_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
