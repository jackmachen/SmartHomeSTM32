#ifndef __stepmotor_H
#define __stepmotor_H	 


#define uint unsigned int


void Moto_Init(void);  //���������ʼ��
void Motorcw(int speed);    //���������ת����
void Motorccw(int speed);   //���������ת����
void Motor_angle(int angle,int speed);  //���������ת�ǶȺ���
//void Motorcw_angle(int angle,int speed);  //���������ת�ǶȺ���
//void Motorccw_angle(int angle,int speed); //���������ת�ǶȺ���
void MotorStop(void);  //�������ֹͣ����

#endif
