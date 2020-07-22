//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//功能：浮点数转换成字符串函数
//作用：void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
//      void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
//      这两个显示函数后面参数是字符串可显示，但是DHT11得到的是整数，处理后
//      为浮点数，无法通过该函数屏幕显示参数，
//      直接DHT11数据（整形或者浮点型）放到该函数，报错。这里出现了c(65): error:  #167: 
//      argument of type "const unsigned char *" is incompatible with parameter
//      of type "unsigned char *"错误
//      只有在存储该数据的数组前面加上&取地址符号才能编译成功，但是这只是显示其
//      地址，并不是我想要的，并且屏幕显示乱码（串口正常显示地址）。
//      最终网上找的该函数，屏幕显示正常
//      https://www.cnblogs.com/craftor/p/3820027.html
//编写：MARKCHEN
//时间：2019年4月14日14:42
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//



#include "./dht11/bsp_dht11.h"     //uint8_t的宏定义统一在bsp_dht11.h
#include "floatTOs.h"



static char table[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};   
//&&&&&&&&&&&&&&&&&&&&浮点数转字符串函数&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void float_to_s(char *str, double number, uint8_t g, uint8_t l)
{
    uint8_t i;
    int temp = number/1;
    double t2 = 0.0;
    for (i = 1; i<=g; i++)
    {
        if (temp==0)
            str[g-i] = table[0];
        else
            str[g-i] = table[temp%10];
        temp = temp/10;
    }
    *(str+g) = '.';
    temp = 0;
    t2 = number;
    for(i=1; i<=l; i++)
    {
        temp = t2*10;
        str[g+i] = table[temp%10];
        t2 = t2*10;
    }
    *(str+g+l+1) = '\0';
}
