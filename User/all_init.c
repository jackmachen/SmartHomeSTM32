//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//功能：初始化程序
//作用：对之前主函数中的各个模块的所有初始化函数进行打包和封装
//编写：MARKCHEN
//时间: 2019年4月22日20:55
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
#include "all_init.h"
#include "stm32f10x.h"
#include "./systick/bsp_SysTick.h"
#include "./dht11/bsp_dht11.h"
#include "OLED.h"
#include "floatTOs.h"
#include "math_display.h"
#include "stm32f10x_it.h"
#include "bsp_beep.h"
#include "smoke.h"
#include "infrare.h"
#include "./LED/LED.h"
#include "./millis/millis.h"
#include "./usart3/usart3.h"
#include "./stepmotor/stepmotor.h"

void all_init(void)
{
	extern const unsigned char BMP1[];
	//&&&&&&&&&&&&&初始化工作&&&&&&&&&&&&&&&&//
	SysTick_Init(); //配置SysTick 为1us中断一次 ，延时初始化
	DHT11_Init();	//初始化DTT11的引脚
	OLED_Init();	//OLED屏幕初始化
		//	OLED_BMP(0,0,132,8,(unsigned char *)BMP1);   //显示长江大学标志图片
	LED_Init();
	USART3_Config();
	Beep_Init(); //蜂鸣器引脚初始化
	MILLIS_Init();
	show_first(); //显示题目和作者等首页信息
	Delay_s(3);
	OLED_CLS(); //清屏
	show_stay();
	Moto_Init(); //步进电机初始化
	EXTI_SMOKE_Config();
}
