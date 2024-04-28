#ifndef __OLED_H
#define __OLED_H

#include <Wire.h>

void OLED_Init();
void OLED_DrawChart();
void format_data(double *rawdata, uint32_t *buffer);

#endif