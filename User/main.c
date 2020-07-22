//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//功能：主函数
//编写：MARKCHEN
//时间：2019年4月
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "./LED/LED.h"
#include "./usart3/usart3.h"
#include "./cJSON/cJSON.h"
#include "./millis/millis.h"
#include "./yun/yun.h"
#include "./systick/bsp_SysTick.h"
#include "./dht11/bsp_dht11.h"
#include "all_init.h"
#include "math_display.h"
#include "bsp_beep.h" 
#include "./stepmotor/stepmotor.h"
#include "smoke.h"

volatile u8 aRxBuffer[1024]={0x00};
volatile u8 RxCounter=0;
volatile u8 ReceiveState=0;

unsigned long lastCheckInTime = 0;   //记录上次报到时间
unsigned long lastCheckStatusTime = 0; 
unsigned long lastSayTime = 0; 
unsigned long lastUpdateTime = 0;   //记录上次上传数据时间
const unsigned long postingInterval = 40000; // 每隔40秒向服务器报到一次
const unsigned long statusInterval = 100000; // 数据上传间隔时间10秒
const unsigned long updateInterval = 5000;


/*用CJSON处理接收到的信息*/
int processMessage(char *msg) {
    cJSON *jsonObj = cJSON_Parse(msg);
    cJSON *method;
    char *m;
    //json字符串解析失败，直接退出
    if(!jsonObj)
    {
        //uart1.printf("json string wrong!");
        return 0;
    }
    method = cJSON_GetObjectItem(jsonObj, "M");
    m = method->valuestring;
    if(strncmp(m, "WELCOME", 7) == 0)
    {
        //防止设备在线状态未消除，先登出
        checkout();
        //防止连续发送指令过快
			  Delay_ms(50);
        checkin();
    }
    if(strncmp(m, "connected", 9) == 0)
    {
        checkout();
				Delay_ms(50);
        checkin();
    }
    //有设备或用户登录，发送欢迎信息
    if(strncmp(m, "login", 5) == 0)
    {
        char *from_id = cJSON_GetObjectItem(jsonObj, "ID")->valuestring;
        char new_content[] = "Dear friend, welcome to BIGIOT !";
        say(from_id, new_content);
    }
    //收到say指令，执行相应动作，并进行相应回复
    if(strncmp(m, "say", 3) == 0 && millis() - lastSayTime > 10)
    {
        char *content = cJSON_GetObjectItem(jsonObj, "C")->valuestring;
        char *from_id = cJSON_GetObjectItem(jsonObj, "ID")->valuestring;
        lastSayTime = millis();
        if(strncmp(content, "play", 4) == 0)
        {
            char new_content[] = "led1 played";
            //do something here....
            Led_On(LED1);//板载LED1亮
            say(from_id, new_content);
        }
        else if(strncmp(content, "stop", 4) == 0)
        {
            char new_content[] = "led stoped";
            //do something here....
            Led_Off(LED1);//板载LED灭
            say(from_id, new_content);
        }
				else if(strncmp(content, "up", 2) == 0)
				{
					  char new_content[] = "led2 played";
            //do something here....
            Led_On(LED2);//板载LED2亮
					  say(from_id, new_content);
				}
				else if(strncmp(content, "plus", 4) == 0)
				{
					  char new_content[] = "led2 stoped";
            //do something here....
            Led_Off(LED2);//板载LED2灭
					  say(from_id, new_content);
				}
				else if(strncmp(content, "pause", 5) == 0)
				{
					  char new_content[] = "beep played";	
            macBEEP_ON();//打开蜂鸣器
					  say(from_id, new_content);
				}
				else if(strncmp(content, "right", 5) == 0)
				{
					  char new_content[] = "beep stoped";
            macBEEP_OFF();//关闭蜂鸣器 
					  say(from_id, new_content);
				}
				else if(strncmp(content, "down", 4) == 0)
				{
					  char new_content[] = "stepmotor played";	
            Motor_angle(-720,200);  //步进电机顺时针	
					  say(from_id, new_content);
				}
				else if(strncmp(content, "forward", 7) == 0)
				{
					  char new_content[] = "stepmotor stoped";
            Motor_angle(720,200);  //步进电机逆时针
            say(from_id, new_content);					
				}				
    }
    if(jsonObj)cJSON_Delete(jsonObj);
    return 1;
}

int main(void)
{
    u8 i = 0;
		float wendu;
		float shidu;
	  int   yanwu;
	  int   chuanglian;
	  DHT11_Data_TypeDef DHT11_Data;	

	  all_init();                      //打包的全部初始化函数
    while (1)
    {
        //delay_ms(100);
        if (millis() - lastCheckInTime > postingInterval || lastCheckInTime == 0) 
					{
            checkin();
            lastCheckInTime = millis();
         }
        
        if (millis() - lastCheckStatusTime > statusInterval) 
					{
            check_status();
            lastCheckStatusTime = millis();
          }
				
				if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)//调用DHT11_Read_TempAndHumidity读取温湿度，
				                                                       //若成功则输出该信息	
		    {					
						display_num(DHT11_Data.temp_int,DHT11_Data.temp_deci,DHT11_Data.humi_int,DHT11_Data.humi_deci);
																																		 //屏幕显示温度和湿度值，封装后的程序	
            if (millis() - lastUpdateTime > updateInterval)
						{					
									wendu = (float)DHT11_Data.temp_int + (float)DHT11_Data.temp_deci/10.0;
									shidu = (float)DHT11_Data.humi_int + (float)DHT11_Data.humi_deci/10.0;
									if(SMOKE_BIT == Bit_RESET)     //检测到该引脚电平变低---有烟雾
									{	
											yanwu = 1;
									}
									else if(SMOKE_BIT == Bit_SET)     //检测到该引脚电平变高---正常
									{
											yanwu = 0;
									}
									/*上传三个接口的实时数据*/
									update4(DEVICEID, INPUTID_1, wendu, INPUTID_2, shidu, INPUTID_3, yanwu, INPUTID_4, chuanglian); 
									lastUpdateTime = millis();
					  }
		    }

        if(ReceiveState == 1)
        {
            ReceiveState = 0;
            i = 0;
            processMessage(aRxBuffer);
            RxCounter = 0;
        }			
    }
}

