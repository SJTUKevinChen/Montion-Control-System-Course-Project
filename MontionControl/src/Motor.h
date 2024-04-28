#ifndef __MOTOR_H
#define __MOTOR_H
#include "PinConfig.h"

void Motor_Init();
void Motor_Rotate(Direction dir, double duty_cycle);

#endif