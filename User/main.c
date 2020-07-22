//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//���ܣ�������
//��д��MARKCHEN
//ʱ�䣺2019��4��
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

unsigned long lastCheckInTime = 0;   //��¼�ϴα���ʱ��
unsigned long lastCheckStatusTime = 0; 
unsigned long lastSayTime = 0; 
unsigned long lastUpdateTime = 0;   //��¼�ϴ��ϴ�����ʱ��
const unsigned long postingInterval = 40000; // ÿ��40�������������һ��
const unsigned long statusInterval = 100000; // �����ϴ����ʱ��10��
const unsigned long updateInterval = 5000;


/*��CJSON������յ�����Ϣ*/
int processMessage(char *msg) {
    cJSON *jsonObj = cJSON_Parse(msg);
    cJSON *method;
    char *m;
    //json�ַ�������ʧ�ܣ�ֱ���˳�
    if(!jsonObj)
    {
        //uart1.printf("json string wrong!");
        return 0;
    }
    method = cJSON_GetObjectItem(jsonObj, "M");
    m = method->valuestring;
    if(strncmp(m, "WELCOME", 7) == 0)
    {
        //��ֹ�豸����״̬δ�������ȵǳ�
        checkout();
        //��ֹ��������ָ�����
			  Delay_ms(50);
        checkin();
    }
    if(strncmp(m, "connected", 9) == 0)
    {
        checkout();
				Delay_ms(50);
        checkin();
    }
    //���豸���û���¼�����ͻ�ӭ��Ϣ
    if(strncmp(m, "login", 5) == 0)
    {
        char *from_id = cJSON_GetObjectItem(jsonObj, "ID")->valuestring;
        char new_content[] = "Dear friend, welcome to BIGIOT !";
        say(from_id, new_content);
    }
    //�յ�sayָ�ִ����Ӧ��������������Ӧ�ظ�
    if(strncmp(m, "say", 3) == 0 && millis() - lastSayTime > 10)
    {
        char *content = cJSON_GetObjectItem(jsonObj, "C")->valuestring;
        char *from_id = cJSON_GetObjectItem(jsonObj, "ID")->valuestring;
        lastSayTime = millis();
        if(strncmp(content, "play", 4) == 0)
        {
            char new_content[] = "led1 played";
            //do something here....
            Led_On(LED1);//����LED1��
            say(from_id, new_content);
        }
        else if(strncmp(content, "stop", 4) == 0)
        {
            char new_content[] = "led stoped";
            //do something here....
            Led_Off(LED1);//����LED��
            say(from_id, new_content);
        }
				else if(strncmp(content, "up", 2) == 0)
				{
					  char new_content[] = "led2 played";
            //do something here....
            Led_On(LED2);//����LED2��
					  say(from_id, new_content);
				}
				else if(strncmp(content, "plus", 4) == 0)
				{
					  char new_content[] = "led2 stoped";
            //do something here....
            Led_Off(LED2);//����LED2��
					  say(from_id, new_content);
				}
				else if(strncmp(content, "pause", 5) == 0)
				{
					  char new_content[] = "beep played";	
            macBEEP_ON();//�򿪷�����
					  say(from_id, new_content);
				}
				else if(strncmp(content, "right", 5) == 0)
				{
					  char new_content[] = "beep stoped";
            macBEEP_OFF();//�رշ����� 
					  say(from_id, new_content);
				}
				else if(strncmp(content, "down", 4) == 0)
				{
					  char new_content[] = "stepmotor played";	
            Motor_angle(-720,200);  //�������˳ʱ��	
					  say(from_id, new_content);
				}
				else if(strncmp(content, "forward", 7) == 0)
				{
					  char new_content[] = "stepmotor stoped";
            Motor_angle(720,200);  //���������ʱ��
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

	  all_init();                      //�����ȫ����ʼ������
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
				
				if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)//����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ�
				                                                       //���ɹ����������Ϣ	
		    {					
						display_num(DHT11_Data.temp_int,DHT11_Data.temp_deci,DHT11_Data.humi_int,DHT11_Data.humi_deci);
																																		 //��Ļ��ʾ�¶Ⱥ�ʪ��ֵ����װ��ĳ���	
            if (millis() - lastUpdateTime > updateInterval)
						{					
									wendu = (float)DHT11_Data.temp_int + (float)DHT11_Data.temp_deci/10.0;
									shidu = (float)DHT11_Data.humi_int + (float)DHT11_Data.humi_deci/10.0;
									if(SMOKE_BIT == Bit_RESET)     //��⵽�����ŵ�ƽ���---������
									{	
											yanwu = 1;
									}
									else if(SMOKE_BIT == Bit_SET)     //��⵽�����ŵ�ƽ���---����
									{
											yanwu = 0;
									}
									/*�ϴ������ӿڵ�ʵʱ����*/
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

