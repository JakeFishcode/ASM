#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY1 PAin(15)	 	//�����ж��Ƿ�ת���ײ�
#define  electricity PBout(10)	 	//�������Ƶ�������ߵ�ƽ�����͵�ƽ��
	 
void KEY_Init(void);//����IO��ʼ��
void  electricity_GPIO_Init(void);	//�����io��ʼ��
#endif