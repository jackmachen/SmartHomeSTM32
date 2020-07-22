#ifndef __SYSTICK_H
#define __SYSTICK_H


#include "stm32f10x.h"


void SysTick_Init(void);
void Delay_us(__IO u32 nTime);         // ��λ1us

void NOP_pro(int i);                   //ԭʼ����ʱ����


#define Delay_ms(x) Delay_us(1000*x)	 //��λms
#define Delay_s(x)  Delay_us(1000000*x)	 //��λs



#endif /* __SYSTICK_H */
