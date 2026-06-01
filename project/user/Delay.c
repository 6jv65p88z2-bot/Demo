#include "Delay.h"


 #define STEP_DELAY_MS  1820 //1820ms的延时
 
 static uint64_t fac_us = 0; //us延时倍乘数
 static uint64_t fac_ms = 0; //ms延时倍乘数


/**
  * @brief  初始化时钟延时函数
  * @param  none
  * @retval none
  */

 void delay_Init(void)
 {
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_DIV8); //选择外部时钟 HCLK/8
    fac_us = system_core_clock / 8 / (1000000U);        //1hz = 36us
    fac_ms = fac_us * 1000U;    
 }

/**
  * @brief  微秒级延时函数
  * @param  nus: 延时的微秒数
  * @retval none
  */

void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = nus * fac_us; //时间加载
    SysTick->VAL = 0x00;           //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数,启用SysTick
    do
    {
        temp = SysTick->CTRL;   //读取当前计数器状态
    } while ((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;         //关闭SysTick
    SysTick->VAL = 0x00; //清空计数器

}

/**
  * @brief  毫秒级延时函数
  * @param  nms: 延时的毫秒数
  * @retval none
  */

void delay_ms(uint32_t nms)
{
    uint32_t temp;
    while (nms)
    {
        /*
            为什么要分段加载？因为SysTick的计数器是24位的，最大值为0xFFFFFF（16777215），
            如果直接加载一个较大的值，可能会导致计数器溢出，无法正确计时。
            因此，我们将较大的延时分成多个小段，每段不超过STEP_DELAY_MS，
            这样就能确保每次加载的值都在计数器的范围内，保证延时的准确性。
        */
        if(nms > STEP_DELAY_MS)
        {
            SysTick->LOAD = STEP_DELAY_MS * fac_ms; //时间加载
            nms -= STEP_DELAY_MS;
        }
        else
        {
            SysTick->LOAD = nms * fac_ms; //时间加载
            nms = 0;
        }
        SysTick->VAL = 0x00;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数,启用SysTick
        do
        {
            temp = SysTick->CTRL;   //读取当前计数器状态
        } while ((temp & 0x01) && !(temp << 16));
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        SysTick->VAL = 0; //清空计数器
    }
}