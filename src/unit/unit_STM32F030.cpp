/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
/*!
  @file unit_STM32F030.cpp
  @brief STM32F030 Unit for M5UnitUnified
*/
#include "unit_STM32F030.hpp"
#include <M5Utility.hpp>
#include <array>
#include <thread>

using namespace m5::utility::mmh3;
using namespace m5::unit::types;
using namespace m5::unit::stm32f030;
using namespace m5::unit::stm32f030::command;

namespace {
template <typename T>
T array_to_type(const std::array<uint8_t, 4>& a) {
    static_assert(std::is_integral<T>::value && sizeof(T) == 4, "Invalid type");
    return (((uint32_t)a[3]) << 24) | (((uint32_t)a[2]) << 16) | (((uint32_t)a[1]) << 8) | (((uint32_t)a[0]) << 0);
}
}  // namespace

namespace m5 {
namespace unit {
// class UnitSTM32F030
const char UnitSTM32F030::name[] = "UnitSTM32F030";
const types::uid_t UnitSTM32F030::uid{"UnitSTM32F030"_mmh3};
const types::uid_t UnitSTM32F030::attr{0};

bool UnitSTM32F030::begin() {
    uint8_t ver{0x00};
    if (!readFirmwareVersion(ver) && (ver == 0x00)) {
        M5_LIB_LOGE("Failed to read version");
        return false;
    }
    return _cfg.periodic ? startPeriodicMeasurement(_cfg.interval) : true;
}

void UnitSTM32F030::update(const bool force) {
    _updated = false;
    if (inPeriodic()) {
        elapsed_time_t at{m5::utility::millis()};
        if (force || !_latest || at >= _latest + _interval) {
            _updated = read_measurement();
            if (_updated) {
                _latest = at;
            }
        }
    }
}

bool UnitSTM32F030::startPeriodicMeasurement(const uint32_t interval) {
    _interval = interval;
    _periodic = true;
    _latest   = 0;
    return true;
}

bool UnitSTM32F030::stopPeriodicMeasurement() {
    _periodic = _updated = false;
    return true;
}

bool UnitSTM32F030::readStatus(uint8_t& status) {
    return readRegister8(ERROR_STATUS_REG, status, 0);
}

bool UnitSTM32F030::readFirmwareVersion(uint8_t& ver) {
    return readRegister8(FIRMWARE_VERSION_REG, ver, 0);
}

bool UnitSTM32F030::readCelsiusTemperature(int32_t& ct) {
    std::array<uint8_t, 4> rbuf{};
    if (readRegister(TEMP_CELSIUS_VAL_REG, rbuf.data(), rbuf.size(), 0)) {
        ct = array_to_type<int32_t>(rbuf);
        return true;
    }
    return false;
}

bool UnitSTM32F030::readFahrenheitTemperature(int32_t& ft) {
    std::array<uint8_t, 4> rbuf{};
    if (readRegister(TEMP_FAHRENHEIT_VAL_REG, rbuf.data(), rbuf.size(), 0)) {
        ft = array_to_type<int32_t>(rbuf);
        return true;
    }
    return false;
}

bool UnitSTM32F030::readInternalCelsiusTemperature(int32_t& ct) {
    std::array<uint8_t, 4> rbuf{};
    if (readRegister(INTERNAL_TEMP_CELSIUS_VAL_REG, rbuf.data(), rbuf.size(), 0)) {
        ct = array_to_type<int32_t>(rbuf);
        return true;
    }
    return false;
}

bool UnitSTM32F030::readInternalFahrenheitTemperature(int32_t& ft) {
    std::array<uint8_t, 4> rbuf{};
    if (readRegister(INTERNAL_TEMP_FAHRENHEIT_VAL_REG, rbuf.data(), rbuf.size(), 0)) {
        ft = array_to_type<int32_t>(rbuf);
        return true;
    }
    return false;
}

bool UnitSTM32F030::readCelsiusTemperatureString(char* str) {
    if (str && readRegister(TEMP_CELSIUS_STRING_REG, (uint8_t*)str, 8U, 0)) {
        str[8] = '\0';
        return true;
    }
    return false;
}

bool UnitSTM32F030::readFahrenheitTemperatureString(char* str) {
    if (str && readRegister(TEMP_FAHRENHEIT_STRING_REG, (uint8_t*)str, 8U, 0)) {
        str[8] = '\0';
        return true;
    }
    return false;
}

bool UnitSTM32F030::readInternalCelsiusTemperatureString(char* str) {
    if (readRegister(INTERNAL_TEMP_CELSIUS_STRING_REG, (uint8_t*)str, 8U, 0)) {
        str[8] = '\0';
        return true;
    }
    return false;
}

bool UnitSTM32F030::readInternalFahrenheitTemperatureString(char* str) {
    if (str && readRegister(INTERNAL_TEMP_FAHRENHEIT_STRING_REG, (uint8_t*)str, 8U, 0)) {
        str[8] = '\0';
        return true;
    }
    return false;
}

bool UnitSTM32F030::changeI2CAddress(const uint8_t i2c_address) {
    if (!m5::utility::isValidI2CAddress(i2c_address)) {
        M5_LIB_LOGE("Invalid address : %02X", i2c_address);
        return false;
    }
    if (writeRegister8(I2C_ADDRESS_REG, i2c_address) && changeAddress(i2c_address)) {
        // Wait wakeup
        uint8_t v{};
        bool done{};
        auto timeout_at = m5::utility::millis() + 100;
        do {
            done = readRegister8(I2C_ADDRESS_REG, v, 0);
            std::this_thread::yield();
        } while (!done && m5::utility::millis() <= timeout_at);
        return done;
    }
    return false;
}

bool UnitSTM32F030::readI2CAddress(uint8_t& i2c_address) {
    return readRegister8(I2C_ADDRESS_REG, i2c_address, 0);
}

//
bool UnitSTM32F030::read_measurement() {
    uint8_t status{0xFF};
    if (!readStatus(status) || (status != 0)) {
        M5_LIB_LOGW("Not read or error:%Xx", status);
        return false;
    }
    int32_t c{}, f{};
    if (readCelsiusTemperature(c) && readFahrenheitTemperature(f)) {
        _temperatureC = conversion(c);
        _temperatureF = conversion(f);
        return true;
    }
    return false;
}

}  // namespace unit
}  // namespace m5
