#include "Shoot.h"
#include "sys.h"
#include "key.h"
#include "delay.h"
#include "led.h"


void Shoot_Init(u16 arr,u16 psc)  // ��ʼ�� ���������ĸ�����
{
   NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
    GPIO_InitTypeDef GPIO_InitStructure;	
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure); //���ݲ�����ʼ��PB12��13��14��15 ������� �ٶ�50MHz

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// TIM8ʹ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO C����ʱ��ʹ��  

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);//��������ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn; //TIM8 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� 0 ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ� 3 ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure); //��ʼ��NVIC�Ĵ���
	
  TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE �����ʹ��	

	TIM_ARRPreloadConfig(TIM8, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM8
}

//���巢�亯��
	u8 turn;			//�����ı䲽�������ת��
	u8 ok;				//�����ж��Ƿ���ɵı�־
	

		void Pellet_launching(void)		//С����
{ 
		LED0 = 0;     //   LED0 ȡ��
	 turn=0;			//�����ı䲽�������ת��
	 ok=0;				//�����ж��Ƿ���ɵı�־
	
	KEY_Init();								//����IO��ʼ��
	electricity_GPIO_Init();	//�����io��ʼ��
	delay_init();
	
	Shoot_Init(99,71);			//f = 72M / psc+1����װ��ֵ = arr + 1��	��T=1us��
													//һ��ʱ��(����תһȦ):(arr+1)*(psc+1)/(72*10^6)			��Tn=100us��
	delay_ms(40);			//��ʱ��С���ȶ�
	
	turn = 1;					//һֱ��ת
	while(KEY1);						//�жϰ����Ƿ���,ѭ��ֱ������������
	
	turn = 0;
	delay_ms(40);			//��ʱ��С���ȶ�
	
	turn = 2;			//��ת-���� (1700*1us)			���ɵ������պõ��ﶥ��
	while(!ok);		//ֱ�����ﶥ��
	electricity = 1;	//�����ͨ�磬��������
	
	turn =0;
	delay_ms(40);		//��ʱ��С���ȶ�
	
	turn = 3;			//��ת-���� (1700*1us)			���ʵ�������ʹ��Ͷ����Ҫ�ľ���
	while(ok);
	
	turn =0;
	delay_ms(40);			//��ʱ��С���ȶ�����
	
	electricity = 0;	//������ϵ磬С����
	LED0 = !LED0;     //   LED0 ȡ��
	delay_ms(20);			//��ʱ��С����
}

//����ֹͣ����

void Motor_STOP_eight(void)			//ֹͣ
{
	A1=0;B1=0;A2=0;B2=0;
}

//���巴ת����
void Motor_REV_eight(void)		//��ת
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
//������ת����

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
void TIM8_UP_IRQHandler(void) //TIM8 �ж�
{
		static int a=0;
		extern u8 turn;
		extern u8 ok;
	
    if(TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) //��� TIM2 �����жϷ������
    { 
			//LED1 = !LED1;
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
			TIM_ClearITPendingBit(TIM8, TIM_IT_Update ); 		//��� TIM2 �����жϱ�־

    }
}