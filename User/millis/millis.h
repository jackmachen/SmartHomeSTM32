#ifndef __MILLIS_H
#define	__MILLIS_H
#define RTC_CURRENT_VAL ((RTC->CNTH<<16)+RTC->CNTL)

void MILLIS_Init(void);
void RTCAlarm_IRQHandler(void);
void RTC_IRQHandler();
unsigned long millis();

#endif