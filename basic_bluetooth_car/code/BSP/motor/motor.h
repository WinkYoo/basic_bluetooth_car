#ifndef MOTOR_H
#define MOTOR_H

#include "main.h" 

typedef enum {
	motor_left,
	motor_right
}motor_type;

void motor_Init(void );
void motor_setspeed(motor_type name,int speed);

#endif
