#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

void led_init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
															//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;				//GPIO引脚，赋值为所有引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
															//函数内部会自动根据结构体的参数配置相应寄存器
															//实现GPIOA的初始化
}


/*使用GPIO_Write，同时设置GPIOA所有引脚的高低电平，实现LED流水灯
		GPIO_Write(GPIOA, ~0x0001);	//0000 0000 0000 0001，PA0引脚为低电平，其他引脚均为高电平，注意数据有按位取反
		Delay_ms(100);				//延时100ms
		GPIO_Write(GPIOA, ~0x0002);	//0000 0000 0000 0010，PA1引脚为低电平，其他引脚均为高电平
		Delay_ms(100);				//延时100ms
		GPIO_Write(GPIOA, ~0x0004);	//0000 0000 0000 0100，PA2引脚为低电平，其他引脚均为高电平
		Delay_ms(100);				//延时100ms
		GPIO_Write(GPIOA, ~0x0008);	//0000 0000 0000 1000，PA3引脚为低电平，其他引脚均为高电平
		Delay_ms(100);				//延时100ms
		GPIO_Write(GPIOA, ~0x0010);	//0000 0000 0001 0000，PA4引脚为低电平，其他引脚均为高电平
		Delay_ms(100);				//延时100ms
		GPIO_Write(GPIOA, ~0x0020);	//0000 0000 0010 0000，PA5引脚为低电平，其他引脚均为高电平
		Delay_ms(100);				//延时100ms
		GPIO_Write(GPIOA, ~0x0040);	//0000 0000 0100 0000，PA6引脚为低电平，其他引脚均为高电平
		Delay_ms(100);				//延时100ms
		GPIO_Write(GPIOA, ~0x0080);	//0000 0000 1000 0000，PA7引脚为低电平，其他引脚均为高电平
		Delay_ms(100);				//延时100ms
*/

/**
 * @brief 控制 GPIOA 的 PA7~PA0 引脚，点亮指定数量的 LED（从 PA7 开始依次亮）
 * @param weizhi 需要点亮的 LED 个数，范围 0~8
 *        0: 所有 LED 熄灭
 *        1: 仅 PA7 点亮
 *        2: PA7、PA6 点亮
 *        ...
 *        8: PA7~PA0 全部点亮
 */
void led_on(uint8_t weizhi)
{
    uint16_t data;          // GPIO 输出数据（16位）
    
    // 限制输入范围
    if (weizhi > 8) weizhi = 8;
    
    if (weizhi == 0)
    {
        // 全部熄灭：所有引脚输出高电平（LED 低电平有效）
        data = 0xFFFF;
    }
    else
    {
        // 计算低 8 位：高 weizhi 位为 0（点亮），低 (8-weizhi) 位为 1（熄灭）
        // 例如 weizhi=1 -> (1<<7)-1 = 0x7F -> bit7=0, bit6~0=1
        // weizhi=8 -> (1<<0)-1 = 0 -> 低 8 位全 0
        uint8_t low_bits = (1 << (8 - weizhi)) - 1;
        // 高 8 位保持为 1，避免影响 PA8~PA15（若未使用则无影响）
        data = low_bits | 0xFF00;
    }
    
    // 写入 GPIOA 输出数据寄存器
    GPIO_Write(GPIOA, data);
}
