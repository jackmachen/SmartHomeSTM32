//#include <stdio.h>
//#include "stm32f10x.h"
//#include "usart1.h"
//extern u8 aRxBuffer[1024];
//extern u8 RxCounter;
//extern u8 ReceiveState;

//void USART1_Config(void)
//{
//    NVIC_InitTypeDef NVIC_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;

//    /* 使能 USART1 时钟*/
//    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
//    /* 选择分组方式*/
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//    /* Enable the USART1 Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    /* USART1 使用IO端口配置 */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
//    GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA

//    /* USART1 工作模式配置 */
//    USART_InitStructure.USART_BaudRate = 115200;	//波特率设置：115200
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
//    USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
//    USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
//    USART_Init(USART1, &USART_InitStructure);  //初始化USART1
//    /*串口中断使能*/
//    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
//    USART_Cmd(USART1, ENABLE);// USART1使能
//}

///*发送一个字节数据*/
//void UART1SendByte(unsigned char SendData)
//{
//    USART_SendData(USART1, SendData);
//    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
//}

///*接收一个字节数据*/
//unsigned char UART1GetByte(unsigned char* GetData)
//{
//    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
//    {
//        return 0;//没有收到数据
//    }
//    *GetData = USART_ReceiveData(USART1);
//    return 1;//收到数据
//}
///*接收一个数据，马上返回接收到的这个数据*/
//void UART1Test(void)
//{
//    unsigned char i = 0;

//    while(1)
//    {
//        while(UART1GetByte(&i))
//        {
//            USART_SendData(USART1, i);
//        }
//    }
//}
///*printf输出重定向*/
//int fputc(int ch, FILE *f)
//{
//    USART_SendData(USART1, (unsigned char) ch);
//    while(!(USART1->SR & USART_FLAG_TXE));
//    return(ch);
//}

//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//    u8 Clear = Clear;
//    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//    {
//        aRxBuffer[RxCounter++] = USART1->DR; //(USART1->DR);	//读取接收到的数据
//    }
//    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  //空闲总线中断
//    {
//        Clear = USART1->SR;
//        Clear = USART1->DR; //清除USART_IT_IDLE位
//        ReceiveState = 1;
//    }
//}

#include <stdio.h>
#include "stm32f10x.h"
#include "stdint.h"
#include "./usart3/usart3.h"
extern u8 aRxBuffer[1024];
extern u8 RxCounter;
extern u8 ReceiveState;

void USART3_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* 使能 USART1 时钟*/
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    /* 选择分组方式*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* USART1 使用IO端口配置 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOB

    /* USART1 工作模式配置 */
    USART_InitStructure.USART_BaudRate = 115200;	//波特率设置：115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
    USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
    USART_Init(USART3, &USART_InitStructure);  //初始化USART1
    /*串口中断使能*/
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    USART_Cmd(USART3, ENABLE);// USART1使能
}

/*发送一个字节数据*/
void UART3SendByte(unsigned char SendData)
{
    USART_SendData(USART3, SendData);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

/*接收一个字节数据*/
unsigned char UART3GetByte(unsigned char* GetData)
{
    if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
    {
        return 0;//没有收到数据
    }
    *GetData = USART_ReceiveData(USART3);
    return 1;//收到数据
}
/*接收一个数据，马上返回接收到的这个数据*/
void UART3Test(void)
{
    unsigned char i = 0;

    while(1)
    {
        while(UART3GetByte(&i))
        {
            USART_SendData(USART3, i);
        }
    }
}
/*printf输出重定向*/
int fputc(int ch, FILE *f)
{
    USART_SendData(USART3, (unsigned char) ch);
    while(!(USART3->SR & USART_FLAG_TXE));
    return(ch);
}

void USART3_IRQHandler(void)                	//串口1中断服务程序
{
    u8 Clear = Clear;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        aRxBuffer[RxCounter++] = USART3->DR; //(USART1->DR);	//读取接收到的数据
    }
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //空闲总线中断
    {
        Clear = USART3->SR;
        Clear = USART3->DR; //清除USART_IT_IDLE位
        ReceiveState = 1;
    }
}





