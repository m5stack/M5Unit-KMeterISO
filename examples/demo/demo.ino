
#include <M5Stack.h>
#include <M5GFX.h>
#include "UNIT_KMETER.h"

#define INPUT_PINS 36

M5GFX display;
M5Canvas canvas(&display);
UNIT_KMETER kmeter;
uint8_t error_status = 0;
uint8_t kmeter_switch = 0;

char temp_celsius[9] = {0};
char temp_fahrenheit[9] = {0};
char inter_temp_celsius[9] = {0};
char inter_temp_fahrenheit[9] = {0};

long delay_time = 0;

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  M5.begin();
  display.begin();
  canvas.setColorDepth(8);
  canvas.setFont(&fonts::efontCN_12);
  canvas.setTextSize(2);
  canvas.setTextColor(ORANGE);
  canvas.createSprite(display.width(), display.height());
  canvas.pushSprite(0, 0); 
  kmeter.begin(&Wire, 0x66, 21, 22, 100000L);
  delay_time = millis() + 10;
}

void loop() {
  if (millis() > delay_time) {
    canvas.fillSprite(0);
    canvas.setTextColor(ORANGE);
    canvas.drawString("Kmeter Test", 50, 0);
    canvas.setCursor(10, 50);
    canvas.setTextSize(3);
    error_status = kmeter.getReadyStatus();
    if (error_status == 0) {
      canvas.setTextColor(GREEN);
      canvas.printf("Temp: %.2fC", ((float)(kmeter.getCelsiusTempValue())) / 100);            
      canvas.setCursor(10, 90);
      canvas.printf("Chip Temp: %.2fC", ((float)(kmeter.getInternalCelsiusTempValue())) / 100);          
    }
    else {
      canvas.setTextColor(RED);
      canvas.printf("Error: %d", kmeter.getReadyStatus());
    }

    canvas.pushSprite(0, 0);         
    delay_time  = millis() + 10;
  }     
}