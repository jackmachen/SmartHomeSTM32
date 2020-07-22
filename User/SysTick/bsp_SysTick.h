#ifndef __SYSTICK_H
#define __SYSTICK_H


#include "stm32f10x.h"


void SysTick_Init(void);
void Delay_us(__IO u32 nTime);         // 单位1us

void NOP_pro(int i);                   //原始的延时函数


#define Delay_ms(x) Delay_us(1000*x)	 //单位ms
#define Delay_s(x)  Delay_us(1000000*x)	 //单位s



#endif /* __SYSTICK_H */
