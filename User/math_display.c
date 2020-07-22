
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//���ܣ�   �������Ļ��ʾ�¶ȣ�ʪ��ֵ
//���ã�   ��ΪDTH11�õ�����ν�����ݣ���С����������������
//         Ҫ�����������ϵõ���С����ֵ���ͱ���������㡣
//         ֮ǰ��Ļ��ʾ��̬���������⣬����������ת�ַ���
//         ����������ʹ��Ļ��ʾʵʱ��̬DTH11�����ݣ����ǳ�
//         �϶࣬�����ڲ鿴��Ϊ�˽��з�װ��ʹ���������
//��д��   MARKCHEN
//ʱ�䣺   2019��4��14��16:39
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
#include "math_display.h"
#include "floatTOs.h"
#include "OLED.h"
#include "./dht11/bsp_dht11.h"
//#include "./usart/bsp_usart.h"
#include "./systick/bsp_SysTick.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//                      ���㺯��
//     �����ݵ�С���������������������͵�һ���γ�float��
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
float maths(int x_int, int y_deci)             //Mathematical operations-----��ѧ����
{                                              //x_int�������ݵ�������y_deci�������ݵ�С��    
	
	  float num = 00.00;                         //char num������
	  float xiaoshu;                             //С�����֡�
	                                             /*֮ǰ��char�Ͷ��壬��ʾ������������Ҳ��ʾ��������
	                                               ֻ��ǰ��������С��һֱ��0�����ĺ�����  */                                        
	  float zhenshu;                             //��������
	
	  xiaoshu = (float)y_deci/10.0;              //(char)����ǿ�ƴ�����ת����float��
		zhenshu = (float)x_int;
		num = zhenshu + xiaoshu;
	  return num;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//               ��Ļ��ʾ�¶Ⱥ�ʪ��ֵ�ĳ���
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void display_num(int t_int, int t_deci,int h_int,int h_deci)
{
//	  DHT11_Data_TypeDef DHT11_Data;
	
	  char t[4];
	  char h[4];
	
	//������
//		if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)//����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ�
//				                                                         //���ɹ����������Ϣ	
//			{
//         printf("\r\nTEST�¶�Ϊ %.2f \r\n ",maths(DHT11_Data.temp_int,DHT11_Data.temp_deci) ); //%.2f��ʾС�������λ
//			}	
	
		
	  float_to_s(t,maths(t_int,t_deci),2,2);
//		OLED_8x16Str(50,0,t);
		OLED_8x16Str(50,2,t);	
	
  	float_to_s(h,maths(h_int,h_deci),2,2);
//	  OLED_8x16Str(50,2,h); 
		OLED_8x16Str(50,4,h);
	
//&&&&&&&&&֮ǰ��ʾ��ʽ�����ڷ�װ&&&&&&&&&&&&&&&&&&&&&&&
/*
		char NUM_temp[4];
	  char NUM_humi[4];
	
	
   	float_to_s(NUM_temp, maths(DHT11_Data.temp_int,DHT11_Data.temp_deci), 2, 2);          //������ת�ַ�������
			                                                                                    //ǰ���2����С����ǰ��λ
                                                                                          //�����2����С�������λ
		printf("%s\n", NUM_temp);	
		OLED_8x16Str(50,0,NUM_temp);
		float_to_s(NUM_humi, maths(DHT11_Data.humi_int,DHT11_Data.humi_deci), 2, 2); 	

		OLED_8x16Str(50,2,NUM_humi);	
*/
}

void display(void)
{
	DHT11_Data_TypeDef DHT11_Data;
	
	if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)//����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ�
				                                                       //���ɹ����������Ϣ	
		{
//				printf("\r\n��ȡDHT11�ɹ�!\r\n");
//				printf("\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n",\
//				DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		}
		display_num(DHT11_Data.temp_int,DHT11_Data.temp_deci,DHT11_Data.humi_int,DHT11_Data.humi_deci);
                          //��Ļ��ʾ�¶Ⱥ�ʪ��ֵ����װ��ĳ���
 	Delay_s(2);		
	}

