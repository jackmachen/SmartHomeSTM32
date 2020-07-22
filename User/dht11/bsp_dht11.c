//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//功能：温湿度传感器程序
//作用：温湿度传感器驱动
//编写：MARKCHEN
//时间: 2019年4月
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

#include "./dht11/bsp_dht11.h"
#include "./systick/bsp_SysTick.h"
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//#include "./usart/bsp_usart.h"

static void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
static uint8_t DHT11_ReadByte(void);

/**
  * @brief  DHT11 初始化函数
  * @param  无
  * @retval 无
  */
void DHT11_Init(void)
{
	DHT11_GPIO_Config();

	DHT11_Dout_1; // 拉高GPIOB7
}

/*
 * 函数名：DHT11_GPIO_Config
 * 描述  ：配置DHT11用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启DHT11_Dout_GPIO_PORT的外设时钟*/
	DHT11_Dout_SCK_APBxClock_FUN(DHT11_Dout_GPIO_CLK, ENABLE);

	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/
	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*设置引脚速率为50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化DHT11_Dout_GPIO_PORT*/
	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);
}

/*
 * 函数名：DHT11_Mode_IPU
 * 描述  ：使DHT11-DATA引脚变为上拉输入模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_IPU(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/
	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;

	/*设置引脚模式为上拉输入模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	/*调用库函数，初始化DHT11_Dout_GPIO_PORT*/
	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);
}

/*
 * 函数名：DHT11_Mode_Out_PP
 * 描述  ：使DHT11-DATA引脚变为推挽输出模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/
	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*设置引脚速率为50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化DHT11_Dout_GPIO_PORT*/
	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);
}

/* 
 * 从DHT11读取一个字节，MSB先行
 */
static uint8_t DHT11_ReadByte(void)
{
	uint8_t i, temp = 0;

	for (i = 0; i < 8; i++)
	{
		/*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/
		while (DHT11_Dout_IN() == Bit_RESET)
			;

		/*DHT11 以26~28us的高电平表示“0”，以70us高电平表示“1”，
		 *通过检测 x us后的电平即可区别这两个状 ，x 即下面的延时 
		 */

		Delay_us(40); //延时x us 这个延时需要大于数据0持续的时间即可

		if (DHT11_Dout_IN() == Bit_SET) /* x us后仍为高电平表示数据“1” */
		{
			/* 等待数据1的高电平结束 */
			while (DHT11_Dout_IN() == Bit_SET)
				;

			temp |= (uint8_t)(0x01 << (7 - i)); //把第7-i位置1，MSB先行
		}
		else // x us后为低电平表示数据“0”
		{
			temp &= (uint8_t) ~(0x01 << (7 - i)); //把第7-i位置0，MSB先行
		}
	}

	return temp;
}

/*
 * 一次完整的数据传输为40bit，高位先出
 * 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
 */
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef *DHT11_Data)
{
	/*输出模式*/
	DHT11_Mode_Out_PP();
	/*主机拉低*/
	DHT11_Dout_0;
	/*延时18ms*/
	Delay_ms(18);
	/*总线拉高 主机延时30us*/
	DHT11_Dout_1;
	Delay_us(30); //延时30us
	/*主机设为输入 判断从机响应信号*/
	DHT11_Mode_IPU();
	/*判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行*/
	if (DHT11_Dout_IN() == Bit_RESET)
	{
		/*轮询直到从机发出 的80us 低电平 响应信号结束*/
		while (DHT11_Dout_IN() == Bit_RESET)
			;

		/*轮询直到从机发出的 80us 高电平 标置信号结束*/
		while (DHT11_Dout_IN() == Bit_SET)
			;

		/*开始接收数据*/
		DHT11_Data->humi_int = DHT11_ReadByte();

		DHT11_Data->humi_deci = DHT11_ReadByte();

		DHT11_Data->temp_int = DHT11_ReadByte() - 3; //之前显示的温度大概高3度，现减3

		DHT11_Data->temp_deci = DHT11_ReadByte();

		DHT11_Data->check_sum = DHT11_ReadByte();

		/*读取结束，引脚改为输出模式*/
		DHT11_Mode_Out_PP();
		/*主机拉高*/
		DHT11_Dout_1;

		/*检查读取的数据是否正确*/
		if (DHT11_Data->check_sum - 3 == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int + DHT11_Data->temp_deci)
			return SUCCESS;
		else
			return ERROR;
	}

	else
		return ERROR;
}

/*************************************END OF FILE******************************/
