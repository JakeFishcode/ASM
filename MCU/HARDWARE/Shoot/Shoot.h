#ifndef __SHOOT_H
#define __SHOOT_H	 
#include "sys.h" 


#define A1 PBout(12)  //A+
#define B1 PBout(13)  //B+
#define A2 PBout(14)  //A-
#define B2 PBout(15)  //B-


void Shoot_Init(u16 arr,u16 psc); //��ʼ��  �����ĸ�����

void Pellet_launching(void);  //���亯��
void Motor_FWD_eight(void); //������ת����
void Motor_REV_eight(void);	//���巴ת����
void Motor_STOP_eight(void);//����ֹͣ����









#endif