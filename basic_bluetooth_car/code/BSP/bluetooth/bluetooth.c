#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bluetooth.h" 
#include "motor.h" 
#include <string.h> 
#include <stdio.h>

//波特率：9600

uint8_t motor_rspeed=0;
uint8_t motor_state=0;		//电机状态
uint8_t motor_lspeed=0;

extern volatile uint8_t rx_data;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart ->Instance ==USART1 )
	{
		switch(rx_data)
		{
			case 'f':
				motor_rspeed =30;
				motor_lspeed=51;
				motor_setspeed( motor_left,motor_lspeed  );
				motor_setspeed( motor_right,motor_rspeed );
				motor_state=1; 
				break ;
			
			case 'b':
				motor_rspeed =30;
				motor_lspeed=51;
				motor_setspeed( motor_left,-motor_lspeed );
				motor_setspeed( motor_right,-motor_rspeed );
				motor_state =2;
				break;
				
			case '+':
				motor_rspeed +=10;
				motor_lspeed+=10;
				if(motor_state==1 && motor_state!=3 && motor_state!=4 )
				{
				motor_setspeed( motor_left,motor_lspeed );
				motor_setspeed( motor_right,motor_rspeed );
				}
				else if(motor_state ==2&& motor_state!=3 && motor_state!=4)
				{
				motor_setspeed( motor_left,-motor_lspeed );
				motor_setspeed( motor_right,-motor_rspeed );
				}
				break ;
				
			case '-':
				motor_rspeed -=10;
				motor_lspeed-=10;
				if(motor_state ==1&& motor_state!=3 && motor_state!=4)
				{
					motor_setspeed( motor_left,motor_lspeed );
					motor_setspeed( motor_right,motor_rspeed );
				}
			
				else if(motor_state ==2&& motor_state!=3 && motor_state!=4)
				{
					motor_setspeed( motor_left,-motor_lspeed );
					motor_setspeed( motor_right,-motor_rspeed );
				}
				break;
			
			
			case 's':
				motor_rspeed =0;
				motor_lspeed=0;
				motor_state =0;
				motor_setspeed( motor_left,motor_lspeed );
				motor_setspeed( motor_right,motor_rspeed );
				break ;
			
			case 'l':
				motor_rspeed =30;
				motor_lspeed=51;
				motor_state =3;
				motor_setspeed( motor_left,-motor_lspeed  );
				motor_setspeed( motor_right,motor_rspeed  );
				break ;
			
			case 'r':
				motor_rspeed =30;
				motor_lspeed=51;
				motor_state=4; 
				motor_setspeed( motor_left,motor_lspeed  );
				motor_setspeed( motor_right,-motor_rspeed );
				break ;
		}
		
	}
	HAL_UART_Receive_IT (&huart1 ,(uint8_t *)&rx_data ,1);
}

void sendstr(char *str)
{
	HAL_UART_Transmit (&huart1 ,(uint8_t *)str,strlen (str),HAL_MAX_DELAY );
}