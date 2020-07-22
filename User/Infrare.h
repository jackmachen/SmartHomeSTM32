#ifndef __INFRARE_H
#define	__INFRARE_H


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


//正常状态高电平，有烟雾低电平，单片机检测到下降沿触发中断

//引脚定义
#define INFRARE_INT_GPIO_PORT         GPIOB
#define INFRARE_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define INFRARE_INT_GPIO_PIN          GPIO_Pin_1
#define INFRARE_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define INFRARE_INT_EXTI_PINSOURCE    GPIO_PinSource1
#define INFRARE_INT_EXTI_LINE         EXTI_Line1            //中断标志位
#define INFRARE_INT_EXTI_IRQ          EXTI1_IRQn

#define INFRARE_IRQHandler            EXTI1_IRQHandler

#define INFRARE_BIT     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取

#define INFRARE_BUTTON_GPIO_PIN       GPIO_Pin_8   //定义的开关（出门打开开关，系统即可以进入中断）
#define INFRARE_BUTTON_GPIO_PORT      GPIOA
#define INFRARE_BUTTON  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取开关的状态


void EXTI_INFRARE_Config(void); 



#endif



