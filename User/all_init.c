//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//���ܣ���ʼ������
//���ã���֮ǰ�������еĸ���ģ������г�ʼ���������д���ͷ�װ
//��д��MARKCHEN
//ʱ��: 2019��4��22��20:55
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
#include "all_init.h"
#include "stm32f10x.h"
#include "./systick/bsp_SysTick.h"
#include "./dht11/bsp_dht11.h"
#include "OLED.h"
#include "floatTOs.h"
#include "math_display.h"
#include "stm32f10x_it.h"
#include "bsp_beep.h"
#include "smoke.h"
#include "infrare.h"
#include "./LED/LED.h"
#include "./millis/millis.h"
#include "./usart3/usart3.h"
#include "./stepmotor/stepmotor.h"

void all_init(void)
{
	extern const unsigned char BMP1[];
	//&&&&&&&&&&&&&��ʼ������&&&&&&&&&&&&&&&&//
	SysTick_Init(); //����SysTick Ϊ1us�ж�һ�� ����ʱ��ʼ��
	DHT11_Init();	//��ʼ��DTT11������
	OLED_Init();	//OLED��Ļ��ʼ��
		//	OLED_BMP(0,0,132,8,(unsigned char *)BMP1);   //��ʾ������ѧ��־ͼƬ
	LED_Init();
	USART3_Config();
	Beep_Init(); //���������ų�ʼ��
	MILLIS_Init();
	show_first(); //��ʾ��Ŀ�����ߵ���ҳ��Ϣ
	Delay_s(3);
	OLED_CLS(); //����
	show_stay();
	Moto_Init(); //���������ʼ��
	EXTI_SMOKE_Config();
}
