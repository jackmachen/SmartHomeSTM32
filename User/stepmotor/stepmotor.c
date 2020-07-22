//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//���ܣ������������
//���ã����Ƶ��
//      ������Ĳ������28BYJ-48
//��д��MARKCHEN
//ʱ��: 2019��4��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
#include "./stepmotor/stepmotor.h"
#include "stm32f10x.h"
#include "./yun/yun.h"

#define uint unsigned int
#define uchar unsigned char

//�����������ת����1
//uchar phasecw[8] ={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};// DA-D-CD-C-BC-B-AB-A
//uchar phaseccw[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};// A-AB-B-BC-C-CD-D-DA.
void Delay_xms(uint x)
{
	uint i, j;
	for (i = 0; i < x; i++)
		for (j = 0; j < 112; j++)
			;
}

void Moto_Init(void)
{
	//���1
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	// IN4: PA3   d
	// IN3: PA2   c
	// IN2: PA1   b
	// IN1: PA0   a
}

void Motorcw(int speed)
{
	//    uint8_t i;

	//    for(i=0;i<8;i++)
	//    {
	//        GPIO_Write(GPIOA,phasecw[i]);
	//        Delay_xms(speed);
	//    }
	GPIO_SetBits(GPIOA, GPIO_Pin_3); //0x09    1001
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_0); // ���˿�GPIOA�ĵ�0��3����1���ߵ�ƽ��  1001
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //0x01    0001
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_0); //0x03    0011
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2); //0x02    0010
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //0x06    0110
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2); //0x04    0100
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2); //0x0C    1100
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_SetBits(GPIOA, GPIO_Pin_3); //0x08    1000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);
}
void Motorccw(int speed)
{
	//    uint8_t i;
	//
	//    for(i=0;i<8;i++)
	//    {
	//        GPIO_Write(GPIOA,phaseccw[i]);
	//        Delay_xms(speed);
	//    }
	GPIO_SetBits(GPIOA, GPIO_Pin_3); //0x08    1000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2); //0x0C    1100
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2); //0x04    0100
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //0x06    0110
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2); //0x02    0010
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_0); //0x03    0011
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //0x01    0001
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_SetBits(GPIOA, GPIO_Pin_3); //0x09    1001
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);

	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	Delay_xms(speed);
}

void MotorStop(void)
{
	//    GPIO_Write(GPIOA,0x0000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3); //0x00    0000
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

//����   *һ������*   *�����*  ת0.08789�ȣ����ʵת0.08789*64=5.625�ȣ�����Ϊ5.625��-�����ǡ�
//��ת��8��Ϊ  *8������*  ����0.08789*8=0.70312�ȡ�����Ϊһ�����ڣ���jΪ��Ҫ��ת��angle�Ƕ������������
void Motor_angle(int angle, int speed)
{
	int i, j;
	int CC = 1;
	j = (int)(angle * 64 / (5.625 * 8));
	if (angle > 0)
	{
		for (i = 0; i < j; i++)
		{
			Motorccw(speed);
			if (i % 67 == 0)
				update_zhen(DEVICEID, INPUTID_4, CC);
		}
	}
	else if (angle < 0)
	{
		for (i = 0; i < -j; i++)
		{
			Motorcw(speed);
			if (i % 67 == 0)
				update_zhen(DEVICEID, INPUTID_4, CC);
		}
	}
}
