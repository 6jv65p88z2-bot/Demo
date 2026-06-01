/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_adc.c
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
#include "wk_adc.h"

/* add user code begin 0 */

volatile uint16_t ADC_ConvertedValue[8][4];

/**
  * @brief  dma configuration.
  * @param  none
  * @retval none
  */
static void dma_config(void)
{
  dma_init_type dma_init_struct;
  crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
  nvic_irq_enable(DMA1_Channel1_IRQn, 0, 0);

  dma_reset(DMA1_CHANNEL1);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = 32;		//dma缓冲区大小，每个通道24个数据字节
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)ADC_ConvertedValue;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&(ADC1->odt);
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_HIGH;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL1, &dma_init_struct);

  dmamux_enable(DMA1, TRUE);
  dmamux_init(DMA1MUX_CHANNEL1, DMAMUX_DMAREQ_ID_ADC1);

  /* enable dma transfer complete interrupt */
  dma_interrupt_enable(DMA1_CHANNEL1, DMA_FDT_INT, TRUE);
  dma_channel_enable(DMA1_CHANNEL1, TRUE);
}

/**
  * @brief  adc configuration.
  * @param  none
  * @retval none
  */
static void adc_config(void)
{
  adc_common_config_type adc_common_struct;
  adc_base_config_type adc_base_struct;
  crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
  nvic_irq_enable(ADC1_2_3_IRQn, 0, 0);

  adc_common_default_para_init(&adc_common_struct);

  /* config combine mode */
  adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;

  /* config division,adcclk is division by hclk */
  adc_common_struct.div = ADC_HCLK_DIV_4;

  /* config common dma mode,it's not useful in independent mode */
  adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;

  /* config common dma request repeat */
  adc_common_struct.common_dma_request_repeat_state = FALSE;

  /* config adjacent adc sampling interval,it's useful for ordinary shifting mode */
  adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;

  /* config inner temperature sensor and vintrv */
  adc_common_struct.tempervintrv_state = FALSE;

  /* config voltage battery */
  adc_common_struct.vbat_state = FALSE;
  adc_common_config(&adc_common_struct);

  adc_base_default_para_init(&adc_base_struct);

  adc_base_struct.sequence_mode = TRUE;
  adc_base_struct.repeat_mode = TRUE;
  adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
  adc_base_struct.ordinary_channel_length = 4;
  adc_base_config(ADC1, &adc_base_struct);
  adc_resolution_set(ADC1, ADC_RESOLUTION_12B);

  /* config ordinary channel */
  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_11, 1, ADC_SAMPLETIME_47_5);   //喷头1温度检测
  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_12, 2, ADC_SAMPLETIME_47_5);   //热床温度检测
  //adc_ordinary_channel_set(ADC1, ADC_CHANNEL_13, 3, ADC_SAMPLETIME_47_5);   //喷头2温度检测
  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_8, 3, ADC_SAMPLETIME_47_5);   //底部机箱温度检测
  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_9, 4, ADC_SAMPLETIME_47_5);   //机箱温度检测

  /* config ordinary trigger source and trigger edge */
  adc_ordinary_conversion_trigger_set(ADC1, ADC_ORDINARY_TRIG_TMR1CH1, ADC_ORDINARY_TRIG_EDGE_NONE);

  /* config dma mode,it's not useful when common dma mode is use */
  adc_dma_mode_enable(ADC1, TRUE);

  /* config dma request repeat,it's not useful when common dma mode is use */
  adc_dma_request_repeat_enable(ADC1, TRUE);

  /* enable adc overflow interrupt */
  adc_interrupt_enable(ADC1, ADC_OCCO_INT, TRUE);

  /* adc enable */
  adc_enable(ADC1, TRUE);
  while(adc_flag_get(ADC1, ADC_RDY_FLAG) == RESET);

  /* adc calibration */
  adc_calibration_init(ADC1);
  while(adc_calibration_init_status_get(ADC1));
  adc_calibration_start(ADC1);
  while(adc_calibration_status_get(ADC1));
}

/* add user code end 0 */

/**
  * @brief  init adc-common function.
  * @param  none
  * @retval none
  */
void wk_adc_common_init(void)
{
  /* add user code begin adc_common_init 0 */

  /* add user code end adc_common_init 0 */

  adc_common_config_type adc_common_struct;

  /* add user code begin adc_common_init 1 */

  /* add user code end adc_common_init 1 */
  
  /* adc_common_settings------------------------------------------------------------ */
  adc_common_default_para_init(&adc_common_struct);
  adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;
  adc_common_struct.div = ADC_HCLK_DIV_4;
  adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;
  adc_common_struct.common_dma_request_repeat_state = FALSE;
  adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;
  adc_common_struct.tempervintrv_state = FALSE;
  adc_common_struct.vbat_state = FALSE;
  adc_common_config(&adc_common_struct);
  
  /* add user code begin adc_common_init 2 */

  /* add user code end adc_common_init 2 */
}

