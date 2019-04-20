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
extern u8   TIM3CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16  TIM3CH1_CAPTURE_VAL;	//���벶��ֵ	
extern  u8  TIM4CH1_CAPTURE_STA;	//���벶��״̬		(�����־λ)    				
extern u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ        ��������ֵ��
extern u32 temp1, temp2; 
extern unsigned int blob_x;//������usart��
extern unsigned int blob_y;
extern int b;
#define REC_NULL 255
#define OBJECT_X 255
#define OBJECT_Y 45
#define RANGE

unsigned char str2[6]="000000";
int main(void)
{
	delay_init();	    	 //��ʱ������ʼ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2*
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600 
	LED_Init();	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	CAR_INIT(); 
  Trig_10us_IO_Init();
	
	TIM3_Int_Init(99998,71); //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	TIM5_Int_Init(99998,71); //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
	Contor_Int_Init(7999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  	 
	Motor_PWM_Init(199,7199);//���PWM��ʼ��
	forward();   //С��ǰ��	 
	TIM_SetCompare4(TIM1,150); //150,1.6ms 
	TIM_SetCompare2(TIM2,0); //150,1.6ms 
	TIM_SetCompare3(TIM2,0); //150,1.6ms 
	TIM_SetCompare4(TIM2,0); //150,1.6ms 
  while(1)
	{
		
		trigger();  //�������� ��������������
		measure();  //��������ʼ��������
		
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

/* if (1 )                //ץȡ����
{	
	DistanceFlag = 4;    //������ĳһ����ʱ  ����ץȡ
}
if (1)
{
	DistanceFlag = 4;    //������ĳһ����ʱ  �������䶯��
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

