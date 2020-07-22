/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED.c
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
# ������
  ���ȵ�����Ҫ���öԱȶȼĴ���0x81,����256��0x00~0xFF�������ȵ�λ���Ե��ڡ���˼���ǣ�������Ļд0x81��                    
	�����������Ļд����Ҫ������ֵ��
  ������룺
  #define  Brightness  0xCF // ����ֵ0xCF�궨���Brightness
  OLED_WrCmd(0x81);   // set contrast control register
  OLED_WrCmd(Brightness);
  OLED_WrCmd(0xa1);

# ��Ļ��������ʾ
  ֻҪ�����ҷ���һ�£������·���һ�¾Ϳ��԰���Ļ��������ʾ���������Է����豸�����ߺͰ�װ��
  ������ʾ��0xa1/0xa0������Կ�����Ļ���ҵ�˳����ʾ��0xc8/0xc0���Կ�����Ļ������˳����ʾ��
  OLED_WrCmd(0xa1);    // �CSet SEG/Colum Mapping           0xa0���ҷ��ã�0xa1����
  OLED_WrCmd(0xc8);   // �CSet COM/Row Scan Direction      0xc0���·��ã�0xc8����
  OLED_WrCmd(0xa1);     OLED WrCmd(0xC8);   //��ȫ������ʾ

# ��Ļ������ʾ
  ����SH1106�Ĵ����е�0xa6��0xa7��������������������ʾ��
  ������룺
	OLED_WrCmd(0xa6);       //ȫ������
  OLED_WrCmd(0xa7);       //ȫ������
	
# ��Ļ����
  ����˾������OLEDģ��ʹ��������оƬ�ϵĵ�ɱã�һ����ѹװ�ã���ΪҺ������ṩ�㹻��������ѹ��
	��ɱõ��ܺ�������ģ����ռ�нϸߵı��������Ҫ����Ļ��������Ҫ�ر���Ļ����Ҫ�رա���ɱá���
	������룺
	����/&&&&&&&&&&&&&&&&&�ر�OLED��ʾ�CʹOLED��������ģʽ&&&&&&&&&&&/
	void OLED_OFF(void)
 {

  OLED_WrCmd(0x8D);       //���õ�Դ��

  OLED_WrCmd(0x10);       //�رյ�Դ��

  OLED_WrCmd(0xAE);       //OLED����
 
  }

  ����/&&&&&&&&&&&&&&&&&&����OLED��ʾ&&&&&&&&&&&&&&&&&&&&&/
	void OLED_ON(void)
  {

  OLED_WrCmd(0x8D);       //���õ�Դ��

  OLED_WrCmd(0x14);       //�رյ�Դ��

  OLED_WrCmd(0xAF);       //OLED����

  }
*************************************************************************************/

#include "OLED.h"
#include "codetab.h"
#include "stm32f10x_gpio.h"
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#include "./systick/bsp_SysTick.h"




void OLED_WrDat(unsigned char dat)//д����
{
	unsigned char i;
	OLED_DC_Set();
	for(i=0;i<8;i++)
	{
		if((dat << i) & 0x80)
		{
			OLED_SDA_Set();
		}
		else
			OLED_SDA_Clr();
		OLED_SCL_Clr();
		OLED_SCL_Set();
	}
}

void OLED_WrCmd(unsigned char cmd)//д����
{
	unsigned char i;
	OLED_DC_Clr();
	for(i=0;i<8;i++) //����һ����λ����
	{
		if((cmd << i) & 0x80)
		{
			OLED_SDA_Set();
		}
		else
		{
			OLED_SDA_Clr();
		}
		OLED_SCL_Clr();
		OLED_SCL_Set();
	}
}

void OLED_SetPos(unsigned char x, unsigned char y)//������ʼ������
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char bmp_dat)//ȫ�����
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		{
			OLED_WrDat(bmp_dat);
		}
	}
}

void OLED_CLS(void)//����
{
	OLED_Fill(0x00);
}

void OLED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PC,D,G�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	 //PD3,PD6�������
	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);	//PD3,PD6 �����
	
	OLED_RST_Clr();
  Delay_ms(500);
	
	OLED_WrCmd(0xAE);//--turn off oled panel
	
	OLED_WrCmd(0x02);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	
	OLED_WrCmd(0xB0);//--set contrast control register
	
	OLED_WrCmd(0x81);// Set SEG Output Current Brightness    ��������
//OLED_WrCmd(0x80);//--Set SEG/Column Mapping     0xa0???? 0xa1??
  OLED_WrCmd(Brightness);//����
	
	OLED_WrCmd(0xA1);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	
	OLED_WrCmd(0xA6);//--set normal display
	
	OLED_WrCmd(0xA8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3F);//--1/64 duty
	
	OLED_WrCmd(0xAD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x8B);//-not offset
	
	OLED_WrCmd(0x30);//--set display clock divide ratio/oscillator frequency
	
	OLED_WrCmd(0xC8);//--set divide ratio, Set Clock as 100 Frames/Sec
	
	OLED_WrCmd(0xD3);//--set pre-charge period
	OLED_WrCmd(0x00);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	
	OLED_WrCmd(0xD5);//--set com pins hardware configuration
	OLED_WrCmd(0x80);
	
	OLED_WrCmd(0xD9);//--set vcomh
	OLED_WrCmd(0x1F);//Set VCOM Deselect Level
	
	OLED_WrCmd(0xDA);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x12);//
	
	OLED_WrCmd(0xDB);//--set Charge Pump enable/disable
	OLED_WrCmd(0x40);//--set(0x10) disable

	OLED_WrCmd(0xAF);//--turn on oled panel
	
	OLED_Fill(0x00);
	OLED_SetPos(0,0);
}