/**
  * @brief  init adc1 function.
  * @param  none
  * @retval none
  */
void wk_adc1_init(void)
{
  /* add user code begin adc1_init 0 */

  /* add user code end adc1_init 0 */

  gpio_init_type gpio_init_struct;
////  adc_base_config_type adc_base_struct;

  gpio_default_para_init(&gpio_init_struct);

//  /* add user code begin adc1_init 1 */
//	
//  /* add user code end adc1_init 1 */

  /*gpio--------------------------------------------------------------------*/ 
  /* configure the IN8 pin */
  gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
  gpio_init_struct.gpio_pins = TEMP_BOTBOX_PIN;
  gpio_init(TEMP_BOTBOX_GPIO_PORT, &gpio_init_struct);

  /* configure the IN9 pin */
  gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
  gpio_init_struct.gpio_pins = TEMP_BOX_PIN;
  gpio_init(TEMP_BOX_GPIO_PORT, &gpio_init_struct);

  /* configure the IN11 pin */
  gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
  gpio_init_struct.gpio_pins = TEMP_E0_PIN;
  gpio_init(TEMP_E0_GPIO_PORT, &gpio_init_struct);

  /* configure the IN12 pin */
  gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
  gpio_init_struct.gpio_pins = TEMP_BED_PIN;
  gpio_init(TEMP_BED_GPIO_PORT, &gpio_init_struct);

  /* configure the IN13 pin */
//   gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
//   gpio_init_struct.gpio_pins = TEMP_E1_PIN;
//   gpio_init(TEMP_E1_GPIO_PORT, &gpio_init_struct);

	dma_config();
	adc_config();
//  /* adc_settings------------------------------------------------------------------- */
//  adc_base_default_para_init(&adc_base_struct);
//  adc_base_struct.sequence_mode = TRUE;
//  adc_base_struct.repeat_mode = TRUE;
//  adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
//  adc_base_struct.ordinary_channel_length = 3;
//  adc_base_config(ADC1, &adc_base_struct);

//  adc_resolution_set(ADC1, ADC_RESOLUTION_12B);

//  /* adc_ordinary_conversionmode---------------------------------------------------- */
//  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_11, 1, ADC_SAMPLETIME_12_5);
//  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_12, 2, ADC_SAMPLETIME_12_5);
//  adc_ordinary_channel_set(ADC1, ADC_CHANNEL_13, 3, ADC_SAMPLETIME_12_5);

//  adc_ordinary_conversion_trigger_set(ADC1, ADC_ORDINARY_TRIG_TMR1CH1, ADC_ORDINARY_TRIG_EDGE_NONE);

//  adc_dma_mode_enable(ADC1, TRUE);

//  /**
//   * Users need to configure ADC1 interrupt functions according to the actual application.
//   * 1. Call the below function to enable the corresponding ADC1 interrupt.
//   *     --adc_interrupt_enable(...)
//   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
//   *     --void ADC1_2_3_IRQHandler(void)
//   */

//  /* ordinary overflow interrupt-------------------------------------------------------------- */
//  adc_interrupt_enable(ADC1, ADC_OCCO_INT, TRUE);

//  /* add user code begin adc1_init 2 */
////	adc_interrupt_enable(ADC1, ADC_PCCE_INT, TRUE);
//  /* add user code end adc1_init 2 */

//  adc_enable(ADC1, TRUE);
//  while(adc_flag_get(ADC1, ADC_RDY_FLAG) == RESET);

//  /* adc calibration---------------------------------------------------------------- */
//  adc_calibration_init(ADC1);
//  while(adc_calibration_init_status_get(ADC1));
//  adc_calibration_start(ADC1);
//  while(adc_calibration_status_get(ADC1));

//  /* add user code begin adc1_init 3 */
//  DMA1_CHANNEL1->dtcnt = 24;
//  DMA1_CHANNEL1->maddr = (uint32_t)ADC_ConvertedValue;
//  DMA1_CHANNEL1->paddr = (uint32_t)&(ADC1->odt);
//  dma_channel_enable(DMA1_CHANNEL1, TRUE);
  /* add user code end adc1_init 3 */
}

/* add user code begin 1 */

/* add user code end 1 */
