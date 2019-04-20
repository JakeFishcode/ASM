#include "infrared.h"

/**********************
功能：检测地面直线 通过六路红外检测
测试：无
修改状态：无
***********************/
//初始化输入引脚
void infrared_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB3

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PB4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB4
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB5	
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//PB13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB13

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB14
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PB15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB15	
	
	
	
	
	
}