#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "OLED2.h"
#include "LED.h"
#include "Key.h"

uint8_t state=0;
uint8_t keynum=0;

/**
  * 坐标轴定义：
  * 左上角为(0, 0)点
  * 横向向右为X轴，取值范围：0~127
  * 纵向向下为Y轴，取值范围：0~63
  * 
  *       0             X轴           127 
  *      .------------------------------->
  *    0 |
  *      |
  *      |
  *      |
  *  Y轴 |
  *      |
  *      |
  *      |
  *   63 |
  *      v
  * 
  */
	
void show(uint8_t moshi){
	OLED_Clear();
	OLED_Clear2();
	switch(moshi){
		case 1:
			OLED_ShowString2(0,0,"1945年          ",OLED_8X16);
			OLED_ShowString2(0,16,"安徽省立蚌埠工业",OLED_8X16);
			OLED_ShowString2(0,32,"职业学校建校",OLED_8X16);
			OLED_ShowString2(0,48,"（合工大前身）",OLED_8X16);
			OLED_ShowImage(9, 0, 110, 64, p2);
			break;
		case 2:
			OLED_ShowString2(0,0,"1955年",OLED_8X16);
			OLED_ShowString2(0,16,"学校提升办学层次",OLED_8X16);
			OLED_ShowString2(0,32,"成功改为本科院校",OLED_8X16);
			OLED_ShowImage(11, 0, 107, 64, p3);
			break;
		case 3:
			OLED_ShowString2(0,0,"1956--1958年",OLED_8X16);
			OLED_ShowString2(0,16,"屯溪路校区修建",OLED_8X16);
			OLED_ShowString2(0,32,"更名合肥工业大学",OLED_8X16);
			OLED_ShowImage(13, 0, 102, 64, p4);
			break;
		case 4:
			OLED_ShowString2(0,0,"1960年",OLED_8X16);
			OLED_ShowString2(0,16,"获评全国重点高校",OLED_8X16);
			OLED_ShowString2(0,32,"跻身国家重点建设",OLED_8X16);
			OLED_ShowString2(0,48,"高校行列",OLED_8X16);
			OLED_ShowImage(18, 0, 92, 64, p5);
			break;
		case 5:
			OLED_ShowString2(0,0,"2001年",OLED_8X16);
			OLED_ShowString2(0,16,"翡翠湖校区动工",OLED_8X16);
			OLED_ShowString2(0,32,"开启多校区办学",OLED_8X16);
			OLED_ShowImage(22, 0, 84, 64, p6);
			break;
		case 6:
			OLED_ShowString2(0,0,"2005年",OLED_8X16);
			OLED_ShowString2(0,16,"入选国家211工程",OLED_8X16);
			OLED_ShowImage(14, 0, 100, 64, p7);
			break;
		case 8:
			OLED_ShowString2(0,0,"2011年",OLED_8X16);
			OLED_ShowString2(0,16,"宣城校区获批筹建",OLED_8X16);
			OLED_ShowImage(18, 0, 92, 64, p8);
			break;
		case 0:
			OLED_ShowString2(0,0,"    欢迎来到  ",OLED_8X16);
			OLED_ShowString2(0,16,"  合肥工业大学",OLED_8X16);
			OLED_ShowString2(0,32,"  厚德    笃学",OLED_8X16);
			OLED_ShowString2(0,48,"  崇实    尚新",OLED_8X16);
			OLED_ShowImage(32, 0, 65, 64, p1);
			break;
	}
	OLED_Update();
	OLED_Update2();
}

int main(void)
{
	/*初始化*/
	OLED_Init();
	OLED_Init2();
	led_init();
	Key_Init();
	
	while (1)
	{
		keynum=Key_GetNum();
		if(keynum==2)
		{
			if(state==6)
			{
				state=8;
			}
			else
			{
				state++;
			}
			state=state%9;
		}
		
		led_on(state);
		show(state);
	}
}
