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
# 调亮度
  亮度调节需要设置对比度寄存器0x81,它有256（0x00~0xFF）个亮度档位可以调节。意思就是：先向屏幕写0x81这                    
	个命令，再向屏幕写您需要的亮度值。
  具体代码：
  #define  Brightness  0xCF // 亮度值0xCF宏定义给Brightness
  OLED_WrCmd(0x81);   // set contrast control register
  OLED_WrCmd(Brightness);
  OLED_WrCmd(0xa1);

# 屏幕倒过来显示
  只要把左右反置一下，再上下反置一下就可以把屏幕倒过来显示，这样可以方便设备的灵活布线和安装。
  如下所示，0xa1/0xa0命令可以控制屏幕左右的顺序显示，0xc8/0xc0可以控制屏幕的上下顺序显示。
  OLED_WrCmd(0xa1);    // –Set SEG/Colum Mapping           0xa0左右反置，0xa1正常
  OLED_WrCmd(0xc8);   // –Set COM/Row Scan Direction      0xc0上下反置，0xc8正常
  OLED_WrCmd(0xa1);     OLED WrCmd(0xC8);   //完全倒置显示

# 屏幕正反显示
  控制SH1106寄存器中的0xa6与0xa7两条命令来控制正反显示。
  具体代码：
	OLED_WrCmd(0xa6);       //全屏正显
  OLED_WrCmd(0xa7);       //全屏反显
	
# 屏幕休眠
  本公司生产的OLED模块使用了驱动芯片上的电荷泵（一种升压装置）来为液晶面板提供足够的驱动电压，
	电荷泵的能耗在整个模块中占有较高的比例。因此要让屏幕休眠首先要关闭屏幕，还要关闭“电荷泵”。
	具体代码：
	休眠/&&&&&&&&&&&&&&&&&关闭OLED显示–使OLED进入休眠模式&&&&&&&&&&&/
	void OLED_OFF(void)
 {

  OLED_WrCmd(0x8D);       //设置电源泵

  OLED_WrCmd(0x10);       //关闭电源泵

  OLED_WrCmd(0xAE);       //OLED休眠
 
  }

  唤醒/&&&&&&&&&&&&&&&&&&开启OLED显示&&&&&&&&&&&&&&&&&&&&&/
	void OLED_ON(void)
  {

  OLED_WrCmd(0x8D);       //设置电源泵

  OLED_WrCmd(0x14);       //关闭电源泵

  OLED_WrCmd(0xAF);       //OLED唤醒

  }
*************************************************************************************/

#include "OLED.h"
#include "codetab.h"
#include "stm32f10x_gpio.h"
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#include "./systick/bsp_SysTick.h"




void OLED_WrDat(unsigned char dat)//写数据
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

void OLED_WrCmd(unsigned char cmd)//写命令
{
	unsigned char i;
	OLED_DC_Clr();
	for(i=0;i<8;i++) //发送一个八位数据
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

void OLED_SetPos(unsigned char x, unsigned char y)//设置起始点坐标
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char bmp_dat)//全屏填充
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

void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}

void OLED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PC,D,G端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	 //PD3,PD6推挽输出
	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOD3,6
  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);	//PD3,PD6 输出高
	
	OLED_RST_Clr();
  Delay_ms(500);
	
	OLED_WrCmd(0xAE);//--turn off oled panel
	
	OLED_WrCmd(0x02);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	
	OLED_WrCmd(0xB0);//--set contrast control register
	
	OLED_WrCmd(0x81);// Set SEG Output Current Brightness    调节亮度
//OLED_WrCmd(0x80);//--Set SEG/Column Mapping     0xa0???? 0xa1??
  OLED_WrCmd(Brightness);//亮度
	
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

void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[])  //该函数占一行
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

void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[])  //改函数占两行&&&&第一行Y为0，第二行Y为2，类推
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

///&&&&&&&&&&&&&&&&&&&&&&&&自定义显示题目“智能家居”汉字&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
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

