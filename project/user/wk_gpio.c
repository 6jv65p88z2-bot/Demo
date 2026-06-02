#include "wk_gpio.h"
#include "wk_system.h"

/**
  * @brief  一次性配置所有的引脚初始化
  * @param  none
  * @retval none
  */

void wk_gpio_config(void)
{
	gpio_init_type gpio_init_struct;
	gpio_default_para_init(&gpio_init_struct);
	
	//输入引脚设置
	//X Y Z轴三轴的限位开关 Z轴分为Z1-->PE1   Z2-->PE3
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = Y_LIMIT_PIN | X_LIMIT_PIN | Z_LIMIT_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOE,&gpio_init_struct);
	
	//低电压 TF卡引脚
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = LV_Det_PIN | TF_Det_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOD,&gpio_init_struct);
	
	//进出料引脚
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = FIL_RUNOUT1_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(FIL_RUNOUT1_GPIO_PORT,&gpio_init_struct);
	
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = FIL_RUNOUT2_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(FIL_RUNOUT2_GPIO_PORT,&gpio_init_struct);
	
	
	//输出引脚设置
	//把在同一个端口下的引脚，全部置0
	gpio_bits_reset(GPIOA,ENABLE_X_PIN | STEP_X_PIN | BlackOut_PIN | ENABLE_Z_PIN | STEP_Z_PIN | DIR_Z_PIN | DIR_E1_PIN);
	gpio_bits_reset(GPIOC,ENABLE_Y_PIN | DIR_X_PIN);
	gpio_bits_reset(GPIOE,DIR_Y_PIN | STEP_Y_PIN | ENABLE_E0_PIN | STEP_E0_PIN | DIR_E0_PIN);
	gpio_bits_set(FLASH_CS_GPIO_PORT,FLASH_CS_PIN);		//默认不选中FLASH
	gpio_bits_reset(GPIOD,ENDLED_DRV_PIN | BOX_FAN1_GPIO_PIN | BOX_FAN2_GPIO_PIN | ENABLE_E1_PIN);
	gpio_bits_reset(STEP_E1_GPIO_PORT,STEP_E1_PIN);
	
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = ENABLE_X_PIN | STEP_X_PIN | ENABLE_Z_PIN | STEP_Z_PIN | DIR_Z_PIN | DIR_E1_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOA,&gpio_init_struct);
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = BlackOut_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(BlackOut_GPIO_PORT,&gpio_init_struct);
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = ENABLE_Y_PIN | DIR_X_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOC,&gpio_init_struct);
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = DIR_Y_PIN | STEP_Y_PIN | ENABLE_E0_PIN | STEP_E0_PIN | DIR_E0_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOE,&gpio_init_struct);
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins = FLASH_CS_PIN | STEP_E1_PIN;
	gpio_init(GPIOB,&gpio_init_struct);
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pins =	ENDLED_DRV_PIN | BOX_FAN1_GPIO_PIN | BOX_FAN2_GPIO_PIN | ENABLE_E1_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOD,&gpio_init_struct);

}

void TurnOnLed(void)
{
	gpio_bits_set(ENDLED_DRV_GPIO_PORT,ENDLED_DRV_PIN);
}

void TurnOffLed(void)
{
	gpio_bits_reset(ENDLED_DRV_GPIO_PORT,ENDLED_DRV_PIN);
}

void TurnReverse(void)
{
	printf("LED_On\r\n");
	gpio_bits_set(ENDLED_DRV_GPIO_PORT,ENDLED_DRV_PIN);
	
	wk_delay_ms(500);
		printf("LED_Off\r\n");
	gpio_bits_reset(ENDLED_DRV_GPIO_PORT,ENDLED_DRV_PIN);

}