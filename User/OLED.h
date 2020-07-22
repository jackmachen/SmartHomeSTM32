/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED.h
* Project  : HelTec.uvprij
* Processor: STM32F103C8T6
* Compiler : MDK fo ARM
* 
* Author : 小林
* Version: 1.00
* Date   : 2014.2.20
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64点阵的OLED显示屏驱动文件，仅适用于惠特自动化(heltec.taobao.com)的SD1306驱动SPI通信方式显示屏
*
* Others: none;
*
* Function List:
*
* 2. void OLED_WrDat(unsigned char dat) -- 向OLED写数据
* 3. void OLED_WrCmd(unsigned char cmd) -- 向OLED写命令
* 4. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 5. void OLED_Fill(unsigned char bmp_dat) -- 全屏填充(0x00可以用于清屏，0xff可以用于全屏点亮)
* 6. void OLED_CLS(void) -- 清屏
* 7. void OLED_Init(void) -- OLED显示屏初始化
* 8. void OLED_6x8Str(unsigned char x, y,unsigned char ch[]) -- 显示6x8的ASCII字符
* 9. void OLED_8x16Str(unsigned char x, y,unsigned char ch[]) -- 显示8x16的ASCII字符
* 10.void OLED_16x16CN(unsigned char x, y, N) -- 显示16x16中文汉字,汉字要先在取模软件中取模
* 11.void OLED_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- 全屏显示128*64的BMP图片
*
* History: none;
*
*************************************************************************************/

#ifndef __OLED_H
#define __OLED_H
//////////////////////////////////////////////////////////////////////////////////	 
//imodule	
//////////////////////////////////////////////////////////////////////////////////	

#define XLevelL			0x00
#define XLevelH			0x10
#define XLevel	    ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	132
#define Max_Row			64
#define	Brightness	0xFF        //亮度定义 0x00-oxFF
#define X_WIDTH 		132
#define Y_WIDTH 		64




//-----------------OLED端口定义----------------

//#define OLED_RST_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)
//#define OLED_RST_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)    //接OLED模块CS

//#define OLED_DC_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_4)
//#define OLED_DC_Set() GPIO_SetBits(GPIOA,GPIO_Pin_4)     //接OLED模块D/C

//#define OLED_SDA_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)
//#define OLED_SDA_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)    //接OLED模块MOSI

//#define OLED_SCL_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)
//#define OLED_SCL_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)    //接OLED模块的CLK


#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)     //接OLED模块D/C

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)    //接OLED模块CS

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_14)    //接OLED模块MOSI

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)    //接OLED模块的CLK

//#define OLED_CMD  0	//写命令
//#define OLED_DATA 1	//写数据

//OLED控制用函数
void OLED_WrDat(unsigned char dat);//写数据
void OLED_WrCmd(unsigned char cmd);//写命令
void OLED_SetPos(unsigned char x, unsigned char y);//设置起始点坐标
void OLED_Fill(unsigned char bmp_dat);//全屏填充
void OLED_CLS(void);//清屏
void OLED_Init(void);//初始化
void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N);
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//void OLED_16x16CN_WENDU(unsigned char x, unsigned char y, unsigned char N);  //温度/湿度汉字显示函数声明
//void OLED_16x16CN_XIAOFANG(unsigned char x, unsigned char y, unsigned char N);  //消防/安全汉字显示函数声明
//void OLED_16x16CN_S_F(unsigned char x, unsigned char y, unsigned char N);        //湿度符号
//void OLED_16x16CN_W_F(unsigned char x, unsigned char y, unsigned char N);        //温度符号
//void OLED_16x16CN_ZHENCHANG(unsigned char x, unsigned char y, unsigned char N); //正常汉字显示函数声明
//void OLED_16x16CN_YICHANG(unsigned char x, unsigned char y, unsigned char N);   //异常汉字显示函数声明

void show_stay(void);     //打包前面固定不变的显示函数,屏幕显示“温度：”，“湿度：”，“℃”，“%”，“消防状况：”“安全状况：”
void show_state(unsigned int a, unsigned char b);  //打包显示正常/异常的函数, 变量a只有0和1，切记0---异常；  1---正常
                                                   //变量b表示行数
void show_first(void);     //显示题目和作者等首页信息		 																							 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);

#endif