///&&&&&&&&&&&&&&&&&&&&&&&&自定义显示“温湿度”汉字&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
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
//&&&&&&&&&&&&&&&&&&&&&自定义显示“消防状况：“和“安全状况：”&&&&&&&&&&&&&&&&&&&&&&&&&&&//
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

//&&&&&&&&&&&&&&&&&&&&&自定义显示“正常”&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
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
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&显示“异常”汉字&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
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


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"%"符号显示&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_S_F(unsigned char x, unsigned char y, unsigned char N)      //湿度符号
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

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"℃"符号显示&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void OLED_16x16CN_W_F(unsigned char x, unsigned char y, unsigned char N)      //温度符号
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
// 打包前面固定不变的显示函数 
// 屏幕显示 “温度：”，“湿度：”，“℃”，“%”，“消防状况：”“安全状况：”
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void show_stay(void)
{
	unsigned char i;
		for(i=0; i<8; i++)//显示“智能家居”汉字
		{
			  OLED_16x16CN_TIMU(i*16,0,i);
		}
		for(i=0; i<3; i++)//显示“温度：”和“湿度：”汉字
		{
//			OLED_16x16CN_WENDU(i*16,0,i);
//		 	OLED_16x16CN_WENDU(i*16,2,i+3);
				OLED_16x16CN_WENDU(i*16,2,i);
  		 	OLED_16x16CN_WENDU(i*16,4,i+3);
		}
			for(i=0; i<5; i++)//显示“消防状况：”和“安全状况：”汉字
		{
//			OLED_16x16CN_XIAOFANG(i*16,4,i);     //"4"代表行数
//		 	OLED_16x16CN_XIAOFANG(i*16,6,i+5);
			OLED_16x16CN_XIAOFANG(i*16,6,i);     //"4"代表行数
//		 	OLED_16x16CN_XIAOFANG(i*16,6,i+5);
		}
		
		for(i=0; i<1; i++)//显示“℃”符号
		{
//			OLED_16x16CN_W_F(i*16+96,0,i);  //i*16+16的倍数代表位数 。 "0"代表行数
				OLED_16x16CN_W_F(i*16+96,2,i);  //i*16+16的倍数代表位数 。 "0"代表行数
		}

		for(i=0; i<1; i++)//显示“%”符号
		{
//			OLED_16x16CN_S_F(i*16+96,2,i);  //i*16+16的倍数代表位数 。 "2"代表行数
			  OLED_16x16CN_S_F(i*16+96,4,i);  //i*16+16的倍数代表位数 。 "2"代表行数		
		}
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//打包显示正常/异常的函数
//前面的a(0或1)代表正常或异常；后面b(4或6)代表行数。
//4对应着第三行（消防状况）；6对应第四行（安全状况）
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void show_state(unsigned int a, unsigned char b)         //变量a只有0和1，切记0---异常；  1---正常
{                                                        //变量b表示行数
	unsigned char i;
	if(1 == a)
		for(i=0; i<2; i++)//显示“正常”汉字
		{
			OLED_16x16CN_ZHENCHANG(i*16+80,b,i); //i*16+16的倍数代表位数 。 "b"代表行数
		}
		
   if(0 == a)
		for(i=0; i<2; i++)//显示“异常”汉字
		{
			OLED_16x16CN_YICHANG(i*16+80,b,i); //i*16+16的倍数代表位数 。 "b"代表行数
		}
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//打包首页显示的函数
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void show_first(void)             //显示题目和作者信息
{
	unsigned char i;
			for(i=0; i<8; i++)//通过点阵显示汉字 -- i表示子表中汉字的位置
		{
			OLED_16x16CN(i*16,0,i);
		 	OLED_16x16CN(i*16,2,i+8);
		 	OLED_16x16CN(i*16,4,i+16);
		 	OLED_16x16CN(i*16,6,i+24);
		}
}




