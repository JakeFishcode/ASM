#include "infrared.h"

/**********************
���ܣ�������ֱ�� ͨ����·������
���ԣ���
�޸�״̬����
***********************/
//��ʼ����������
void infrared_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTBʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB3

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PB4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB4
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB5	
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//PB13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB13

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB14
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PB15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB15	
	
	
	
	
	
}