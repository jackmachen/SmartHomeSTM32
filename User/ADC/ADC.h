#ifndef __ADC_H
#define	__ADC_H
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
void RCC_Configuration(void);
void GPIO_Configuration(void);
void Adc_Init(void);

#endif
