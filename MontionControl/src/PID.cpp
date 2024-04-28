#include <Wire.h>
#include "PinConfig.h"
#include "PID.h"
#include "Scurve.h"
#include "Motor.h"
#include "TrapezoidalCurve.h"

extern double velocity_angle;
extern double position_angle;
extern double Timeclock; // s
extern double Current_Duty_Cycle;
extern CurveSelectClass CurveSelect;
double PID_output = 0;
extern BarStateClass BarState;

typedef struct{
    double Kp;
    double Ki;
    double Kd;
    double Integer;
    double Last_Error;
    double output;
} PID_Controller;

PID_Controller PID_Controller_Velocity;
PID_Controller PID_Controller_Position;

double InRange(double data, double MINIMUM, double MAXIMUM)
{
    if(data > MAXIMUM) return MAXIMUM;
    else if(data < MINIMUM) return MINIMUM;
    else return data;
}

void PID_Clear()
{
    PID_Controller_Velocity.Integer = 0;
    PID_Controller_Velocity.Last_Error = 0;
    PID_Controller_Velocity.output = 0;
    PID_Controller_Position.Integer = 0;
    PID_Controller_Position.Last_Error = 0;
    PID_Controller_Position.output = 0;
}
void PID_Velocity_Init(double p = 1, double i = 0, double d = 0)
{
    PID_Controller_Velocity.Kp = p;
    PID_Controller_Velocity.Ki = i;
    PID_Controller_Velocity.Kd = d;
    PID_Controller_Velocity.Integer = 0;
    PID_Controller_Velocity.Last_Error = 0;
    PID_Controller_Velocity.output = 0;
}

void PID_Position_Init(double p = 1, double i = 0, double d = 0)
{
    PID_Controller_Position.Kp = p;
    PID_Controller_Position.Ki = i;
    PID_Controller_Position.Kd = d;
    PID_Controller_Position.Integer = 0;
    PID_Controller_Position.Last_Error = 0;
    PID_Controller_Position.output = 0;
}


// 速度PID未启用
void PID_Velocity(double t)
{
    double Error = Scurve_velocity(t) - velocity_angle;
    
    PID_Controller_Velocity.output = 0;
    PID_Controller_Velocity.Integer += Error;

    PID_Controller_Velocity.output += PID_Controller_Velocity.Kp * Error;
    PID_Controller_Velocity.output += PID_Controller_Velocity.Ki * PID_Controller_Velocity.Integer;
    PID_Controller_Velocity.output += PID_Controller_Velocity.Kd * (Error - PID_Controller_Velocity.Last_Error);

    PID_Controller_Velocity.Last_Error = Error;
    /************************************FOR TEST************************************/
    // Motor_Rotate(Forward, InRange(Current_Duty_Cycle + output, 0, 100));

    // if(output < 0)Motor_Rotate(Stop, 0);
    // else if(output > 100)Motor_Rotate(Forward, 100);
    // else Motor_Rotate(Forward, output);

    // if(output > 100) Motor_Rotate(Forward, 100);
    // else if(output < -100) Motor_Rotate(Backward, 100);
    // else if(output > 0) Motor_Rotate(Forward, output);
    // else if(output <= 0)Motor_Rotate(Backward, -output);
    /************************************FOR TEST************************************/
}

void PID_Position(double t)
{   
    double Error;
    if(CurveSelect == useScurve) Error = Scurve_position(t) - position_angle;
    else if(CurveSelect == useTrapezoidalCurve) Error = TrapezoidalCurve_position(t) - position_angle;

    PID_Controller_Position.output = 0;
    PID_Controller_Position.Integer += Error;
    
    PID_Controller_Position.output += PID_Controller_Position.Kp * Error;
    PID_Controller_Position.output += PID_Controller_Position.Ki * PID_Controller_Position.Integer;
    PID_Controller_Position.output += PID_Controller_Position.Kd * (Error - PID_Controller_Position.Last_Error);

    PID_Controller_Position.Last_Error = Error;
}

void PID_Control(double t)
{
    PID_output = 0;
    // if(BarState == Opening && t <= ta / 4)
    // {
    //     PID_output += 0.25 - 0.25 / (ta / 4) * t;
    // }
    // else if(BarState == Closing && t >= ta + tm + 3 * ta / 4)
    // {
    //     PID_output += 0.25 - 0.25 / (ta / 4) * (2 * ta + tm - t);
    // }
    PID_Position(t);
    // PID_Velocity(t);
    PID_output += PID_Controller_Position.output / (pi / 2) * 100;
    // PID_output += PID_Controller_Velocity.output;

    if(PID_output > 100) Motor_Rotate(Forward, 100);
    else if(PID_output < -100) Motor_Rotate(Backward, 100);
    else if(PID_output > 0) Motor_Rotate(Forward, PID_output);
    else if(PID_output <= 0)Motor_Rotate(Backward, -PID_output);
}