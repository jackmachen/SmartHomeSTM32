#include "bsp_led.h"   




static void                         LED_GPIO_Config                  ( void );


 /**
  * @brief  配置 LED 的 GPIO 功能
  * @param  无
  * @retval 无
  */
static void LED_GPIO_Config ( void )
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
/*
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//将PB3设置成为普通的GPIO口
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE); //需要开启APB2总线上
	                                                                           //的 AFIO 和 GPIOB 时钟
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭JTAG调试开启SWD调试
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
*/	  


	
	/* 配置 LED1 引脚 */
	RCC_APB2PeriphClockCmd ( macLED1_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED1_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( macLED1_GPIO_PORT, & GPIO_InitStructure );	

	/* 配置 LED2 引脚 */
	RCC_APB2PeriphClockCmd ( macLED2_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED2_GPIO_PIN;	
	GPIO_Init ( macLED2_GPIO_PORT, & GPIO_InitStructure );	

	/* 配置 LED3 引脚 */
	RCC_APB2PeriphClockCmd ( macLED3_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED3_GPIO_PIN;	
	GPIO_Init ( macLED3_GPIO_PORT, & GPIO_InitStructure );		  		
}


 /**
  * @brief  LED 初始化函数
  * @param  无
  * @retval 无
  */
void LED_Init ( void )
{
  LED_GPIO_Config ();
	
	macLED1_OFF();
	macLED2_OFF();
	macLED3_OFF();
	
}
/*********************************************END OF FILE**********************/
