#include "bsp_beep.h" 



static void                     Beep_GPIO_Config                        ( void );



void Beep_Init ( void )
{		
	Beep_GPIO_Config ();

	macBEEP_OFF ();         // 关闭蜂鸣器
	
}


static void Beep_GPIO_Config ( void )
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	
	/*开启GPIOB和GPIOF的外设时钟*/
	macBEEP_GPIO_APBxClock_FUN  ( macBEEP_GPIO_CLK, ENABLE ); 

	/*选择要控制的GPIOG引脚*/															   
	GPIO_InitStructure.GPIO_Pin = macBEEP_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOG6*/
	GPIO_Init ( macBEEP_PORT, & GPIO_InitStructure );

}
/*********************************************END OF FILE**********************/
