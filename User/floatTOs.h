
#ifndef __FLOATTOS_H
#define __FLOATTOS_H


#include "./dht11/bsp_dht11.h"     //uint8_t的宏定义统一在bsp_dht11.h


void float_to_s(char *str, double number, uint8_t g, uint8_t l);      //浮点数转字符串函数
                                                                   
#endif
