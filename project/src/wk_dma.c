/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_dma.c
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
#include "wk_dma.h"

/* add user code begin 0 */

/*-熊-*/
volatile uint8_t dma_status = 0;	// DMA状态标志位
uint8_t dma_buffer[DMA2_CHANNEL4_BUFFER_SIZE];	// dma接收缓存数组
#define DMA_STATUS_IDLE          0x00  // 空闲状态
#define DMA_STATUS_TRANSFERRING  0x01  // 正在传输
#define DMA_STATUS_COMPLETE      0x02  // 传输完成
#define DMA_STATUS_ERROR         0x04  // 传输错误
#define DMA_STATUS_HALF_COMPLETE 0x08  // 半传输完成
// DMA控制结构
typedef struct 
{
    uint8_t *buffer;          // 缓冲区指针
    uint32_t buffer_size;     // 缓冲区大小
    uint32_t transfer_count;  // 已传输字节数
    uint32_t total_count;     // 总需要传输字节数
    uint8_t status;           // 状态
    uint8_t error_code;       // 错误代码
} dma_ctrl_t;
dma_ctrl_t dma_ctrl = {0};

/* add user code end 0 */

/**
  * @brief  init dma1 channel1 for "adc1"
  * @param  none
  * @retval none
  */
void wk_dma1_channel1_init(void)
{
  /* add user code begin dma1_channel1 0 */

  /* add user code end dma1_channel1 0 */

  dma_init_type dma_init_struct;

  dma_reset(DMA1_CHANNEL1);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_HIGH;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL1, &dma_init_struct);

  /* dmamux function enable */
  dmamux_enable(DMA1, TRUE);
  dmamux_init(DMA1MUX_CHANNEL1, DMAMUX_DMAREQ_ID_ADC1);

  /**
   * Users need to configure DMA1 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding DMA1 interrupt.
   *     --dma_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void DMA1_Channel1_IRQHandler(void)
   */ 
  /* add user code begin dma1_channel1 1 */
	dma_interrupt_enable(DMA1_CHANNEL1, DMA_FDT_INT, TRUE);
  /* add user code end dma1_channel1 1 */
}

/**
  * @brief  init dma1 channel2 for "usart2_tx"
  * @param  none
  * @retval none
  */
void wk_dma1_channel2_init(void)
{
  /* add user code begin dma1_channel2 0 */

  /* add user code end dma1_channel2 0 */

  dma_init_type dma_init_struct;

  dma_reset(DMA1_CHANNEL2);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_LOW;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL2, &dma_init_struct);

  /* dmamux function enable */
  dmamux_enable(DMA1, TRUE);
  dmamux_init(DMA1MUX_CHANNEL2, DMAMUX_DMAREQ_ID_USART2_TX);

  /**
   * Users need to configure DMA1 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding DMA1 interrupt.
   *     --dma_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void DMA1_Channel2_IRQHandler(void)
   */ 
  /* add user code begin dma1_channel2 1 */

  /* add user code end dma1_channel2 1 */
}

/**
  * @brief  init dma1 channel3 for "tmr2_ch2"
  * @param  none
  * @retval none
  */
void wk_dma1_channel3_init(void)
{
  /* add user code begin dma1_channel3 0 */

  /* add user code end dma1_channel3 0 */

  dma_init_type dma_init_struct;

  dma_reset(DMA1_CHANNEL3);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_HIGH;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA1_CHANNEL3, &dma_init_struct);

  /* dmamux function enable */
  dmamux_enable(DMA1, TRUE);
  dmamux_init(DMA1MUX_CHANNEL3, DMAMUX_DMAREQ_ID_TMR2_CH2);

  /**
   * Users need to configure DMA1 interrupt functions according to the actual application.
   * 1. Call the below function to enable the corresponding DMA1 interrupt.
   *     --dma_interrupt_enable(...)
   * 2. Add the user's interrupt handler code into the below function in the at32f435_437_int.c file.
   *     --void DMA1_Channel3_IRQHandler(void)
   */ 
  /* add user code begin dma1_channel3 1 */

  /* add user code end dma1_channel3 1 */
}

/**
  * @brief  config dma channel transfer parameter
  * @param  dmax_channely: DMAx_CHANNELy
  * @param  peripheral_base_addr: peripheral address.
  * @param  memory_base_addr: memory address.
  * @param  buffer_size: buffer size.
  * @retval none
  */
void wk_dma_channel_config(dma_channel_type* dmax_channely, uint32_t peripheral_base_addr, uint32_t memory_base_addr, uint16_t buffer_size)
{
  /* add user code begin dma_channel_config 0 */

  /* add user code end dma_channel_config 0 */

  dmax_channely->dtcnt = buffer_size;
  dmax_channely->paddr = peripheral_base_addr;
  dmax_channely->maddr = memory_base_addr;

  /* add user code begin dma_channel_config 1 */

  /* add user code end dma_channel_config 1 */
}

/* add user code begin 1 */

/* add user code end 1 */