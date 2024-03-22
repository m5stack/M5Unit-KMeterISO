#include "M5UnitKmeterISO.h"
#include <string.h>

void M5UnitKmeterISO::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                 uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void M5UnitKmeterISO::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

bool M5UnitKmeterISO::begin(TwoWire *wire, uint8_t addr, uint8_t sda,
                            uint8_t scl, uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

int32_t M5UnitKmeterISO::getCelsiusTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, KMETER_TEMP_VAL_REG, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

int32_t M5UnitKmeterISO::getFahrenheitTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, KMETER_TEMP_VAL_REG + 4, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

int32_t M5UnitKmeterISO::getInternalCelsiusTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, KMETER_INTERNAL_TEMP_VAL_REG, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

int32_t M5UnitKmeterISO::getInternalFahrenheitTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, KMETER_INTERNAL_TEMP_VAL_REG + 4, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

void M5UnitKmeterISO::getCelsiusTempString(char *str) {
    char read_buf[8] = {0};

    readBytes(_addr, KMETER_TEMP_CELSIUS_STRING_REG, (uint8_t *)read_buf, 8);
    memcpy(str, read_buf, sizeof(read_buf));
}

void M5UnitKmeterISO::getFahrenheitTempString(char *str) {
    uint8_t read_buf[8] = {0};

    readBytes(_addr, KMETER_TEMP_FAHRENHEIT_STRING_REG, (uint8_t *)read_buf, 8);
    memcpy(str, read_buf, sizeof(read_buf));
}

void M5UnitKmeterISO::getInternalCelsiusTempString(char *str) {
    uint8_t read_buf[8] = {0};

    readBytes(_addr, KMETER_INTERNAL_TEMP_CELSIUS_STRING_REG,
              (uint8_t *)read_buf, 8);
    memcpy(str, read_buf, sizeof(read_buf));
}

void M5UnitKmeterISO::getInternalFahrenheitTempString(char *str) {
    uint8_t read_buf[8] = {0};

    readBytes(_addr, KMETER_INTERNAL_TEMP_FAHRENHEIT_STRING_REG,
              (uint8_t *)read_buf, 8);
    memcpy(str, read_buf, sizeof(read_buf));
}

uint8_t M5UnitKmeterISO::getReadyStatus(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, KMETER_KMETER_ERROR_STATUS_REG, read_buf, 1);
    return read_buf[0];
}

uint8_t M5UnitKmeterISO::getFirmwareVersion(void) {
    uint8_t reg;
    uint8_t read_buf[4] = {0};

    readBytes(_addr, KMETER_FIRMWARE_VERSION_REG, read_buf, 1);
    return read_buf[0];
}

bool M5UnitKmeterISO::setI2CAddress(uint8_t addr) {
    _wire->beginTransmission(_addr);
    _wire->write(KMETER_I2C_ADDRESS_REG);
    _wire->write(addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        _addr = addr;
        return true;
    } else {
        return false;
    }
}
