
#ifndef __LED_H
#define	__LED_H


#include "stdint.h"

#define LED1        0x01
#define LED2        0x02
#define LED_BL      0x03


extern void LED_Init(void);
extern void Led_On(uint8_t leds);
extern void Led_Off(uint8_t leds);
extern void Led_Toggle(uint8_t leds);


#endif
