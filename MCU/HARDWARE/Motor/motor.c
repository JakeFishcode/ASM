#include "motor.h"
#include "delay.h"
#include "led.h"
#include "Shoot.h"
/**********************
功能：初始化四路电机PWM  TIM1-CH1（PA8）;TIM1-CH4(PA11);TIM2-CH3(PA2);TIM2-CH4(PA3)
测试：暂未测试
修改状态：无
***********************/

	void Motor_PWM_Init(u16 arr,u16 psc)
{

  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// TIM1使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// TIM2 使能
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO A外设时钟使能  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO B外设时钟使能 	

   //设置该引脚为复用输出功能,输出TIM1 CH1/ TIM1 CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_11; //初始化IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位


	//初始化 TIM1 CH4 PWM模式

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	
	//初始化 TIM2 CH2 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	
	
	
	//初始化 TIM2 CH3 PWM模式
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	//初始化 TIM2 CH4 PWM模式
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	
	                 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4预装载使能	 

	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
}

/**********************
功能：电机驱动模块初始化
测试：未测试
修改状态：无
***********************/
u16 angle;
u16 speed;
void Motor_INIT()
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化 PC0 PC1 PC2 PC3 PC4 PC5 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化PA4 PA5
	
	/* L298N模块输出A、B初始化 */
	IN1 = 0;
	IN2 = 0;
	IN3 = 0;
	IN4 = 0;
	IN5 = 0;
	IN6 = 0;
	IN7 = 0;
	IN8 = 0;
}

void CAR_INIT()
{
	Motor_INIT();
	stop();
}

/**********************
功能：控制麦克纳姆轮转向 
测试：可用
备注：定义车头方向超前 前边两个轮子分别为号1号 2号 后边从左到右分别为3号 4号 1-4号分别对应IN1-IN8
***********************/
void forward()	
{
	 //OUT1、OUT2，电机1正转
	IN1 = 1;
	IN2 = 0;                                                                                                                  
	 //OUT3、OUT4，电机2正转
	IN3 = 1;
	IN4 = 0;
	//OUT5、OUT6， 电机3正转
	IN5 = 1;
	IN6 = 0;
	 //OUT7、OUT8，电机4正转
	IN7 = 1;
	IN8 = 0;
}

void back()
{
	 //OUT1、OUT2，电机1反转
	IN1 = 0;
	IN2 = 1;
	 //OUT3、OUT4，电机2反转
	IN3 = 0;
	IN4 = 1;
	//OUT5、OUT6， 电机3反转
	IN5 = 0;
	IN6 = 1;
	 //OUT7、OUT8，电机4反转
	IN7 = 0;
	IN8 = 1;
}

void stop()
{
	 //OUT1、OUT2，电机1停止
	IN1 = 0;
	IN2 = 0;
	 //OUT3、OUT4，电机2停止
	IN3 = 0;
	IN4 = 0;
	//OUT5、OUT6， 电机3停止
	IN5 = 0;
	IN6 = 0;
	 //OUT7、OUT8，电机4停止
	IN7 = 0;
	IN8 = 0;
}
void left_run()
{
   //OUT1、OUT2，电机1反转
	IN1 = 0;
	IN2 = 1;
	 //OUT3、OUT4，电机2正转
	IN3 = 1;
	IN4 = 0;
	//OUT5、OUT6， 电机3正转
	IN5 = 1;
	IN6 = 0;
	 //OUT7、OUT8，电机4反转
	IN7 = 0;
	IN8 = 1;
}
void right_run()
{
   //OUT1、OUT2，电机1正转
	IN1 = 1;
	IN2 = 0;
	 //OUT3、OUT4，电机2反转
	IN3 = 0;
	IN4 = 1;
	//OUT5、OUT6， 电机3反转
	IN5 = 0;
	IN6 = 1;
	 //OUT7、OUT8，电机4正转
	IN7 = 1;
	IN8 = 0;
}


//逆时针旋转
	void turnleft()
{  
   
   //OUT1、OUT2，电机1反转
	IN1 = 0;
	IN2 = 1;
	 //OUT3、OUT4，电机2正转
	IN3 = 1;
	IN4 = 0;
	//OUT5、OUT6， 电机3反转
	IN5 = 0;
	IN6 = 1;
	 //OUT7、OUT8，电机4正转
	IN7 = 1;
	IN8 = 0;

}
//顺时针旋转
void turnright()
{
//OUT1、OUT2，电机1正转
	IN1 = 1;
	IN2 = 0;
	 //OUT3、OUT4，电机2反转
	IN3 = 0;
	IN4 = 1;
	//OUT5、OUT6， 电机3正转
	IN5 = 1;
	IN6 = 0;
	 //OUT7、OUT8，电机4反转
	IN7 = 0;
	IN8 = 1;

}
//加速函数
void speedup()
{
	   speed=100;
      TIM_SetCompare4(TIM2,speed); //  TIM2-CH4 用于小车PWM 调节
}
	
