#include <Wire.h>
#include "PinConfig.h"
#include "Motor.h"

double Current_Duty_Cycle = 0;

void Motor_Init()
{
  // Initialize the PWM Controller
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  ledcAttachPin(PWM, 0);
  ledcSetup(0, PWM_FRE, RESOLUTION);   
}

/***************************************
Function: Make the Motor rotate
Parameter1: dir(Direction):Forward, Backward, Stop
Parameter2: duty_cycle(double):0 ~ 100
Return: None
Sample: Motor_Rotate(Forward, 50.0)
****************************************/
void Motor_Rotate(Direction dir, double duty_cycle)
{
  Current_Duty_Cycle = duty_cycle;
  if(dir == Forward)
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(0, duty_cycle * 0.01 * 255);
  }
  else if(dir == Backward)
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(0, duty_cycle * 0.01 * 255);
  }
  else if(dir == Stop)
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}