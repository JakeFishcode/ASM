#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
#define Trig_1 PCout(11) // PC11
#define Trig_2 PCout(12)//  PC12

void TIM3_Int_Init(u16 arr,u16 psc); 
void TIM5_Int_Init(u16 arr,u16 psc); 
float measure();
void trigger();

void Trig_10us_IO_Init(void);
 
#endif
