#include <Wire.h>
#include "StateControl.h"
#include "PinConfig.h"

BarStateClass BarState;
bool OpenFlag;
bool CloseFlag;

extern double Timeclock; // s


void Button_Init()
{
    BarState = Closed;
    OpenFlag = false;
    CloseFlag = false;
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), &BUTTON_RISING, RISING);
}

void IRAM_ATTR BUTTON_RISING()
{
    if(BarState == Closed) OpenFlag = true;
    else if(BarState == Opened) CloseFlag = true;
}