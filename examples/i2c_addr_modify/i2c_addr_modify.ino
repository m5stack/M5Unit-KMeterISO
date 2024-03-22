
/**
 * @file i2c_addr_modify.ino
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

M5UnitKmeterISO kmeter;

void setup() {
    delay(2000);
    Serial.begin(115200);
    while (!kmeter.begin(&Wire, KMETER_DEFAULT_ADDR, 21, 22, 100000L)) {
        Serial.println("Unit KmeterISO not found");
    }

    if (kmeter.setI2CAddress(KMETER_DEFAULT_ADDR + 1)) {
        Serial.printf("Modify KmeterISO I2C Addr to  %02X",
                      KMETER_DEFAULT_ADDR + 1);
    } else {
        Serial.println("I2C Addr Modify Fail");
    }
}

void loop() {
}