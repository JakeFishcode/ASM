#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


#define KEY1 PAin(15)	 	//用来判断是否转到底部
#define  electricity PBout(10)	 	//用来控制电磁铁，高电平吸，低电平断
	 
void KEY_Init(void);//按键IO初始化
void  electricity_GPIO_Init(void);	//电磁铁io初始化
#endif
