
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//功能：   运算和屏幕显示温度，湿度值
//作用：   因为DTH11得到的所谓的数据，其小数和整数都是整形
//         要想真正意义上得到有小数的值，就必须进行运算。
//         之前屏幕显示动态数字有问题，经过浮点型转字符型
//         函数，可以使屏幕显示实时动态DTH11的数据，但是程
//         较多，不利于查看，为此进行封装，使代码更整洁
//编写：   MARKCHEN
//时间：   2019年4月14日16:39
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
#include "math_display.h"
#include "floatTOs.h"
#include "OLED.h"
#include "./dht11/bsp_dht11.h"
//#include "./usart/bsp_usart.h"
#include "./systick/bsp_SysTick.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//                      运算函数
//     把数据的小数（都是整数）和整数和到一起形成float型
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
float maths(int x_int, int y_deci)             //Mathematical operations-----数学运算
{                                              //x_int代表数据的整数，y_deci代表数据的小数    
	
	  float num = 00.00;                         //char num不正常
	  float xiaoshu;                             //小数部分。
	                                             /*之前用char型定义，显示不正常，串口也显示不正常，
	                                               只有前面整数，小数一直是0。更改后正常  */                                        
	  float zhenshu;                             //整数部分
	
	  xiaoshu = (float)y_deci/10.0;              //(char)代表强制从整形转换成float型
		zhenshu = (float)x_int;
		num = zhenshu + xiaoshu;
	  return num;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//               屏幕显示温度和湿度值的程序
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void display_num(int t_int, int t_deci,int h_int,int h_deci)
{
//	  DHT11_Data_TypeDef DHT11_Data;
	
	  char t[4];
	  char h[4];
	
	//测试用
//		if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)//调用DHT11_Read_TempAndHumidity读取温湿度，
//				                                                         //若成功则输出该信息	
//			{
//         printf("\r\nTEST温度为 %.2f \r\n ",maths(DHT11_Data.temp_int,DHT11_Data.temp_deci) ); //%.2f表示小数点后两位
//			}	
	
		
	  float_to_s(t,maths(t_int,t_deci),2,2);
//		OLED_8x16Str(50,0,t);
		OLED_8x16Str(50,2,t);	
	
  	float_to_s(h,maths(h_int,h_deci),2,2);
//	  OLED_8x16Str(50,2,h); 
		OLED_8x16Str(50,4,h);
	
//&&&&&&&&&之前显示方式，现在封装&&&&&&&&&&&&&&&&&&&&&&&
/*
		char NUM_temp[4];
	  char NUM_humi[4];
	
	
   	float_to_s(NUM_temp, maths(DHT11_Data.temp_int,DHT11_Data.temp_deci), 2, 2);          //浮点数转字符串函数
			                                                                                    //前面的2代表小数点前两位
                                                                                          //后面的2代表小数点后两位
		printf("%s\n", NUM_temp);	
		OLED_8x16Str(50,0,NUM_temp);
		float_to_s(NUM_humi, maths(DHT11_Data.humi_int,DHT11_Data.humi_deci), 2, 2); 	

		OLED_8x16Str(50,2,NUM_humi);	
*/
}

void display(void)
{
	DHT11_Data_TypeDef DHT11_Data;
	
	if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)//调用DHT11_Read_TempAndHumidity读取温湿度，
				                                                       //若成功则输出该信息	
		{
//				printf("\r\n读取DHT11成功!\r\n");
//				printf("\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",\
//				DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		}
		display_num(DHT11_Data.temp_int,DHT11_Data.temp_deci,DHT11_Data.humi_int,DHT11_Data.humi_deci);
                          //屏幕显示温度和湿度值，封装后的程序
 	Delay_s(2);		
	}

