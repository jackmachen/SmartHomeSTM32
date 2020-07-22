#ifndef __BEEP_H_
#define	__BEEP_H_



#include "stm32f10x.h"



/******************** BEEP �������ò������� **************************/
#define             macBEEP_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             macBEEP_GPIO_CLK                        RCC_APB2Periph_GPIOC
#define             macBEEP_PORT                            GPIOC
#define             macBEEP_PIN                             GPIO_Pin_13



/******************** BEEP �����궨�� **************************/
#define             macBEEP_ON()	                          GPIO_SetBits ( macBEEP_PORT, macBEEP_PIN )
#define             macBEEP_OFF()                           GPIO_ResetBits ( macBEEP_PORT, macBEEP_PIN )



/************************** BEEP ��������********************************/
void                            Beep_Init                               ( void );



#endif /* __BEEP_H_ */
