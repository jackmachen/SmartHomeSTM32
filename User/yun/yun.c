//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//功能：定义的联网相关接口和发送数据函数
//编写：MARKCHEN
//时间：2019年4月
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "./usart3/usart3.h"
#include "./yun/yun.h"
#include "./LED/LED.h"

/*发送登录信息*/
void checkin(void)
{
    printf("{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*退出登录*/
void checkout(void)
{
    printf("{\"M\":\"checkout\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*检查当前登录状态*/
void check_status(void)
{
    printf("{\"M\":\"status\"}\n");
}
/*发送指令到目标单位*/
void say(char *toID, char *content)
{
    printf("{\"M\":\"say\",\"ID\":\"%s\",\"C\":\"%s\"}\n", toID, content);
}
/*上传一个接口的实时数据*/
void update1(char *did, char *inputid, float value)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%f\"}}\n", did, inputid, value);
}
/*上传两个接口的实时数据*/
void update2(char *did, char *inputid1, float value1, char *inputid2, float value2)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%.2f\",\"%s\":\"%.2f\"}}\n", did, inputid1, value1, inputid2, value2);
}

/*上传整数型数据一个接口的实时数据*/
void update_zhen(char *did, char *inputid, int value)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%d\"}}\n", did, inputid, value);
}

/*上传三个接口的实时数据*/
void update3(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%.2f\",\"%s\":\"%.2f\",\"%s\":\"%d\"}}\n",
           did, inputid1, value1, inputid2, value2, inputid3, a);
}

/*上传四个接口的实时数据*/
void update4(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a, char *inputid4, int b)
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%.2f\",\"%s\":\"%.2f\",\"%s\":\"%d\",\"%s\":\"%d\"}}\n",
           did, inputid1, value1, inputid2, value2, inputid3, a, inputid4, b);
}

/*发送一个报警接口的报警信息*/
void alert(char *did, char *number)
{
    printf("{\"M\":\"alert\",\"ID\":\"%s\",\"C\":\"%s\"}\n", did, number);
}
