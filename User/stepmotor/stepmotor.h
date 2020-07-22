#ifndef __stepmotor_H
#define __stepmotor_H	 


#define uint unsigned int


void Moto_Init(void);  //步进电机初始化
void Motorcw(int speed);    //步进电机正转函数
void Motorccw(int speed);   //步进电机反转函数
void Motor_angle(int angle,int speed);  //步进电机正转角度函数
//void Motorcw_angle(int angle,int speed);  //步进电机正转角度函数
//void Motorccw_angle(int angle,int speed); //步进电机反转角度函数
void MotorStop(void);  //步进电机停止函数

#endif
