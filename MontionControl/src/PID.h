#ifndef __PID_H
#define __PID_H

void PID_Velocity_Init(double p, double i ,double d);
void PID_Velocity(double t);
void PID_Position_Init(double p, double i, double d);
void PID_Position(double t);
void PID_Control(double t);
void PID_Clear();

#endif