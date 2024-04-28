#include <Wire.h>
#include "PinConfig.h"
#include "Encoder.h"

int64_t position_cnt = 0;
double position_angle = 0; // rad

void Encoder_Init()
{
  position_cnt = 0;
  position_angle = 0; // rad
  // Initialize the Encoders
  attachInterrupt(digitalPinToInterrupt(C1), &C1_RISING_CNT, RISING);
  //attachInterrupt(digitalPinToInterrupt(C2), &C2_RISING_CNT, RISING);  
}

void IRAM_ATTR C1_RISING_CNT()
{
  if(digitalRead(C2) == LOW) position_cnt ++;
  else position_cnt --; 
  position_angle = (double)position_cnt / PULSE / GEAR_RATIO * 2 * pi;
}

// void IRAM_ATTR C2_RISING_CNT()
// {
//   if(digitalRead(C1) == HIGH) position_cnt ++;
//   else position_cnt --;
//   position_angle = (double)position_cnt / PULSE / GEAR_RATIO * 2 * pi;
// }

