#ifndef __INFRARE_H
#define	__INFRARE_H


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


//����״̬�ߵ�ƽ��������͵�ƽ����Ƭ����⵽�½��ش����ж�

//���Ŷ���
#define INFRARE_INT_GPIO_PORT         GPIOB
#define INFRARE_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define INFRARE_INT_GPIO_PIN          GPIO_Pin_1
#define INFRARE_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define INFRARE_INT_EXTI_PINSOURCE    GPIO_PinSource1
#define INFRARE_INT_EXTI_LINE         EXTI_Line1            //�жϱ�־λ
#define INFRARE_INT_EXTI_IRQ          EXTI1_IRQn

#define INFRARE_IRQHandler            EXTI1_IRQHandler

#define INFRARE_BIT     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ

#define INFRARE_BUTTON_GPIO_PIN       GPIO_Pin_8   //����Ŀ��أ����Ŵ򿪿��أ�ϵͳ�����Խ����жϣ�
#define INFRARE_BUTTON_GPIO_PORT      GPIOA
#define INFRARE_BUTTON  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ���ص�״̬


void EXTI_INFRARE_Config(void); 



#endif



