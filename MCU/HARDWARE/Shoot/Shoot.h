#ifndef __SHOOT_H
#define __SHOOT_H	 
#include "sys.h" 


#define A1 PBout(12)  //A+
#define B1 PBout(13)  //B+
#define A2 PBout(14)  //A-
#define B2 PBout(15)  //B-


void Shoot_Init(u16 arr,u16 psc); //初始化  发射四个引脚

void Pellet_launching(void);  //发射函数
void Motor_FWD_eight(void); //定义正转函数
void Motor_REV_eight(void);	//定义反转函数
void Motor_STOP_eight(void);//定义停止函数









#endif