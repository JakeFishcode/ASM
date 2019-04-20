#ifndef __L298N_H
#define __L298N_H	 
#include "sys.h"
#define  IN1 PCout(0)
#define  IN2 PCout(1)
#define  IN3 PCout(2)
#define  IN4 PCout(3)
#define  IN5 PAout(4)
#define  IN6 PAout(5)
#define  IN7 PCout(4)
#define  IN8 PCout(5)
# define a_PARAMETER  20
# define b_PARAMETER  15

void Motor_INIT(void);
void Motor_PWM_Init(u16 arr,u16 psc);

void forward(void);
void back(void);
void stop(void);
void CAR_INIT(void);
void turnleft(void); //即是逆时针旋转
void turnright(void);//即是顺时针旋转
//void speedup(void);
//void speeddown(void);
//float Kinematic_Analysis(float Vx, float Vy, float Vz);//麦轮运动分析
void left_run(void);
void right_run(void);
void avoidancce(void);
void Contor_Int_Init(u16 arr,u16 psc);

#endif




