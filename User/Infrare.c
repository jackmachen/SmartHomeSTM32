
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//���ܣ�����̽����ģ������-----infrare--������
//���ã�
//��д��MARKCHEN
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "infrare.h"
#include "stm32f10x_gpio.h"

static void Infrare_BUTTON_Mode_IPD(void);      //�������ŵĳ�ʼ��


static void INFRARE_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//�����ж����ȼ�
                                                 //�������ȼ����飺��ռ���ȼ��ʹ����ȼ�  ��������趨���ȼ�����λ���� 
                                                 //������NVIC_PriorityGroup_1����ռ���ȼ�1Ϊ�������ȼ�3λ
  /* �����ж�Դ*/
  NVIC_InitStructure.NVIC_IRQChannel = INFRARE_INT_EXTI_IRQ;
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
void EXTI_INFRARE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*����GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(INFRARE_INT_GPIO_CLK,ENABLE);
	
	/* ���� NVIC �ж�*/
	INFRARE_NVIC_Configuration();
	

	/* ѡ���õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = INFRARE_INT_GPIO_PIN;
//  /* ����Ϊ�������� */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(INFRARE_INT_GPIO_PORT, &GPIO_InitStructure);
	
	  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(INFRARE_INT_GPIO_PORT, &GPIO_InitStructure);
   //&&&&&&&&
	Infrare_BUTTON_Mode_IPD();//�������ŵĳ�ʼ��
	 //&&&&&&&&
	
	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(INFRARE_INT_EXTI_PORTSOURCE, INFRARE_INT_EXTI_PINSOURCE); 
	                                                             //ѡ��GPIO�ܽ������ⲿ�ж���·
                                                               //��һ������ѡ�������ⲿ�ж���Դ��GPIO�˿�  
																															 //�ڶ��������Ǵ����õ��ⲿ�ж���·��������GPIO_PinSourcex(x����0~15)
  EXTI_InitStructure.EXTI_Line = INFRARE_INT_EXTI_LINE;
	


	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;          //����Ϊ�ж����󣬿���ΪEXTI_Mode_Interrupt�ж��������
                                                               //EXTI_Mode_Event�¼�����
	/* �������½����жϴ��� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//������ʽ�½��ش��� ������ΪEXTI_Trigger_Rising�����ش�������
                                                               //EXTI_Trigger_Rising_Falling�������½��ش���
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                    //�ж���ʹ��   ENABLEʹ�ܣ�DISABLEʧ��
  EXTI_Init(&EXTI_InitStructure);                              //���ݲ����ṹ���ʼ��EXTI�ж�
}


static void Infrare_BUTTON_Mode_IPD(void)      //�������ŵĳ�ʼ��
{
   
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  	/*ѡ��Ҫ���Ƶ�DHT11_Dout_GPIO_PORT����*/	
	  GPIO_InitStructure.GPIO_Pin = INFRARE_BUTTON_GPIO_PIN;

	   /*��������ģʽΪ��������ģʽ*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ; 

	  /*���ÿ⺯������ʼ��DHT11_Dout_GPIO_PORT*/
	  GPIO_Init(INFRARE_BUTTON_GPIO_PORT, &GPIO_InitStructure);	 
	
}


/*********************************************END OF FILE**********************/


