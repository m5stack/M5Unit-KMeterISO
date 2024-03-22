#ifndef _M5_UNIT_KMETER_ISO_H_
#define _M5_UNIT_KMETER_ISO_H_

#include "Arduino.h"
#include "Wire.h"

#define KMETER_DEFAULT_ADDR                        0x66
#define KMETER_TEMP_VAL_REG                        0x00
#define KMETER_INTERNAL_TEMP_VAL_REG               0x10
#define KMETER_KMETER_ERROR_STATUS_REG             0x20
#define KMETER_TEMP_CELSIUS_STRING_REG             0x30
#define KMETER_TEMP_FAHRENHEIT_STRING_REG          0x40
#define KMETER_INTERNAL_TEMP_CELSIUS_STRING_REG    0x50
#define KMETER_INTERNAL_TEMP_FAHRENHEIT_STRING_REG 0x60
#define KMETER_FIRMWARE_VERSION_REG                0xFE
#define KMETER_I2C_ADDRESS_REG                     0xFF

class M5UnitKmeterISO {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t addr = KMETER_DEFAULT_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 100000L);
    int32_t getCelsiusTempValue(void);
    int32_t getFahrenheitTempValue(void);
    int32_t getInternalCelsiusTempValue(void);
    int32_t getInternalFahrenheitTempValue(void);
    uint8_t getReadyStatus(void);
    void getCelsiusTempString(char *str);
    void getFahrenheitTempString(char *str);
    void getInternalCelsiusTempString(char *str);
    void getInternalFahrenheitTempString(char *str);
    uint8_t getFirmwareVersion(void);

    bool setI2CAddress(uint8_t addr);
};

#endif
