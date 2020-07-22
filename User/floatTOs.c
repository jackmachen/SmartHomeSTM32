//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//���ܣ�������ת�����ַ�������
//���ã�void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
//      void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
//      ��������ʾ��������������ַ�������ʾ������DHT11�õ����������������
//      Ϊ���������޷�ͨ���ú�����Ļ��ʾ������
//      ֱ��DHT11���ݣ����λ��߸����ͣ��ŵ��ú������������������c(65): error:  #167: 
//      argument of type "const unsigned char *" is incompatible with parameter
//      of type "unsigned char *"����
//      ֻ���ڴ洢�����ݵ�����ǰ�����&ȡ��ַ���Ų��ܱ���ɹ���������ֻ����ʾ��
//      ��ַ������������Ҫ�ģ�������Ļ��ʾ���루����������ʾ��ַ����
//      ���������ҵĸú�������Ļ��ʾ����
//      https://www.cnblogs.com/craftor/p/3820027.html
//��д��MARKCHEN
//ʱ�䣺2019��4��14��14:42
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//



#include "./dht11/bsp_dht11.h"     //uint8_t�ĺ궨��ͳһ��bsp_dht11.h
#include "floatTOs.h"



static char table[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};   
//&&&&&&&&&&&&&&&&&&&&������ת�ַ�������&&&&&&&&&&&&&&&&&&&&&&&&//
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
