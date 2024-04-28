#include <Wire.h>
#include "PinConfig.h"
#include "TIM.h"
#include "PID.h"
#include "OLED.h"
#include "Scurve.h"
#include "TrapezoidalCurve.h"

hw_timer_t *Timer = NULL;
double Timeclock = 0; // s
double velocity_angle = 0; // rad / s
int SteadyStateCnt = 0;
int VelocityCheckPointCnt = 0;
CurveSelectClass CurveSelect;

extern double position_angle; // rad
extern BarStateClass BarState;
extern bool OpenFlag;
extern bool CloseFlag;
extern double myscreen_buffer[128];

// Initialize the timer
void TIM_Init()
{
  Timer = timerBegin(0, 80, true); // use TIM0, div = 0, Count up
  timerAttachInterrupt(Timer, ONTIMER, true);
  timerAlarmWrite(Timer, TIME_OF_ITR * 1000, true); // T = TIME_OF_ITR * 1000 us= TIME_OF_ITR ms
  timerAlarmEnable(Timer);
  Timeclock_Clear();
}

/***************************************
Function: Clear the Timeclock
parameter: None
return : None
Sample: 
****************************************/
void Timeclock_Clear()
{
  Timeclock = 0;
}

void ONTIMER()
{
  static double last_position_angle = 0;
  Timeclock = Timeclock + TIME_OF_ITR * 0.001;
  velocity_angle = (position_angle - last_position_angle) / (TIME_OF_ITR * 0.001);
  last_position_angle = position_angle;

  if(OpenFlag)
  {
    Timeclock = 0;
    SteadyStateCnt = 0;
    BarState = Opening;
    OpenFlag = false;
    PID_Clear();
  }
  else if(CloseFlag)
  {
    Timeclock = 0;
    SteadyStateCnt = 0;
    BarState = Closing;
    CloseFlag = false;
    PID_Clear();
  }

  if(BarState == Opening)
  {
    PID_Control(Timeclock);
    if(CurveSelect == useScurve)
    {
      if(fabs(Scurve_position(Timeclock) - position_angle) <= 0.04)SteadyStateCnt ++;
    }
    else if(CurveSelect == useTrapezoidalCurve)
    {
      if(fabs(TrapezoidalCurve_position(Timeclock) - position_angle) <= 0.04)SteadyStateCnt ++;
    }
    if(SteadyStateCnt >= STEADYTHRESHOLD / (TIME_OF_ITR * 0.001)) BarState = Opened;
  }
  else if(BarState == Closing)
  {
    PID_Control(2 * ta + tm - Timeclock);
    if(CurveSelect == useScurve)
    {
      if(fabs(Scurve_position(2 * ta + tm - Timeclock) - position_angle) <= 0.04)SteadyStateCnt ++;
    }
    else if(CurveSelect == useTrapezoidalCurve)
    {
      if(fabs(TrapezoidalCurve_position(2 * ta + tm - Timeclock) - position_angle) <= 0.04)SteadyStateCnt ++;
    }
    if(SteadyStateCnt >= STEADYTHRESHOLD / (TIME_OF_ITR * 0.001)) BarState = Closed;
  }


/************************************FOR TEST************************************/
  VelocityCheckPointCnt ++;
  if(VelocityCheckPointCnt >= VELOCITYCHECKPOINT / TIME_OF_ITR)
  {
    VelocityCheckPointCnt = 0;
    for(uint8_t i = 1;i < 128; i++)
    {
        myscreen_buffer[i - 1] = myscreen_buffer[i];
    }
    myscreen_buffer[127] = velocity_angle;
  }
  /************************************FOR TEST************************************/
}