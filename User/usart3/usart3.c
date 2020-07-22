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

//    /* ʹ�� USART1 ʱ��*/
//    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
//    /* ѡ����鷽ʽ*/
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//    /* Enable the USART1 Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    /* USART1 ʹ��IO�˿����� */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA

//    /* USART1 ����ģʽ���� */
//    USART_InitStructure.USART_BaudRate = 115200;	//���������ã�115200
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
//    USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
//    USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
//    USART_Init(USART1, &USART_InitStructure);  //��ʼ��USART1
//    /*�����ж�ʹ��*/
//    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
//    USART_Cmd(USART1, ENABLE);// USART1ʹ��
//}

///*����һ���ֽ�����*/
//void UART1SendByte(unsigned char SendData)
//{
//    USART_SendData(USART1, SendData);
//    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
//}

///*����һ���ֽ�����*/
//unsigned char UART1GetByte(unsigned char* GetData)
//{
//    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
//    {
//        return 0;//û���յ�����
//    }
//    *GetData = USART_ReceiveData(USART1);
//    return 1;//�յ�����
//}
///*����һ�����ݣ����Ϸ��ؽ��յ����������*/
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
///*printf����ض���*/
//int fputc(int ch, FILE *f)
//{
//    USART_SendData(USART1, (unsigned char) ch);
//    while(!(USART1->SR & USART_FLAG_TXE));
//    return(ch);
//}

//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//    u8 Clear = Clear;
//    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//    {
//        aRxBuffer[RxCounter++] = USART1->DR; //(USART1->DR);	//��ȡ���յ�������
//    }
//    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  //���������ж�
//    {
//        Clear = USART1->SR;
//        Clear = USART1->DR; //���USART_IT_IDLEλ
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

    /* ʹ�� USART1 ʱ��*/
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    /* ѡ����鷽ʽ*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* USART1 ʹ��IO�˿����� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOB

    /* USART1 ����ģʽ���� */
    USART_InitStructure.USART_BaudRate = 115200;	//���������ã�115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
    USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
    USART_Init(USART3, &USART_InitStructure);  //��ʼ��USART1
    /*�����ж�ʹ��*/
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    USART_Cmd(USART3, ENABLE);// USART1ʹ��
}

/*����һ���ֽ�����*/
void UART3SendByte(unsigned char SendData)
{
    USART_SendData(USART3, SendData);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

/*����һ���ֽ�����*/
unsigned char UART3GetByte(unsigned char* GetData)
{
    if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
    {
        return 0;//û���յ�����
    }
    *GetData = USART_ReceiveData(USART3);
    return 1;//�յ�����
}
/*����һ�����ݣ����Ϸ��ؽ��յ����������*/
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
/*printf����ض���*/
int fputc(int ch, FILE *f)
{
    USART_SendData(USART3, (unsigned char) ch);
    while(!(USART3->SR & USART_FLAG_TXE));
    return(ch);
}

void USART3_IRQHandler(void)                	//����1�жϷ������
{
    u8 Clear = Clear;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        aRxBuffer[RxCounter++] = USART3->DR; //(USART1->DR);	//��ȡ���յ�������
    }
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //���������ж�
    {
        Clear = USART3->SR;
        Clear = USART3->DR; //���USART_IT_IDLEλ
        ReceiveState = 1;
    }
}





