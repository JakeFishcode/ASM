#include "motor.h"
#include "delay.h"
#include "led.h"
#include "Shoot.h"
/**********************
���ܣ���ʼ����·���PWM  TIM1-CH1��PA8��;TIM1-CH4(PA11);TIM2-CH3(PA2);TIM2-CH4(PA3)
���ԣ���δ����
�޸�״̬����
***********************/

	void Motor_PWM_Init(u16 arr,u16 psc)
{

  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// TIM1ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// TIM2 ʹ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO A����ʱ��ʹ��  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO B����ʱ��ʹ�� 	

   //���ø�����Ϊ�����������,���TIM1 CH1/ TIM1 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_11; //��ʼ��IO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ


	//��ʼ�� TIM1 CH4 PWMģʽ

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	
	//��ʼ�� TIM2 CH2 PWMģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	
	
	
	//��ʼ�� TIM2 CH3 PWMģʽ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	//��ʼ�� TIM2 CH4 PWMģʽ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	
	                 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 

	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
}

/**********************
���ܣ��������ģ���ʼ��
���ԣ�δ����
�޸�״̬����
***********************/
u16 angle;
u16 speed;
void Motor_INIT()
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ�� PC0 PC1 PC2 PC3 PC4 PC5 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��PA4 PA5
	
	/* L298Nģ�����A��B��ʼ�� */
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
���ܣ����������ķ��ת�� 
���ԣ�����
��ע�����峵ͷ����ǰ ǰ���������ӷֱ�Ϊ��1�� 2�� ��ߴ����ҷֱ�Ϊ3�� 4�� 1-4�ŷֱ��ӦIN1-IN8
***********************/
void forward()	
{
	 //OUT1��OUT2�����1��ת
	IN1 = 1;
	IN2 = 0;                                                                                                                  
	 //OUT3��OUT4�����2��ת
	IN3 = 1;
	IN4 = 0;
	//OUT5��OUT6�� ���3��ת
	IN5 = 1;
	IN6 = 0;
	 //OUT7��OUT8�����4��ת
	IN7 = 1;
	IN8 = 0;
}

void back()
{
	 //OUT1��OUT2�����1��ת
	IN1 = 0;
	IN2 = 1;
	 //OUT3��OUT4�����2��ת
	IN3 = 0;
	IN4 = 1;
	//OUT5��OUT6�� ���3��ת
	IN5 = 0;
	IN6 = 1;
	 //OUT7��OUT8�����4��ת
	IN7 = 0;
	IN8 = 1;
}

void stop()
{
	 //OUT1��OUT2�����1ֹͣ
	IN1 = 0;
	IN2 = 0;
	 //OUT3��OUT4�����2ֹͣ
	IN3 = 0;
	IN4 = 0;
	//OUT5��OUT6�� ���3ֹͣ
	IN5 = 0;
	IN6 = 0;
	 //OUT7��OUT8�����4ֹͣ
	IN7 = 0;
	IN8 = 0;
}
void left_run()
{
   //OUT1��OUT2�����1��ת
	IN1 = 0;
	IN2 = 1;
	 //OUT3��OUT4�����2��ת
	IN3 = 1;
	IN4 = 0;
	//OUT5��OUT6�� ���3��ת
	IN5 = 1;
	IN6 = 0;
	 //OUT7��OUT8�����4��ת
	IN7 = 0;
	IN8 = 1;
}
void right_run()
{
   //OUT1��OUT2�����1��ת
	IN1 = 1;
	IN2 = 0;
	 //OUT3��OUT4�����2��ת
	IN3 = 0;
	IN4 = 1;
	//OUT5��OUT6�� ���3��ת
	IN5 = 0;
	IN6 = 1;
	 //OUT7��OUT8�����4��ת
	IN7 = 1;
	IN8 = 0;
}


//��ʱ����ת
	void turnleft()
{  
   
   //OUT1��OUT2�����1��ת
	IN1 = 0;
	IN2 = 1;
	 //OUT3��OUT4�����2��ת
	IN3 = 1;
	IN4 = 0;
	//OUT5��OUT6�� ���3��ת
	IN5 = 0;
	IN6 = 1;
	 //OUT7��OUT8�����4��ת
	IN7 = 1;
	IN8 = 0;

}
//˳ʱ����ת
void turnright()
{
//OUT1��OUT2�����1��ת
	IN1 = 1;
	IN2 = 0;
	 //OUT3��OUT4�����2��ת
	IN3 = 0;
	IN4 = 1;
	//OUT5��OUT6�� ���3��ת
	IN5 = 1;
	IN6 = 0;
	 //OUT7��OUT8�����4��ת
	IN7 = 0;
	IN8 = 1;

}
//���ٺ���
void speedup()
{
	   speed=100;
      TIM_SetCompare4(TIM2,speed); //  TIM2-CH4 ����С��PWM ����
}
	
