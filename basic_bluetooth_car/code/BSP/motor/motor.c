#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "motor.h"  
#include <string.h> 
#include <stdio.h>
#include <stdlib.h> 

void motor_Init(void )
{
	HAL_GPIO_WritePin (GPIOB ,GPIO_PIN_12 ,GPIO_PIN_RESET );
	HAL_GPIO_WritePin (GPIOB ,GPIO_PIN_13 ,GPIO_PIN_RESET );
	HAL_GPIO_WritePin (GPIOB ,GPIO_PIN_14 ,GPIO_PIN_RESET );
	HAL_GPIO_WritePin (GPIOB ,GPIO_PIN_15 ,GPIO_PIN_RESET );
	
	HAL_TIM_PWM_Start (&htim3 ,TIM_CHANNEL_1 );
	HAL_TIM_PWM_Start (&htim3 ,TIM_CHANNEL_2 );
	
	__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_2,0);
}

void motor_setspeed(motor_type name ,int speed)
{
	uint32_t arr=__HAL_TIM_GET_AUTORELOAD (&htim3 );
	uint32_t pulse=(uint32_t )((abs(speed)) *0.01*arr );
	
	if(speed >100) speed=100;
	if(speed <-100) speed =-100;
	
	if(name ==motor_left)
	{
		HAL_TIM_PWM_Stop (&htim3 ,TIM_CHANNEL_1 );
		
		if(speed >0 )
		{
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_13 ,GPIO_PIN_SET );
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_12 ,GPIO_PIN_RESET );
		}
		else if(speed<0 )
		{
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_13 ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_12 ,GPIO_PIN_SET );
		}
		else 
		{
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_13 ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_12 ,GPIO_PIN_RESET );
		}
		
		__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_1 ,pulse );	
		HAL_TIM_PWM_Start (&htim3 ,TIM_CHANNEL_1 );
	}			//左电机
	
	if(name ==motor_right)
	{
		HAL_TIM_PWM_Stop (&htim3 ,TIM_CHANNEL_2 );
		
		if(speed >0 )
		{
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_15 ,GPIO_PIN_SET );
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_14 ,GPIO_PIN_RESET );
		}
		else if(speed<0 )
		{
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_15 ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_14 ,GPIO_PIN_SET );
		}
		else 
		{
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_15 ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_14 ,GPIO_PIN_RESET );
		}
		
		__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_2 ,pulse );
		HAL_TIM_PWM_Start (&htim3 ,TIM_CHANNEL_2 );	
	}				//右电机
}
	