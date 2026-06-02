#ifndef __AT32F435_437_WK_CONFIG_H__
#define __AT32F435_437_WK_CONFIG_H__

#include "stdio.h"
#include "at32f435_437.h"

//引脚宏定义
//限位引脚
#define Y_LIMIT_PIN										GPIO_PINS_2
#define X_LIMIT_PIN										GPIO_PINS_0
#define Z_LIMIT_PIN										GPIO_PINS_1
#define Y_LIMIT_GPIO_PORT							GPIOE
#define X_LIMIT_GPIO_PORT							GPIOE
#define Z_LIMIT_GPIO_PORT							GPIOE

//低电压和TF卡引脚
#define LV_Det_PIN										GPIO_PINS_10
#define LV_Det_GPIO_PORT							GPIOD
#define	TF_Det_PIN										GPIO_PINS_3
#define	TF_Det_GPIO_PORT							GPIOD

//进出料引脚
#define	FIL_RUNOUT1_PIN								GPIO_PINS_6
#define	FIL_RUNOUT1_GPIO_PORT					GPIOC
#define FIL_RUNOUT2_PIN								GPIO_PINS_15
#define	FIL_RUNOUT2_GPIO_PORT					GPIOA


//GPIOA端口
#define	ENABLE_X_PIN									GPIO_PINS_0
#define	ENABLE_X_GPIO_PORT						GPIOA
#define	STEP_X_PIN										GPIO_PINS_1
#define	STEP_X_GPIO_PORT							GPIOA
#define	BlackOut_PIN									GPIO_PINS_4			//断电续打检测引脚
#define	BlackOut_GPIO_PORT						GPIOA
#define	ENABLE_Z_PIN									GPIO_PINS_5
#define	ENBALE_Z_GPIO_PORT						GPIOA
#define STEP_Z_PIN										GPIO_PINS_6
#define	STEP_Z_GPIO_PORT							GPIOA
#define	DIR_Z_PIN											GPIO_PINS_7
#define	DIR_Z_GPIO_PORT								GPIOA
#define DIR_E1_PIN										GPIO_PINS_8
#define	DIR_E1_GPIO_PORT							GPIOA

//GPIOC端口
#define	ENABLE_Y_PIN									GPIO_PINS_4
#define	ENABLE_Y_GPIO_PORT						GPIOC
#define DIR_X_PIN											GPIO_PINS_5
#define DIR_X_GPIO_PORT								GPIOC


//GPIOE端口
#define DIR_Y_PIN											GPIO_PINS_11
#define	DIR_Y_GPIO_PORT								GPIOE
#define	STEP_Y_PIN										GPIO_PINS_12
#define	STEP_Y_GPIO_PORT							GPIOE
#define	ENABLE_E0_PIN									GPIO_PINS_13
#define	ENABLE_E0_GPIO_PORT						GPIOE
#define	STEP_E0_PIN										GPIO_PINS_14				//在原理图上，挤出机1叫做E1；在代码宏定义中，挤出机叫做E0；这个设计的有点乱
#define	STEP_E0_GPIO_PORT							GPIOE
#define	DIR_E0_PIN										GPIO_PINS_15
#define	DIR_E0_GPIO_PORT							GPIOE

//GPIOB端口
#define	FLASH_CS_PIN									GPIO_PINS_12
#define	FLASH_CS_GPIO_PORT						GPIOB

//GPIOD端口
#define	ENDLED_DRV_PIN								GPIO_PINS_11			//指示灯
#define ENDLED_DRV_GPIO_PORT					GPIOD
#define	BOX_FAN1_GPIO_PIN							GPIO_PINS_0
#define	BOX_FAN1_GPIO_PORT						GPIOD
#define	BOX_FAN2_GPIO_PIN							GPIO_PINS_1
#define BOX_FAN_GPIO_PORT							GPIOD
#define	ENABLE_E1_PIN									GPIO_PINS_6
#define	ENABLE_E1_GPIO_PORT						GPIOD
#define STEP_E1_PIN										GPIO_PINS_7
#define	STEP_E1_GPIO_PORT							GPIOB










//函数声明
void wk_periph_clock_config(void);

#endif
