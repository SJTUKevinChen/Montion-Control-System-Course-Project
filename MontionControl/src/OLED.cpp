#include <U8g2lib.h>
#include <Wire.h>
#include "PinConfig.h"
#include "OLED.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /*clock=*/SCL, /*data=*/SDA, /*reset=*/U8X8_PIN_NONE);   
double myscreen_buffer[128];

void OLED_Init()
{
  u8g2.begin();
  u8g2.enableUTF8Print(); // enable UTF8 support for the Arduino print() function
}

void OLED_DrawChart()
{ 
    // for(uint8_t i = 1;i < 128; i++)
    // {
    //     myscreen_buffer[i - 1] = myscreen_buffer[i];
    // }
    // myscreen_buffer[127] = value;

    uint32_t buffer_formated[128];
    format_data(myscreen_buffer, buffer_formated);

    
    u8g2.clearBuffer();

    for(uint8_t i = 0; i < 127; i++)
    {
        u8g2.drawLine(i, 64 - buffer_formated[i], i+1, 64 - buffer_formated[i+1]);
    }
    u8g2.setFont(u8g2_font_unifont_t_chinese2); 
    u8g2.setFontDirection(0);
    char str[50];
    sprintf(str, "w=%.4lf rad/s", myscreen_buffer[127]);
    u8g2.setCursor(0, 15);
    u8g2.print(str);
    u8g2.sendBuffer();

}

void format_data(double *rawdata, uint32_t *buffer)
{
    uint8_t index = 1;
    double min, max, range;
    double num = rawdata[0];
    min = num;
    max = num;
    do
    {
        num = rawdata[index];
        if(num < min) min = num;
        if(num > max) max = num;
    } while(++index < 128);
    index = 0;
    range = max - min;

    if(range > 0)
    {
        do
        {
            num = rawdata[index];
            buffer[index] = (int)((num - min) * 64 / range);
        } while(++index < 128);
        
    }
}