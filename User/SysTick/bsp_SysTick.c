

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//功能：定时程序
//作用：SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
//      常用的有 1us 10us 1ms 中断。  
//编写：MARK
//时间: 2019年4月22日20:55
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
  
#include "./systick/bsp_SysTick.h"

//static __IO u32 TimingDelay;
 static __IO u32 TimingDelay = 0;
 
 
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 1000000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief   us延时程序,10us为一个单位
  * @param  
  *		@arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
  * @retval  无
  */
void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}



void NOP_pro(int i)
{
	int a;
	int b;
	for(a=0;a<i;a++)
	{
		for(b=0;b<i;b++)
	  {
	  }
	}
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*********************************************END OF FILE**********************/