void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[])  //�ú���ռһ��
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c = ch[j]-32;
		if(x>126)
		{
			x=0;y++;
		}
		OLED_SetPos(x,y);
		for(i=0;i<6;i++)
		{
			OLED_WrDat(F6x8[c][i]);
		}
		x+=6;
		j++;
	}
}

void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[])  //�ĺ���ռ����&&&&��һ��YΪ0���ڶ���YΪ2������
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120)
		{
			x=0;y++;
		}
		OLED_SetPos(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8X16[c*16+i]);
		}
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8X16[c*16+i+8]);
		}
		x+=8;
		j++;
	}
}

void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
}

///&&&&&&&&&&&&&&&&&&&&&&&&�Զ�����ʾ��Ŀ�����ܼҾӡ�����&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_TIMU(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_TIMU[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_TIMU[adder]);
		adder += 1;
	}
}

///&&&&&&&&&&&&&&&&&&&&&&&&�Զ�����ʾ����ʪ�ȡ�����&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_WENDU(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_WENDU[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_WENDU[adder]);
		adder += 1;
	}
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&�Զ�����ʾ������״�������͡���ȫ״������&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_XIAOFANG(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_XIAOFANG[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_XIAOFANG[adder]);
		adder += 1;
	}
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

//&&&&&&&&&&&&&&&&&&&&&�Զ�����ʾ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_ZHENCHANG(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_ZHENCHANG[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_ZHENCHANG[adder]);
		adder += 1;
	}
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&��ʾ���쳣������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_YICHANG(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_YICHANG[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_YICHANG[adder]);
		adder += 1;
	}
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"%"������ʾ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_S_F(unsigned char x, unsigned char y, unsigned char N)      //ʪ�ȷ���
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_S_F[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_S_F[adder]);
		adder += 1;
	}
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"��"������ʾ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_W_F(unsigned char x, unsigned char y, unsigned char N)      //�¶ȷ���
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x+2 , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_W_F[adder]);
		adder += 1;
	}
	OLED_SetPos(x+2,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_W_F[adder]);
		adder += 1;
	}
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//


void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;
	
  if(y1%8==0)
	{
		y=y1/8;
	}
  else
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_WrDat(BMP[j++]);
		}
	}
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// ���ǰ��̶��������ʾ���� 
// ��Ļ��ʾ ���¶ȣ�������ʪ�ȣ��������桱����%����������״����������ȫ״������
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void show_stay(void)
{
	unsigned char i;
		for(i=0; i<8; i++)//��ʾ�����ܼҾӡ�����
		{
			  OLED_16x16CN_TIMU(i*16,0,i);
		}
		for(i=0; i<3; i++)//��ʾ���¶ȣ����͡�ʪ�ȣ�������
		{
//			OLED_16x16CN_WENDU(i*16,0,i);
//		 	OLED_16x16CN_WENDU(i*16,2,i+3);
				OLED_16x16CN_WENDU(i*16,2,i);
  		 	OLED_16x16CN_WENDU(i*16,4,i+3);
		}
			for(i=0; i<5; i++)//��ʾ������״�������͡���ȫ״����������
		{
//			OLED_16x16CN_XIAOFANG(i*16,4,i);     //"4"��������
//		 	OLED_16x16CN_XIAOFANG(i*16,6,i+5);
			OLED_16x16CN_XIAOFANG(i*16,6,i);     //"4"��������
//		 	OLED_16x16CN_XIAOFANG(i*16,6,i+5);
		}
		
		for(i=0; i<1; i++)//��ʾ���桱����
		{
//			OLED_16x16CN_W_F(i*16+96,0,i);  //i*16+16�ı�������λ�� �� "0"��������
				OLED_16x16CN_W_F(i*16+96,2,i);  //i*16+16�ı�������λ�� �� "0"��������
		}

		for(i=0; i<1; i++)//��ʾ��%������
		{
//			OLED_16x16CN_S_F(i*16+96,2,i);  //i*16+16�ı�������λ�� �� "2"��������
			  OLED_16x16CN_S_F(i*16+96,4,i);  //i*16+16�ı�������λ�� �� "2"��������		
		}
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//�����ʾ����/�쳣�ĺ���
//ǰ���a(0��1)�����������쳣������b(4��6)����������
//4��Ӧ�ŵ����У�����״������6��Ӧ�����У���ȫ״����
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void show_state(unsigned int a, unsigned char b)         //����aֻ��0��1���м�0---�쳣��  1---����
{                                                        //����b��ʾ����
	unsigned char i;
	if(1 == a)
		for(i=0; i<2; i++)//��ʾ������������
		{
			OLED_16x16CN_ZHENCHANG(i*16+80,b,i); //i*16+16�ı�������λ�� �� "b"��������
		}
		
   if(0 == a)
		for(i=0; i<2; i++)//��ʾ���쳣������
		{
			OLED_16x16CN_YICHANG(i*16+80,b,i); //i*16+16�ı�������λ�� �� "b"��������
		}
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//�����ҳ��ʾ�ĺ���
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void show_first(void)             //��ʾ��Ŀ��������Ϣ
{
	unsigned char i;
			for(i=0; i<8; i++)//ͨ��������ʾ���� -- i��ʾ�ӱ��к��ֵ�λ��
		{
			OLED_16x16CN(i*16,0,i);
		 	OLED_16x16CN(i*16,2,i+8);
		 	OLED_16x16CN(i*16,4,i+16);
		 	OLED_16x16CN(i*16,6,i+24);
		}
}




