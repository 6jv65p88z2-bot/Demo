#include "wk_usart.h"

void wk_usart1_init(void)
{
	//1.
	gpio_init_type gpio_init_struct;
	gpio_default_para_init(&gpio_init_struct);
	
	//2.配置PA9为USART1_TX
    gpio_pin_mux_config(GPIOA,GPIO_PINS_SOURCE9,GPIO_MUX_7);
		gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pull  = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_pins = GPIO_PINS_9;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init(GPIOA,&gpio_init_struct);

    //3.配置PA10为USART1_RX
    gpio_pin_mux_config(GPIOA,GPIO_PINS_SOURCE10,GPIO_MUX_7);
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_pins = GPIO_PINS_10;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init(GPIOA,&gpio_init_struct);

    //4.配置USART1
    usart_init(USART1,115200,USART_DATA_8BITS,USART_STOP_1_BIT);
		usart_transmitter_enable(USART1,TRUE);
    usart_receiver_enable(USART1,TRUE);
    usart_parity_selection_config(USART1, USART_PARITY_NONE);
		usart_hardware_flow_control_set(USART1, USART_HARDWARE_FLOW_NONE);
		
    usart_enable(USART1,TRUE);
}

void wk_usart2_init(void)
{
	//1.
	gpio_init_type gpio_init_struct;
	gpio_default_para_init(&gpio_init_struct);
	
	//2.配置PA2为USART2的TX，这里和串口屏相连
	gpio_pin_mux_config(GPIOA,GPIO_PINS_SOURCE2,GPIO_MUX_7);		//复用功能，选择GPIO_MUX_7，把PA2复用为USART2的TX引脚，在数据手册中有说明
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;	//复用模式
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_pins = GPIO_PINS_2;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;	//OUT-PP  复用推挽输出
	gpio_init(GPIOA,&gpio_init_struct);
	
	//3.配置PA3为USART2的RX，这里和串口屏相连
	gpio_pin_mux_config(GPIOA,GPIO_PINS_SOURCE3,GPIO_MUX_7);
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	gpio_init_struct.gpio_pins = GPIO_PINS_3;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;  //OUT-PP  复用推挽输出
	gpio_init(GPIOA,&gpio_init_struct);
	
	//4.配置USART2
	usart_init(USART2,115200,USART_DATA_8BITS,USART_STOP_1_BIT);
	usart_transmitter_enable(USART2,TRUE);
	usart_receiver_enable(USART2,TRUE);
	usart_parity_selection_config(USART2,USART_PARITY_NONE);
	usart_dma_transmitter_enable(USART2,TRUE);
	usart_hardware_flow_control_set(USART2,USART_HARDWARE_FLOW_NONE);	
	
	//5.串口中断
	usart_interrupt_enable(USART2,USART_RDBF_INT,TRUE);		//缓冲区满，则中断
	usart_interrupt_enable(USART2,USART_IDLE_INT,TRUE);		//检测到空闲电路，则中断
	
	usart_enable(USART2,TRUE);
}
	

#pragma import(__use_no_semihosting)	//确保没有从 C 库链接使用半主机的函数

int __ttywrch(int ch)
{
	ch = ch;
	return ch;
}

//标准库需要支持的函数
struct __FILE 
{
	int handle;
};

FILE __stdout;  

void _sys_exit(int x)
{
	x = x;
}

int fputc(int ch,FILE *f)
{
	usart_data_transmit(USART1,(uint8_t)ch);	//调用串口发送函数
	//while(usart_flag_get(USART1,USART_RDBF_INT) != FALSE);
	while(RESET == usart_flag_get(USART1,USART_TDC_FLAG));
	return ch;
}






