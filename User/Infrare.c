
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//功能：红外探测器模块驱动-----infrare--红外线
//作用：
//编写：MARKCHEN
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "infrare.h"
#include "stm32f10x_gpio.h"

static void Infrare_BUTTON_Mode_IPD(void);      //开关引脚的初始化


static void INFRARE_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//设置中断优先级
                                                 //设置优先级分组：先占优先级和从优先级  输入参数设定优先级分组位长度 
                                                 //本例中NVIC_PriorityGroup_1：先占优先级1为，从优先级3位
  /* 配置中断源*/
  NVIC_InitStructure.NVIC_IRQChannel = INFRARE_INT_EXTI_IRQ;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

 /**
  * @brief  配置 IO为EXTI中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void EXTI_INFRARE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*开启GPIO口的时钟*/
	RCC_APB2PeriphClockCmd(INFRARE_INT_GPIO_CLK,ENABLE);
	
	/* 配置 NVIC 中断*/
	INFRARE_NVIC_Configuration();
	

	/* 选择用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = INFRARE_INT_GPIO_PIN;
//  /* 配置为浮空输入 */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(INFRARE_INT_GPIO_PORT, &GPIO_InitStructure);
	
	  /* 配置为下拉输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(INFRARE_INT_GPIO_PORT, &GPIO_InitStructure);
   //&&&&&&&&
	Infrare_BUTTON_Mode_IPD();//开关引脚的初始化
	 //&&&&&&&&
	
	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(INFRARE_INT_EXTI_PORTSOURCE, INFRARE_INT_EXTI_PINSOURCE); 
	                                                             //选择GPIO管脚用作外部中断线路
                                                               //第一个参数选择用作外部中断线源的GPIO端口  
																															 //第二个参数是待设置的外部中断线路，可以是GPIO_PinSourcex(x可以0~15)
  EXTI_InitStructure.EXTI_Line = INFRARE_INT_EXTI_LINE;
	


	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;          //设置为中断请求，可以为EXTI_Mode_Interrupt中断请求或者
                                                               //EXTI_Mode_Event事件请求
	/* 上升沿下降沿中断触发 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//触发方式下降沿触发 还可以为EXTI_Trigger_Rising上升沿触发或者
                                                               //EXTI_Trigger_Rising_Falling上升沿下降沿触发
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                    //中断线使能   ENABLE使能，DISABLE失能
  EXTI_Init(&EXTI_InitStructure);                              //根据参数结构体初始化EXTI中断
}


static void Infrare_BUTTON_Mode_IPD(void)      //开关引脚的初始化
{
   
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/	
	  GPIO_InitStructure.GPIO_Pin = INFRARE_BUTTON_GPIO_PIN;

	   /*设置引脚模式为下拉输入模式*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ; 

	  /*调用库函数，初始化DHT11_Dout_GPIO_PORT*/
	  GPIO_Init(INFRARE_BUTTON_GPIO_PORT, &GPIO_InitStructure);	 
	
}


/*********************************************END OF FILE**********************/