void speeddown()
{     speed=150; 

		    TIM_SetCompare4(TIM2,speed); //  TIM2 - CH4 用于小车PWM 调节
	    //TIM_SetCompare2(TIM2,speed); 
		  //TIM_SetCompare4(TIM1,speed); 
		  //TIM_SetCompare3(TIM2,speed); 
}
			 
void Contor_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM4, //TIM4
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIM4外设
							 
}			 


int  t2=0, t3=0; 
 int b = 0;

extern int DistanceFlag;
void TIM4_IRQHandler(void)   //TIM4  中断 主要用于实现小车位置改变  以及机械臂的操作
{	 static int a=0;
	 extern u8 turn, ok;			//用来改变步进电机的转向
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		
	if(DistanceFlag == 1)
	{	
		LED1 =!LED1;   
	  b ++;
		
	if (b <3)
		back();            
	else if (b < 7)
	 {speedup() ;
	 turnright();}
	else
		{ speeddown();       //开始减速
		 forward();
	   DistanceFlag = 0;	
	   t2=0;
	   b = 0 ;
		}
	}	
		 
// 侧面距离优化
	if(DistanceFlag == 2)
	{	  
	  b++;
		
	if (b <3)
	{	speedup() ;
	left_run();} 
	else
		{ 
		 speeddown();       //开始减速
		 forward();
	   DistanceFlag = 0;	
	   t2 = 0 ;
	   b = 0 ;
	  }
	}		
//如果车靠近右边位置时小车位置的改变
	if(DistanceFlag == 3)
	{	
		LED1 =!LED1;   
	  b ++;
		
	if (b <3)
		back();
	else if (b < 7)
	{
		speedup();
	 turnleft();	} 
	else
		{
		 speeddown();       //开始减速
		 forward();
	   DistanceFlag = 0;	
	   t2= 0;
	   b = 0 ;
		}
	}		
	if(DistanceFlag == 4)
{
 stop();
	b++;
	LED1 = !LED1 ; //执行代码时 LED1 闪烁
	if(b<3)
		TIM_SetCompare3(TIM2,195); //  对应底部关节  垂直状态  
	else if (2 < b < 6)
		TIM_SetCompare4(TIM1,176); //  对应 中间关节   放置小球 状态
	else if (5 < b < 9)
	{TIM_SetCompare2(TIM2,195); //195,1.6ms    对应 抓手   打开 状态
	   LED1 = !LED1 ; }//执行代码时 LED1 闪烁
	else if (8 < b < 12)
		 TIM_SetCompare2(TIM2,185); //150,1.6ms  对应 抓手   关闭 状态
	else if (11 < b < 15)
	   TIM_SetCompare3(TIM2,185); //  对应底部关节  水平状态
	else if (14 < b < 18)
		 TIM_SetCompare4(TIM1,195); //195,1.6ms   对应 中间关节     向下 状态
	else if (17 < b < 21)
		TIM_SetCompare2(TIM2,195); //195,1.6ms    对应 抓手   打开 状态 
	else if (20 < b < 24)
		TIM_SetCompare2(TIM2,185); //150,1.6ms  对应 抓手   关闭 状态
	else if (23 < b < 27)
     TIM_SetCompare4(TIM1,185); //150,1.6ms  对应 中间关节向上状态   状态
	else if (26 < b < 28)
		forward();
		DistanceFlag = 0;
		b = 0;
	}

	
	// 当 满足某一条件时 触发发射动作
	if(DistanceFlag == 4)
	{	  
	switch(turn)
			{
			case 0:		//停止
							Motor_STOP_eight();		
							break;
			
			case 1:  //一直反转
							Motor_REV_eight();		
							break;
			
			case 2:	//正转一定距离到顶部	（不可调整，刚好到达顶部）
							a++;
							if(a<2000)			Motor_FWD_eight();	
							else						ok=1;										//已到达顶部
							break;
			
			case 3:	//反转一定距离		（可适当调整，使其投出想要的距离）
							a--;
							if(a>700)			Motor_REV_eight();			
							else       			{a = 0; ok = 0;	}				//已到达想要的距离
							break;
							
			case 4:  //一直正转
							Motor_FWD_eight();		
							break;
			
			default:	//停止
							Motor_STOP_eight();		
							break;
			
	}		
	

}		
 TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		}		 
	 }	 