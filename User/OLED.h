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
* Author : С��
* Version: 1.00
* Date   : 2014.2.20
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64�����OLED��ʾ�������ļ����������ڻ����Զ���(heltec.taobao.com)��SD1306����SPIͨ�ŷ�ʽ��ʾ��
*
* Others: none;
*
* Function List:
*
* 2. void OLED_WrDat(unsigned char dat) -- ��OLEDд����
* 3. void OLED_WrCmd(unsigned char cmd) -- ��OLEDд����
* 4. void OLED_SetPos(unsigned char x, unsigned char y) -- ������ʼ������
* 5. void OLED_Fill(unsigned char bmp_dat) -- ȫ�����(0x00��������������0xff��������ȫ������)
* 6. void OLED_CLS(void) -- ����
* 7. void OLED_Init(void) -- OLED��ʾ����ʼ��
* 8. void OLED_6x8Str(unsigned char x, y,unsigned char ch[]) -- ��ʾ6x8��ASCII�ַ�
* 9. void OLED_8x16Str(unsigned char x, y,unsigned char ch[]) -- ��ʾ8x16��ASCII�ַ�
* 10.void OLED_16x16CN(unsigned char x, y, N) -- ��ʾ16x16���ĺ���,����Ҫ����ȡģ�����ȡģ
* 11.void OLED_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- ȫ����ʾ128*64��BMPͼƬ
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
#define	Brightness	0xFF        //���ȶ��� 0x00-oxFF
#define X_WIDTH 		132
#define Y_WIDTH 		64




//-----------------OLED�˿ڶ���----------------

//#define OLED_RST_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)
//#define OLED_RST_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)    //��OLEDģ��CS

//#define OLED_DC_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_4)
//#define OLED_DC_Set() GPIO_SetBits(GPIOA,GPIO_Pin_4)     //��OLEDģ��D/C

//#define OLED_SDA_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)
//#define OLED_SDA_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)    //��OLEDģ��MOSI

//#define OLED_SCL_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)
//#define OLED_SCL_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)    //��OLEDģ���CLK


#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)     //��OLEDģ��D/C

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)    //��OLEDģ��CS

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_14)    //��OLEDģ��MOSI

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)    //��OLEDģ���CLK

//#define OLED_CMD  0	//д����
//#define OLED_DATA 1	//д����

//OLED�����ú���
void OLED_WrDat(unsigned char dat);//д����
void OLED_WrCmd(unsigned char cmd);//д����
void OLED_SetPos(unsigned char x, unsigned char y);//������ʼ������
void OLED_Fill(unsigned char bmp_dat);//ȫ�����
void OLED_CLS(void);//����
void OLED_Init(void);//��ʼ��
void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N);
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//void OLED_16x16CN_WENDU(unsigned char x, unsigned char y, unsigned char N);  //�¶�/ʪ�Ⱥ�����ʾ��������
//void OLED_16x16CN_XIAOFANG(unsigned char x, unsigned char y, unsigned char N);  //����/��ȫ������ʾ��������
//void OLED_16x16CN_S_F(unsigned char x, unsigned char y, unsigned char N);        //ʪ�ȷ���
//void OLED_16x16CN_W_F(unsigned char x, unsigned char y, unsigned char N);        //�¶ȷ���
//void OLED_16x16CN_ZHENCHANG(unsigned char x, unsigned char y, unsigned char N); //����������ʾ��������
//void OLED_16x16CN_YICHANG(unsigned char x, unsigned char y, unsigned char N);   //�쳣������ʾ��������

void show_stay(void);     //���ǰ��̶��������ʾ����,��Ļ��ʾ���¶ȣ�������ʪ�ȣ��������桱����%����������״����������ȫ״������
void show_state(unsigned int a, unsigned char b);  //�����ʾ����/�쳣�ĺ���, ����aֻ��0��1���м�0---�쳣��  1---����
                                                   //����b��ʾ����
void show_first(void);     //��ʾ��Ŀ�����ߵ���ҳ��Ϣ		 																							 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);

#endif
