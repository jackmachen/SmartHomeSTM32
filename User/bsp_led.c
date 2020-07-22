#include "bsp_led.h"   




static void                         LED_GPIO_Config                  ( void );


 /**
  * @brief  ���� LED �� GPIO ����
  * @param  ��
  * @retval ��
  */
static void LED_GPIO_Config ( void )
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
/*
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//��PB3���ó�Ϊ��ͨ��GPIO��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE); //��Ҫ����APB2������
	                                                                           //�� AFIO �� GPIOB ʱ��
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//�ر�JTAG���Կ���SWD����
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
*/	  


	
	/* ���� LED1 ���� */
	RCC_APB2PeriphClockCmd ( macLED1_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED1_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( macLED1_GPIO_PORT, & GPIO_InitStructure );	

	/* ���� LED2 ���� */
	RCC_APB2PeriphClockCmd ( macLED2_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED2_GPIO_PIN;	
	GPIO_Init ( macLED2_GPIO_PORT, & GPIO_InitStructure );	

	/* ���� LED3 ���� */
	RCC_APB2PeriphClockCmd ( macLED3_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = macLED3_GPIO_PIN;	
	GPIO_Init ( macLED3_GPIO_PORT, & GPIO_InitStructure );		  		
}


 /**
  * @brief  LED ��ʼ������
  * @param  ��
  * @retval ��
  */
void LED_Init ( void )
{
  LED_GPIO_Config ();
	
	macLED1_OFF();
	macLED2_OFF();
	macLED3_OFF();
	
}
/*********************************************END OF FILE**********************/
