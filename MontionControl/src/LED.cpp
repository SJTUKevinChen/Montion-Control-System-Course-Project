#include <Wire.h>
#include "LED.h"
#include "PinConfig.h"

#define RED_LED_ON digitalWrite(RED_LED, HIGH)
#define YELLOW_LED_ON digitalWrite(YELLOW_LED, HIGH)
#define GREEN_LED_ON digitalWrite(GREEN_LED, HIGH)
#define CURVE_IDT_LED_ON digitalWrite(CURVE_IDT_LED, HIGH)
#define RED_LED_OFF digitalWrite(RED_LED, LOW)
#define YELLOW_LED_OFF digitalWrite(YELLOW_LED, LOW)
#define GREEN_LED_OFF digitalWrite(GREEN_LED, LOW)
#define CURVE_IDT_LED_OFF digitalWrite(CURVE_IDT_LED, LOW)
extern BarStateClass BarState;
extern CurveSelectClass CurveSelect;

void LED_Init()
{
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(CURVE_IDT_LED, OUTPUT);
}

void LED_ShowState()
{
    if(BarState == Closed)
    {
        RED_LED_ON;
        YELLOW_LED_OFF;
        GREEN_LED_OFF;
    }
    else if(BarState == Opened)
    {
        GREEN_LED_ON;
        RED_LED_OFF;
        YELLOW_LED_OFF;
    }
    else
    {
        YELLOW_LED_ON;
        GREEN_LED_OFF;
        RED_LED_OFF;
    }
}

void LED_ShowCurve()
{
    if(CurveSelect == useScurve)
    {
        CURVE_IDT_LED_ON;
    }
    else if(CurveSelect == useTrapezoidalCurve)
    {
        CURVE_IDT_LED_OFF;
    }

}