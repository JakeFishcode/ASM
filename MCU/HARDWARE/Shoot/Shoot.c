#include "Shoot.h"
#include "sys.h"
#include "key.h"
#include "delay.h"
#include "led.h"


void Shoot_Init(u16 arr,u16 psc)  // 初始化 发射所用四个引脚
{
   NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
    GPIO_InitTypeDef GPIO_InitStructure;	
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure); //根据参数初始化PB12，13，14，15 推挽输出 速度50MHz

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// TIM8使能
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO C外设时钟使能  

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);//允许更新中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn; //TIM8 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级 0 级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级 3 级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
	NVIC_Init(&NVIC_InitStructure); //初始化NVIC寄存器
	
  TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	

	TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM8, ENABLE);  //使能TIM8
}

//定义发射函数
	u8 turn;			//用来改变步进电机的转向
	u8 ok;				//用来判断是否完成的标志
	

		void Pellet_launching(void)		//小球发射
{ 
		LED0 = 0;     //   LED0 取反
	 turn=0;			//用来改变步进电机的转向
	 ok=0;				//用来判断是否完成的标志
	
	KEY_Init();								//按键IO初始化
	electricity_GPIO_Init();	//电磁铁io初始化
	delay_init();
	
	Shoot_Init(99,71);			//f = 72M / psc+1。重装载值 = arr + 1；	（T=1us）
													//一拍时间(八拍转一圈):(arr+1)*(psc+1)/(72*10^6)			（Tn=100us）
	delay_ms(40);			//延时待小车稳定
	
	turn = 1;					//一直反转
	while(KEY1);						//判断按键是否按下,循环直到按键被按下
	
	turn = 0;
	delay_ms(40);			//延时待小车稳定
	
	turn = 2;			//正转-八拍 (1700*1us)			不可调整，刚好到达顶部
	while(!ok);		//直到到达顶部
	electricity = 1;	//电磁铁通电，拉缩弹簧
	
	turn =0;
	delay_ms(40);		//延时待小车稳定
	
	turn = 3;			//反转-八拍 (1700*1us)			可适当调整，使其投出想要的距离
	while(ok);
	
	turn =0;
	delay_ms(40);			//延时待小球稳定下来
	
	electricity = 0;	//电磁铁断电，小球发射
	LED0 = !LED0;     //   LED0 取反
	delay_ms(20);			//延时看小球发射
}

//定义停止函数

void Motor_STOP_eight(void)			//停止
{
	A1=0;B1=0;A2=0;B2=0;
}

//定义反转函数
void Motor_REV_eight(void)		//反转
{
    static u8 j = 0;
    switch(j)
    {
        case 7:
        {
            A1 =1;B1=0;A2=0;B2=0;
            break;
        }

        case 6:
        {
            A1=1;B1=1;A2=0;B2=0;
            break;
        }

        case 5:
        {
            A1=0;B1=1;A2=0;B2=0;
            break;
        }

        case 4:
        {
            A1=0;B1=1;A2=1;B2=0;
            break;
        }
 				case 3:
        {
            A1=0;B1=0;A2=1;B2=0;
            break;
        }

        case 2:
        {
            A1=0;B1=0;A2=1;B2=1;
            break;
        }

        case 1:
        {
            A1=0;B1=0;A2=0;B2=1;
            break;
        }

        case 0:
        {
            A1=1;B1=0;A2=0;B2=1;
            break;
        }

    }
    j++;
    if(j==8)	j=0;
}
//定义正转函数

void Motor_FWD_eight(void)			
{
    static u8 i = 0;
    switch(i)
    {
        case 0:
        {
            A1 =1;B1=0;A2=0;B2=0;
            break;
        }

        case 1:
        {
            A1=1;B1=1;A2=0;B2=0;
            break;
        }

        case 2:
        {
            A1=0;B1=1;A2=0;B2=0;
            break;
        }

        case 3:
        {
            A1=0;B1=1;A2=1;B2=0;
            break;
        }
        case 4:
        {
            A1=0;B1=0;A2=1;B2=0;
            break;
        }

        case 5:
        {
            A1=0;B1=0;A2=1;B2=1;
            break;
        }

        case 6:
        {
            A1=0;B1=0;A2=0;B2=1;
            break;
        }

        case 7:
        {
            A1=1;B1=0;A2=0;B2=1;
            break;
        }

    }
    i++;
    if(i==8)i=0;
}
void TIM8_UP_IRQHandler(void) //TIM8 中断
{
		static int a=0;
		extern u8 turn;
		extern u8 ok;
	
    if(TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) //检查 TIM2 更新中断发生与否
    { 
			//LED1 = !LED1;
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
			TIM_ClearITPendingBit(TIM8, TIM_IT_Update ); 		//清除 TIM2 更新中断标志

    }
}