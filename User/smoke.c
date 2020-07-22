
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//���ܣ�����̽����ģ������
//���ã�
//��д��MARK
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#include "smoke.h"
#include "stm32f10x_gpio.h"

static void SMOKE_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ*/
  NVIC_InitStructure.NVIC_IRQChannel = SMOKE_INT_EXTI_IRQ;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

 /**
  * @brief  ���� IOΪEXTI�жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_SMOKE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*����GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(SMOKE_INT_GPIO_CLK,ENABLE);
	
	/* ���� NVIC �ж�*/
	SMOKE_NVIC_Configuration();
	

	/* ѡ���õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = SMOKE_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(SMOKE_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(SMOKE_INT_EXTI_PORTSOURCE, SMOKE_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = SMOKE_INT_EXTI_LINE;
	


	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������½����жϴ��� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}



/*********************************************END OF FILE**********************/


