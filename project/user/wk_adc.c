#include "wk_adc.h"


volatile uint16_t ADC_ConvertedValue[8][4];		//ADC采样后的内存缓冲区


/**
  * @brief  DMA设置
  * @param  none
  * @retval none
  */
static void dma_config(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK,TRUE); //使能DMA时钟
	//使能DMA中断,并且抢占优先级和继承优先级均为0
	nvic_irq_enable(DMA1_Channel1_IRQn,0,0);
	
	//DMA复位和默认参数初始化
	dma_reset(DMA1_CHANNEL1);
	dma_default_para_init(&dma_init_struct);
	//配置DMA
	dma_init_struct.peripheral_base_addr = (uint32_t)&ADC1->odt;  //ADC的数据寄存器
	dma_init_struct.peripheral_inc_enable = FALSE;	//外设地址自增失能
	dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
	dma_init_struct.memory_base_addr = (uint32_t)ADC_ConvertedValue;	//读取到内存地址ADC_ConvertedValue
	dma_init_struct.memory_inc_enable = TRUE;//内存地址自增使能
	dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
	
	dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;	//外设->内存
	dma_init_struct.buffer_size = 32;		// 每个通道24个字节
	dma_init_struct.loop_mode_enable = FALSE;	//非循环模式
	dma_init_struct.priority = DMA_PRIORITY_HIGH;//高优先级
	dma_init(DMA1_CHANNEL1,&dma_init_struct);
	
	//ADC1通道映射到DMA
	dmamux_enable(DMA1,TRUE);
	dmamux_init(DMA1MUX_CHANNEL1,DMAMUX_DMAREQ_ID_ADC1);  //ADC1请求映射到DMA1的通道
	//启用DMA传输完成中断
	dma_interrupt_enable(DMA1_CHANNEL1,DMA_FDT_INT,TRUE);
	dma_channel_enable(DMA1_CHANNEL1,TRUE);
}

/**
  * @brief  ADC configuration.
  * @param  none
  * @retval none
  */

static void adc_config(void)
{
	adc_common_config_type adc_common_struct;		//相同设置
	adc_base_config_type adc_base_struct;				//基础设置
	
	//开启ADC外设时钟并且使能ADC中断管理，且完成默认参数设置
	crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK,TRUE);
	nvic_irq_enable(ADC1_2_3_IRQn,0,0);
	adc_common_default_para_init(&adc_common_struct);
	//对adc_common_struct进行配置
	adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;		//独立模式
	adc_common_struct.div = ADC_HCLK_DIV_4;		//4分频
	adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;
	adc_common_struct.common_dma_request_repeat_state = FALSE;
	adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;	//47.5个周期
	adc_common_struct.tempervintrv_state = FALSE;
	adc_common_struct.vbat_state = FALSE;
	adc_common_config(&adc_common_struct);		//对此结构进行注册
	
	
	//对adc_base_struct进行配置
	adc_base_default_para_init(&adc_base_struct);
	adc_base_struct.sequence_mode =  TRUE;	//序列模式
	adc_base_struct.repeat_mode = TRUE;		//重复模式
	adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;		//左对齐
	adc_base_struct.ordinary_channel_length = 4;				//4个通道
	adc_base_config(ADC1,&adc_base_struct);
	
	adc_resolution_set(ADC1,ADC_RESOLUTION_12B)	;//12位分辨率
	
	
	//设置ADC1的4个通道采样
	adc_ordinary_channel_set(ADC1,ADC_CHANNEL_11,1,ADC_SAMPLETIME_47_5);						//喷头1温度检测
	adc_ordinary_channel_set(ADC1,ADC_CHANNEL_12,2,ADC_SAMPLETIME_47_5);						//热床温度检测
	adc_ordinary_channel_set(ADC1,ADC_CHANNEL_8,3,ADC_SAMPLETIME_47_5);						//底部机箱温度检测
	adc_ordinary_channel_set(ADC1,ADC_CHANNEL_9,4,ADC_SAMPLETIME_47_5);						//整机机箱温度检测
	//触发ADC转换
	adc_ordinary_conversion_trigger_set(ADC1,ADC_ORDINARY_TRIG_TMR1CH1,ADC_ORDINARY_TRIG_EDGE_NONE);	//TIM1中断，则触发ADC转换
	//开启ADC->DMA的链路
	adc_dma_mode_enable(ADC1,TRUE);	//ADC->DMA
	
	//开启ADC->DMA的请求
	adc_dma_request_repeat_enable(ADC1,TRUE);		//请求接续使能
	//使能ADC1中断
	adc_interrupt_enable(ADC1,ADC_OCCO_INT,TRUE);		//普通通道转换溢出使能中断
	//开启ADC并等待
	adc_enable(ADC1,TRUE);
	while(adc_flag_get(ADC1,ADC_RDY_FLAG) == RESET);		//说明开启未完成，继续等待开启成功，则标志位会被置位为SET
	//ADC校准
	adc_calibration_init(ADC1);//初始化校准
	while(adc_calibration_init_status_get(ADC1));	//等待初始化校准完成
	adc_calibration_start(ADC1);//开始校准
	while(adc_calibration_status_get(ADC1));	//等待校准完成

}