#ifndef __SMOKE_H
#define	__SMOKE_H


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


//����״̬�ߵ�ƽ��������͵�ƽ����Ƭ����⵽�½��ش����ж�

//���Ŷ���
#define SMOKE_INT_GPIO_PORT         GPIOB
#define SMOKE_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define SMOKE_INT_GPIO_PIN          GPIO_Pin_4
#define SMOKE_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define SMOKE_INT_EXTI_PINSOURCE    GPIO_PinSource4
#define SMOKE_INT_EXTI_LINE         EXTI_Line4            //�жϱ�־λ
#define SMOKE_INT_EXTI_IRQ          EXTI4_IRQn

#define SMOKE_IRQHandler            EXTI4_IRQHandler

#define SMOKE_BIT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//��ȡ




void EXTI_SMOKE_Config(void);



#endif



