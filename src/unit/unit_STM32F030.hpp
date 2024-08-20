/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
/*!
  @file unit_STM32F030.hpp
  @brief KmeterISO Unit for M5UnitUnified
*/
#ifndef M5_UNIT_UNIFIED_KMETERISO_UNIT_STM32F030_HPP
#define M5_UNIT_UNIFIED_KMETERISO_UNIT_STM32F030_HPP

#include <M5UnitComponent.hpp>

namespace m5 {
namespace unit {

/*!
  @class UnitSTM32F030
  @brief KMeterISO unitis an integrated K-type thermocouple sensor unit that
  integrates the functions of "acquisition + isolation + communication"
 */
class UnitSTM32F030 : public Component {
    M5_UNIT_COMPONENT_HPP_BUILDER(UnitSTM32F030, 0x66);  // 66

   public:
    /*!
      @struct config_t
      @brief Settings
     */
    struct config_t {
        bool periodic{true};      //!< @brief start periodic?
        uint32_t interval{1000};  //!< @breif periodic interval
    };

    explicit UnitSTM32F030(const uint8_t addr = DEFAULT_ADDRESS) : Component(addr) {
    }
    virtual ~UnitSTM32F030() {
    }

    virtual bool begin() override;
    virtual void update(const bool force = false) override;

#if 0
    ///@name Settings
    ///@{
    /*! @brief Gets the configration */
    config_t config() {
        return _cfg;
    }
    //! @brief Set the configration
    void config(const config_t& cfg) {
        _cfg = cfg;
    }
    ///@}
#endif

    ///@name Properties
    ///@{
    //! @brief Latest celsius temperature
    float celsiusTemperature() const {
        return _temperatureC;
    }
    //! @brief Latest fahrenheit temperature
    float fahrenheitTemperature() const {
        return _temperatureF;
    }
    ///@}

    /*!
      @brief Read status
      @param[out] status Status
      @return True if successful
    */
    bool readStatus(uint8_t& status);
    /*!
      @brief Read firmware version
      @param[out] ver version
      @return True if successful
    */
    bool readFirmwareVersion(uint8_t& ver);

    ///@name Measurement
    ///@{
    bool startPeriodicMeasurement(const uint32_t interval);
    bool stopPeriodicMeasurement();

    /*!
      @brief Read celsius temperature
      @param[out] ct temperature(C)
      @return True if successful
      @note Value containing two decimal places
     */
    bool readCelsiusTemperature(int32_t& ct);
    /*!
      @brief Read fahrenheit temperature
      @param[out] ft temperature(F)
      @return True if successful
      @note Value containing two decimal places
    */
    bool readFahrenheitTemperature(int32_t& ft);
    /*!
      @brief Read internal celsius temperature
      @param[out] ct temperature(C)
      @return True if successful
      @note Value containing two decimal places
    */
    bool readInternalCelsiusTemperature(int32_t& ct);
    /*!
      @brief Read internal fahrenheit temperature
      @param[out] ft temperature(F)
      @return True if successful
      @note Value containing two decimal places
     */
    bool readInternalFahrenheitTemperature(int32_t& ft);
    /*!
      @brief Read celsius temperature string
      @param[out] str string buffer
      @return True if successful
      @warning str must be at least 9 bytes
    */
    bool readCelsiusTemperatureString(char* str);
    /*!
      @brief Read fahrenheit temperature string
      @param[out] str string buffer
      @return True if successful
      @warning str must be at least 9 bytes
    */
    bool readFahrenheitTemperatureString(char* str);
    /*!
      @brief Read internal celsius temperature string
      @param[out] str string buffer
      @return True if successful
      @warning str must be at least 9 bytes
    */
    bool readInternalCelsiusTemperatureString(char* str);
    /*!
      @brief Read internal fahrenheit temperature string
      @param[out] str string buffer
      @return True if successful
      @warning str must be at least 9 bytes
    */
    bool readInternalFahrenheitTemperatureString(char* str);
    ///@}

    ///@name I2C Address
    ///@warning Handling warning
    ///@{
    /*!
      @brief Change device I2C address
      @param i2c_address I2C address
      @return True if successful

    */
    bool changeI2CAddress(const uint8_t i2c_address);
    /*!
      @brief Read device I2C address
      @param[out] i2c_address I2C address
      @return True if successful
    */
    bool readI2CAddress(uint8_t& i2c_address);
    ///@}

    /*!
      @brief Temperature conversion
      @param temp Value obtained
      @return temperature(float)
     */
    static inline float conversion(const int32_t temp) {
        return temp / 100.0f;
    }

   protected:
    bool read_measurement();

   protected:
    float _temperatureC{}, _temperatureF{};

    config_t _cfg{};
};

namespace stm32f030 {
namespace command {
///@cond
constexpr uint8_t TEMP_CELSIUS_VAL_REG{0X00};
constexpr uint8_t TEMP_FAHRENHEIT_VAL_REG{0X04};
constexpr uint8_t INTERNAL_TEMP_CELSIUS_VAL_REG{0X10};
constexpr uint8_t INTERNAL_TEMP_FAHRENHEIT_VAL_REG{0X14};
constexpr uint8_t ERROR_STATUS_REG{0x20};
constexpr uint8_t TEMP_CELSIUS_STRING_REG{0x30};
constexpr uint8_t TEMP_FAHRENHEIT_STRING_REG{0x40};
constexpr uint8_t INTERNAL_TEMP_CELSIUS_STRING_REG{0x50};
constexpr uint8_t INTERNAL_TEMP_FAHRENHEIT_STRING_REG{0x60};
constexpr uint8_t FIRMWARE_VERSION_REG{0xFE};
constexpr uint8_t I2C_ADDRESS_REG{0xFF};
///@endcond
}  // namespace command
}  // namespace stm32f030

}  // namespace unit
}  // namespace m5
#endif
