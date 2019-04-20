#include "measure.h"
#include "led.h"
#include "usart.h" 
#include "delay.h"

//通用定时器中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!以及定时器4！

  void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟3使能
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟

	//PA6初始化设置
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);	
	
	//初始化定时器3 
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_ICPSC_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	
	//初始化TIM3输入捕获参数
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter=0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//上升沿捕获
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//映射到TI1
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	
	
	//中断3分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

   TIM_ITConfig( TIM3, TIM_IT_Update|TIM_IT_CC1 ,ENABLE  );
	 TIM_Cmd(TIM3, ENABLE);  //使能定时器3	
}

// 初始化定时器3参数

u8  TIM3CH1_CAPTURE_STA=0;	//输入捕获状态		(捕获标志位)    				
u16	TIM3CH1_CAPTURE_VAL;	//输入捕获值        （捕获数值）

//TIM 3中断函数程序
void TIM3_IRQHandler(void)
{ 
 	if((TIM3CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//判断是否发生更新 即是不是发生溢出中断！	 
		{	    
			if(TIM3CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM3CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH1_CAPTURE_STA=0;			//清空
				TIM3CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   	 TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
	
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}


void TIM5_Int_Init(u16 arr,u16 psc)
{
  TIM_ICInitTypeDef TIM5_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟5使能	  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟

	
	//PB6初始化

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
	
	//初始化定时器4
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_ICPSC_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM4输入捕获参数
	
	TIM5_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM5_ICInitStructure.TIM_ICFilter=0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM5_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//上升沿捕获
	TIM5_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM5_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//映射到TI1
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);	
	
	//中断4分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	 TIM_ITConfig( TIM5, TIM_IT_Update|TIM_IT_CC1 ,ENABLE  );

   TIM_Cmd(TIM5, ENABLE);  //使能定时器4	
}

//定时器 4中断服务函数（

u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		(捕获标志位)    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值        （捕获数值）

//TIM 4中断函数程序
void TIM5_IRQHandler(void)
{  

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//判断是否发生更新 即是不是发生溢出中断！	 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   	 TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
	}
//PC11 PC12 一个10us高电平触发用
void Trig_10us_IO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure; 
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;		//使能PA4 PA5 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  
 GPIO_Init(GPIOC, &GPIO_InitStructure);					  
 GPIO_ResetBits(GPIOC,GPIO_Pin_11);	
 GPIO_ResetBits(GPIOC,GPIO_Pin_12);			
}

//打印输出超声波的距离
  u32 temp1=0; 
  u32 temp2=0;
float  measure()
{ 
	  
	if(TIM3CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			temp1=TIM3CH1_CAPTURE_STA&0X3F;
			temp1*=65536;//溢出时间总和
			temp1+=TIM3CH1_CAPTURE_VAL;//得到总的高电平时间
					
			temp1=(float)temp1*0.017;			//得到DAC电压值
		   printf("Front_Measure:%d cm\r\n",temp1);//打印总的距离
	
			TIM3CH1_CAPTURE_STA=0;//开启下一次捕获
		}
		if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			temp2=TIM5CH1_CAPTURE_STA&0X3F;
			temp2*=65536;//溢出时间总和
			temp2+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间
					
			temp2=(float)temp2*0.017;			//得到DAC电压值
			printf("Left_Measure:%d cm\r\n",temp2);//打印总的距离
			
			TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
		}
		
}

//给超声波发送脉冲 触发超声波反馈位置坐标

void trigger()
{
     Trig_1=1;
		 Trig_2=1;
		delay_us(10);
		 Trig_1=0;
		 Trig_2=0;
		delay_us(25);
}
