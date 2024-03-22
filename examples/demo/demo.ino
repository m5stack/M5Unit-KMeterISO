/**
 * @file demo.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief
 * @version 0.1
 * @date 2024-03-22
 *
 *
 * @Hardwares: M5Core + Unit KmeterISO
 * @Platform Version: Arduino M5Stack Board Manager v2.1.1
 * @Dependent Library:
 * M5UnitKmeterISO: https://github.com/m5stack/M5Unit-KMeterISO
 */

#include "M5UnitKmeterISO.h"

#define INTERVAL_TIME 500

M5UnitKmeterISO kmeter;
uint8_t error_status = 0;
long delay_time      = 0;

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
    Serial.begin(115200);
    while (!kmeter.begin(&Wire, KMETER_DEFAULT_ADDR, 21, 22, 100000L)) {
        Serial.println("Unit KmeterISO not found");
    }

    delay_time = millis() + INTERVAL_TIME;
}

void loop() {
    if (millis() > delay_time) {
        error_status = kmeter.getReadyStatus();
        if (error_status == 0) {
            Serial.printf("Celsius Temp: %.2fC\r\n",
                          ((float)(kmeter.getCelsiusTempValue())) / 100);
            Serial.printf("Fahrenheit Temp: %.2fF\r\n",
                          ((float)(kmeter.getFahrenheitTempValue())) / 100);
            Serial.printf(
                "Chip Celsius Temp: %.2fC\r\n",
                ((float)(kmeter.getInternalCelsiusTempValue())) / 100);
            Serial.printf(
                "Chip Fahrenheit Temp: %.2fF\r\n",
                ((float)(kmeter.getInternalFahrenheitTempValue())) / 100);
        } else {
            Serial.printf("Error: %d", kmeter.getReadyStatus());
        }

        delay_time = millis() + INTERVAL_TIME;
    }
}