#ifndef __PINCONFIG_H
#define __PINCONFIG_H

#define pi 3.12159265 //3.14159265
#define ta 4 // Acceleration/Deceleration time
#define tm 4 // Time running in constant speed
#define SCL 13
#define SDA 12
#define IN3 4
#define IN4 16
#define C1 17 //17
#define C2 5 //5
#define PWM 2 
#define BUTTON 23
#define RED_LED 18
#define YELLOW_LED 19
#define GREEN_LED 21
#define CURVE_IDT_LED 22
#define GEAR_RATIO 810
#define PULSE 11 // Pulses per revolution 
#define TIME_OF_ITR 20 // time of interruption(ms)
#define PWM_FRE 100000 // PWM frequency
#define RESOLUTION 8 // PWM resolution(bit)
#define STEADYTHRESHOLD 4 // the time threshold recognizing the steady system (s)
#define VELOCITYCHECKPOINT 100 // ms

typedef enum{Forward, Backward, Stop} Direction;
typedef enum{Closed, Opening, Opened, Closing} BarStateClass;
typedef enum{useTrapezoidalCurve, useScurve} CurveSelectClass;



#endif