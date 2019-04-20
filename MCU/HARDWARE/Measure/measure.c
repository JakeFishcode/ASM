#include "measure.h"
#include "led.h"
#include "usart.h" 
#include "delay.h"

//ͨ�ö�ʱ���жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!�Լ���ʱ��4��

  void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��3ʹ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

	//PA6��ʼ������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);	
	
	//��ʼ����ʱ��3 
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_ICPSC_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	
	//��ʼ��TIM3���벶�����
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter=0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//�����ز���
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//ӳ�䵽TI1
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	
	
	//�ж�3�����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

   TIM_ITConfig( TIM3, TIM_IT_Update|TIM_IT_CC1 ,ENABLE  );
	 TIM_Cmd(TIM3, ENABLE);  //ʹ�ܶ�ʱ��3	
}

// ��ʼ����ʱ��3����

u8  TIM3CH1_CAPTURE_STA=0;	//���벶��״̬		(�����־λ)    				
u16	TIM3CH1_CAPTURE_VAL;	//���벶��ֵ        ��������ֵ��

//TIM 3�жϺ�������
void TIM3_IRQHandler(void)
{ 
 	if((TIM3CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//�ж��Ƿ������� ���ǲ��Ƿ�������жϣ�	 
		{	    
			if(TIM3CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM3CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH1_CAPTURE_STA=0;			//���
				TIM3CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);
				TIM3CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   	 TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
	
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
 
}


void TIM5_Int_Init(u16 arr,u16 psc)
{
  TIM_ICInitTypeDef TIM5_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��5ʹ��	  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

	
	//PB6��ʼ��

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
	
	//��ʼ����ʱ��4
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_ICPSC_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM4���벶�����
	
	TIM5_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM5_ICInitStructure.TIM_ICFilter=0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM5_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//�����ز���
	TIM5_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM5_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//ӳ�䵽TI1
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);	
	
	//�ж�4�����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	 TIM_ITConfig( TIM5, TIM_IT_Update|TIM_IT_CC1 ,ENABLE  );

   TIM_Cmd(TIM5, ENABLE);  //ʹ�ܶ�ʱ��4	
}

//��ʱ�� 4�жϷ�������

u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		(�����־λ)    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ        ��������ֵ��

//TIM 4�жϺ�������
void TIM5_IRQHandler(void)
{  

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//�ж��Ƿ������� ���ǲ��Ƿ�������жϣ�	 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   	 TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
	}
//PC11 PC12 һ��10us�ߵ�ƽ������
void Trig_10us_IO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure; 
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;		//ʹ��PA4 PA5 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  
 GPIO_Init(GPIOC, &GPIO_InitStructure);					  
 GPIO_ResetBits(GPIOC,GPIO_Pin_11);	
 GPIO_ResetBits(GPIOC,GPIO_Pin_12);			
}

//��ӡ����������ľ���
  u32 temp1=0; 
  u32 temp2=0;
float  measure()
{ 
	  
	if(TIM3CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp1=TIM3CH1_CAPTURE_STA&0X3F;
			temp1*=65536;//���ʱ���ܺ�
			temp1+=TIM3CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
					
			temp1=(float)temp1*0.017;			//�õ�DAC��ѹֵ
		   printf("Front_Measure:%d cm\r\n",temp1);//��ӡ�ܵľ���
	
			TIM3CH1_CAPTURE_STA=0;//������һ�β���
		}
		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp2=TIM5CH1_CAPTURE_STA&0X3F;
			temp2*=65536;//���ʱ���ܺ�
			temp2+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
					
			temp2=(float)temp2*0.017;			//�õ�DAC��ѹֵ
			printf("Left_Measure:%d cm\r\n",temp2);//��ӡ�ܵľ���
			
			TIM5CH1_CAPTURE_STA=0;//������һ�β���
		}
		
}

//���������������� ��������������λ������

void trigger()
{
     Trig_1=1;
		 Trig_2=1;
		delay_us(10);
		 Trig_1=0;
		 Trig_2=0;
		delay_us(25);
}
