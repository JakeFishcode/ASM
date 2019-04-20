#include "led.h"
#include "delay.h"
#include "sys.h"
#include "measure.h"
#include "usart.h"
#include "motor.h"
#include "Shoot.h"
//#include "arm.h"
//#include "infrared.h"
void get_x_y(unsigned int *x,unsigned int *y);
/*extern  u32 temp1; 
extern  u32 temp2;*/
int DistanceFlag = 0;
extern u8   TIM3CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16  TIM3CH1_CAPTURE_VAL;	//输入捕获值	
extern  u8  TIM4CH1_CAPTURE_STA;	//输入捕获状态		(捕获标志位)    				
extern u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值        （捕获数值）
extern u32 temp1, temp2; 
extern unsigned int blob_x;//定义在usart中
extern unsigned int blob_y;
extern int b;
#define REC_NULL 255
#define OBJECT_X 255
#define OBJECT_Y 45
#define RANGE

unsigned char str2[6]="000000";
int main(void)
{
	delay_init();	    	 //延时函数初始
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2*
	uart_init(9600);	 //串口初始化为9600 
	LED_Init();	 //初始化与LED连接的硬件接口
	CAR_INIT(); 
  Trig_10us_IO_Init();
	
	TIM3_Int_Init(99998,71); //10Khz的计数频率，计数到5000为500ms 
	TIM5_Int_Init(99998,71); //10Khz的计数频率，计数到5000为500ms
	Contor_Int_Init(7999,7199);//10Khz的计数频率，计数到5000为500ms  	 
	Motor_PWM_Init(199,7199);//电机PWM初始化
	forward();   //小车前进	 
	TIM_SetCompare4(TIM1,150); //150,1.6ms 
	TIM_SetCompare2(TIM2,0); //150,1.6ms 
	TIM_SetCompare3(TIM2,0); //150,1.6ms 
	TIM_SetCompare4(TIM2,0); //150,1.6ms 
  while(1)
	{
		
		trigger();  //发送数据 触发超声波测试
		measure();  //超声波开始测量数据
		
		get_xy(&blob_y,&blob_x);
		delay_ms(30);
		
		while(blob_y!=REC_NULL&&blob_x!=REC_NULL)
		{
			while(blob_y<250)
			{
				left_run();
				delay_ms(30);
			}
			while(blob_y>260)
			{
				right_run();
				delay_ms(30);
			}
			while(blob_x<40)
			{
				left_run();
				delay_ms(30);
			}
			
			while(blob_x>50)
			{
				right_run();
				delay_ms(30);
			}
				stop();	
		}
	
		if(temp1<10 && b == 0 )
		{  
			if(temp2 <100)
				DistanceFlag = 4;
			else
				DistanceFlag = 3;
		}
		if(temp2<10 && b == 0)
			DistanceFlag = 2;
	}
}

/* if (1 )                //抓取条件
{	
	DistanceFlag = 4;    //当满足某一条件时  触发抓取
}
if (1)
{
	DistanceFlag = 4;    //当满足某一条件时  触发发射动作
}
*/		
void adjustment(unsigned int x,unsigned y)
{
	while(blob_y!=REC_NULL&&blob_x!=REC_NULL)
	{
		while(y<250)
		{
			left_run();
			delay_ms(30);
		}
		while(y>260)
		{
			right_run();
			delay_ms(30);
		}
		while(x<40)
		{
			left_run();
			delay_ms(30);
		}
			
		while(x>50)
		{
			right_run();
			delay_ms(30);
		}
		stop();	
	}
	
}

