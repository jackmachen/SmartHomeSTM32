//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//���ܣ������������ؽӿںͷ������ݺ���
//��д��MARKCHEN
//ʱ�䣺2019��4��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "./usart3/usart3.h"
#include "./yun/yun.h"
#include "./LED/LED.h"

/*���͵�¼��Ϣ*/
void checkin(void)
{
    printf("{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*�˳���¼*/
void checkout(void)
{
    printf("{\"M\":\"checkout\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*��鵱ǰ��¼״̬*/
void check_status(void)
{
    printf("{\"M\":\"status\"}\n");
}
/*����ָ�Ŀ�굥λ*/
void say(char *toID, char *content)
{
    printf("{\"M\":\"say\",\"ID\":\"%s\",\"C\":\"%s\"}\n", toID, content);
}
/*�ϴ�һ���ӿڵ�ʵʱ����*/
void update1(char *did, char *inputid, float value)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%f\"}}\n", did, inputid, value);
}
/*�ϴ������ӿڵ�ʵʱ����*/
void update2(char *did, char *inputid1, float value1, char *inputid2, float value2)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%.2f\",\"%s\":\"%.2f\"}}\n", did, inputid1, value1, inputid2, value2);
}

/*�ϴ�����������һ���ӿڵ�ʵʱ����*/
void update_zhen(char *did, char *inputid, int value)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%d\"}}\n", did, inputid, value);
}

/*�ϴ������ӿڵ�ʵʱ����*/
void update3(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%.2f\",\"%s\":\"%.2f\",\"%s\":\"%d\"}}\n",
           did, inputid1, value1, inputid2, value2, inputid3, a);
}

/*�ϴ��ĸ��ӿڵ�ʵʱ����*/
void update4(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a, char *inputid4, int b)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%.2f\",\"%s\":\"%.2f\",\"%s\":\"%d\",\"%s\":\"%d\"}}\n",
           did, inputid1, value1, inputid2, value2, inputid3, a, inputid4, b);
}

/*����һ�������ӿڵı�����Ϣ*/
void alert(char *did, char *number)
{
    printf("{\"M\":\"alert\",\"ID\":\"%s\",\"C\":\"%s\"}\n", did, number);
}