void speeddown()
{     speed=150; 

		    TIM_SetCompare4(TIM2,speed); //  TIM2 - CH4 ����С��PWM ����
	    //TIM_SetCompare2(TIM2,speed); 
		  //TIM_SetCompare4(TIM1,speed); 
		  //TIM_SetCompare3(TIM2,speed); 
}
			 
void Contor_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4, //TIM4
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4����
							 
}			 


int  t2=0, t3=0; 
 int b = 0;

extern int DistanceFlag;
void TIM4_IRQHandler(void)   //TIM4  �ж� ��Ҫ����ʵ��С��λ�øı�  �Լ���е�۵Ĳ���
{	 static int a=0;
	 extern u8 turn, ok;			//�����ı䲽�������ת��
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
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
		{ speeddown();       //��ʼ����
		 forward();
	   DistanceFlag = 0;	
	   t2=0;
	   b = 0 ;
		}
	}	
		 
// ��������Ż�
	if(DistanceFlag == 2)
	{	  
	  b++;
		
	if (b <3)
	{	speedup() ;
	left_run();} 
	else
		{ 
		 speeddown();       //��ʼ����
		 forward();
	   DistanceFlag = 0;	
	   t2 = 0 ;
	   b = 0 ;
	  }
	}		
//����������ұ�λ��ʱС��λ�õĸı�
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
		 speeddown();       //��ʼ����
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
	LED1 = !LED1 ; //ִ�д���ʱ LED1 ��˸
	if(b<3)
		TIM_SetCompare3(TIM2,195); //  ��Ӧ�ײ��ؽ�  ��ֱ״̬  
	else if (2 < b < 6)
		TIM_SetCompare4(TIM1,176); //  ��Ӧ �м�ؽ�   ����С�� ״̬
	else if (5 < b < 9)
	{TIM_SetCompare2(TIM2,195); //195,1.6ms    ��Ӧ ץ��   �� ״̬
	   LED1 = !LED1 ; }//ִ�д���ʱ LED1 ��˸
	else if (8 < b < 12)
		 TIM_SetCompare2(TIM2,185); //150,1.6ms  ��Ӧ ץ��   �ر� ״̬
	else if (11 < b < 15)
	   TIM_SetCompare3(TIM2,185); //  ��Ӧ�ײ��ؽ�  ˮƽ״̬
	else if (14 < b < 18)
		 TIM_SetCompare4(TIM1,195); //195,1.6ms   ��Ӧ �м�ؽ�     ���� ״̬
	else if (17 < b < 21)
		TIM_SetCompare2(TIM2,195); //195,1.6ms    ��Ӧ ץ��   �� ״̬ 
	else if (20 < b < 24)
		TIM_SetCompare2(TIM2,185); //150,1.6ms  ��Ӧ ץ��   �ر� ״̬
	else if (23 < b < 27)
     TIM_SetCompare4(TIM1,185); //150,1.6ms  ��Ӧ �м�ؽ�����״̬   ״̬
	else if (26 < b < 28)
		forward();
		DistanceFlag = 0;
		b = 0;
	}

	
	// �� ����ĳһ����ʱ �������䶯��
	if(DistanceFlag == 4)
	{	  
	switch(turn)
			{
			case 0:		//ֹͣ
							Motor_STOP_eight();		
							break;
			
			case 1:  //һֱ��ת
							Motor_REV_eight();		
							break;
			
			case 2:	//��תһ�����뵽����	�����ɵ������պõ��ﶥ����
							a++;
							if(a<2000)			Motor_FWD_eight();	
							else						ok=1;										//�ѵ��ﶥ��
							break;
			
			case 3:	//��תһ������		�����ʵ�������ʹ��Ͷ����Ҫ�ľ��룩
							a--;
							if(a>700)			Motor_REV_eight();			
							else       			{a = 0; ok = 0;	}				//�ѵ�����Ҫ�ľ���
							break;
							
			case 4:  //һֱ��ת
							Motor_FWD_eight();		
							break;
			
			default:	//ֹͣ
							Motor_STOP_eight();		
							break;
			
	}		
	

}		
 TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		}		 
	 }	 