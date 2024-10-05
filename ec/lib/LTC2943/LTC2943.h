// Code from: https://build.particle.io/libs/LTC2943/1.0.0/tab/LTC2943.cpp
// Modified by Byran Huang 2024
// anyon_e project

/*
Copyright 2011(c) Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
    - Neither the name of Analog Devices, Inc. nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
    - The use of this software may or may not infringe the patent rights
      of one or more patent holders.  This license does not release you
      from the requirement that you obtain separate licenses from these
      patent holders to use this software.
    - Use of the software either in source or binary form, must be run
      on or directly connected to an Analog Devices Inc. component.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED.

IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, INTELLECTUAL PROPERTY
RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LTC2943_H
#define LTC2943_H

/*! @name LTC2943 I2C Address
@{ */

#define LTC2943_I2C_ADDRESS 0x64
#define LTC2943_I2C_ALERT_RESPONSE  0x0C
//! @}


/*!
| Name                                              | Value |
| :------------------------------------------------ | :---: |
| LTC2943_STATUS_REG                                | 0x00  |
| LTC2943_CONTROL_REG                               | 0x01  |
| LTC2943_ACCUM_CHARGE_MSB_REG                      | 0x02  |
| LTC2943_ACCUM_CHARGE_LSB_REG                      | 0x03  |
| LTC2943_CHARGE_THRESH_HIGH_MSB_REG                | 0x04  |
| LTC2943_CHARGE_THRESH_HIGH_LSB_REG                | 0x05  |
| LTC2943_CHARGE_THRESH_LOW_MSB_REG                 | 0x06  |
| LTC2943_CHARGE_THRESH_LOW_LSB_REG                 | 0x07  |
| LTC2943_VOLTAGE_MSB_REG                           | 0x08  |
| LTC2943_VOLTAGE_LSB_REG                           | 0x09  |
| LTC2943_VOLTAGE_THRESH_HIGH_MSB_REG               | 0x0A  |
| LTC2943_VOLTAGE_THRESH_HIGH_LSB_REG               | 0x0B  |
| LTC2943_VOLTAGE_THRESH_LOW_MSB_REG                | 0x0C  |
| LTC2943_VOLTAGE_THRESH_LOW_LSB_REG                | 0x0D  |
| LTC2943_CURRENT_MSB_REG                           | 0x0E  |
| LTC2943_CURRENT_LSB_REG                           | 0x0F  |
| LTC2943_CURRENT_THRESH_HIGH_MSB_REG               | 0x10  |
| LTC2943_CURRENT_THRESH_HIGH_LSB_REG               | 0x11  |
| LTC2943_CURRENT_THRESH_LOW_MSB_REG                | 0x12  |
| LTC2943_CURRENT_THRESH_LOW_LSB_REG                | 0x13  |
| LTC2943_TEMPERATURE_MSB_REG                       | 0x14  |
| LTC2943_TEMPERATURE_LSB_REG                       | 0x15  |
| LTC2943_TEMPERATURE_THRESH_HIGH_REG               | 0x16  |
| LTC2943_TEMPERATURE_THRESH_LOW_REG                | 0x17  |
*/

/*! @name Registers
@{ */
// Registers
#define LTC2943_STATUS_REG                          0x00
#define LTC2943_CONTROL_REG                         0x01
#define LTC2943_ACCUM_CHARGE_MSB_REG                0x02
#define LTC2943_ACCUM_CHARGE_LSB_REG                0x03
#define LTC2943_CHARGE_THRESH_HIGH_MSB_REG          0x04
#define LTC2943_CHARGE_THRESH_HIGH_LSB_REG          0x05
#define LTC2943_CHARGE_THRESH_LOW_MSB_REG           0x06
#define LTC2943_CHARGE_THRESH_LOW_LSB_REG           0x07
#define LTC2943_VOLTAGE_MSB_REG                     0x08
#define LTC2943_VOLTAGE_LSB_REG                     0x09
#define LTC2943_VOLTAGE_THRESH_HIGH_MSB_REG         0x0A
#define LTC2943_VOLTAGE_THRESH_HIGH_LSB_REG         0x0B
#define LTC2943_VOLTAGE_THRESH_LOW_MSB_REG          0x0C
#define LTC2943_VOLTAGE_THRESH_LOW_LSB_REG          0x0D
#define LTC2943_CURRENT_MSB_REG                     0x0E
#define LTC2943_CURRENT_LSB_REG                     0x0F
#define LTC2943_CURRENT_THRESH_HIGH_MSB_REG         0x10
#define LTC2943_CURRENT_THRESH_HIGH_LSB_REG         0x11
#define LTC2943_CURRENT_THRESH_LOW_MSB_REG          0x12
#define LTC2943_CURRENT_THRESH_LOW_LSB_REG          0x13
#define LTC2943_TEMPERATURE_MSB_REG                 0x14
#define LTC2943_TEMPERATURE_LSB_REG                 0x15
#define LTC2943_TEMPERATURE_THRESH_HIGH_REG         0x16
#define LTC2943_TEMPERATURE_THRESH_LOW_REG          0x17
//! @}

/*!
| Command Codes                                 | Value     |
| :-------------------------------------------- | :-------: |
| LTC2943_AUTOMATIC_MODE                        | 0xC0      |
| LTC2943_SCAN_MODE                             | 0x80      |
| LTC2943_MANUAL_MODE                           | 0x40      |
| LTC2943_SLEEP_MODE                            | 0x00      |
| LTC2943_PRESCALAR_M_1                         | 0x00      |
| LTC2943_PRESCALAR_M_4                         | 0x08      |
| LTC2943_PRESCALAR_M_16                        | 0x10      |
| LTC2943_PRESCALAR_M_64                        | 0x18      |
| LTC2943_PRESCALAR_M_256                       | 0x20      |
| LTC2943_PRESCALAR_M_1024                      | 0x28      |
| LTC2943_PRESCALAR_M_4096                      | 0x30      |
| LTC2943_PRESCALAR_M_4096_2                    | 0x31      |
| LTC2943_ALERT_MODE                            | 0x04      |
| LTC2943_CHARGE_COMPLETE_MODE                  | 0x02      |
| LTC2943_DISABLE_ALCC_PIN                      | 0x00      |
| LTC2943_SHUTDOWN_MODE                         | 0x01      |
*/

/*! @name Command Codes
@{ */
// Command Codes
#define LTC2943_AUTOMATIC_MODE                  0xC0
#define LTC2943_SCAN_MODE                       0x80
#define LTC2943_MANUAL_MODE                     0x40
#define LTC2943_SLEEP_MODE                      0x00

#define LTC2943_PRESCALAR_M_1                   0x00
#define LTC2943_PRESCALAR_M_4                   0x08
#define LTC2943_PRESCALAR_M_16                  0x10
#define LTC2943_PRESCALAR_M_64                  0x18
#define LTC2943_PRESCALAR_M_256                 0x20
#define LTC2943_PRESCALAR_M_1024                0x28
#define LTC2943_PRESCALAR_M_4096                0x30
#define LTC2943_PRESCALAR_M_4096_2              0x31

#define LTC2943_ALERT_MODE                      0x04
#define LTC2943_CHARGE_COMPLETE_MODE            0x02

#define LTC2943_DISABLE_ALCC_PIN                0x00
#define LTC2943_SHUTDOWN_MODE                   0x01

//! @}

/*!
| Conversion Constants                              |  Value   |
| :------------------------------------------------ | :------: |
| LTC2943_CHARGE_lsb                                | 0.34  mAh|
| LTC2943_VOLTAGE_lsb                               | 1.44   mV|
| LTC2943_CURRENT_lsb                               |  29.3  uV|
| LTC2943_TEMPERATURE_lsb                           | 0.25    C|
| LTC2943_FULLSCALE_VOLTAGE                         |  23.6   V|
| LTC2943_FULLSCALE_CURRENT                         |  60    mV|
| LTC2943_FULLSCALE_TEMPERATURE                     | 510     K|

*/
/*! @name Conversion Constants
@{ */
const float LTC2943_CHARGE_lsb = 0.34E-3;
const float LTC2943_VOLTAGE_lsb = 1.44E-3;
const float LTC2943_CURRENT_lsb = 29.3E-6;
const float LTC2943_TEMPERATURE_lsb = 0.25;
const float LTC2943_FULLSCALE_VOLTAGE = 23.6;
const float LTC2943_FULLSCALE_CURRENT = 60E-3;
const float LTC2943_FULLSCALE_TEMPERATURE = 510;
//! @}

//! @}


//! Write an 8-bit code to the LTC2943.
//! @return The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
int8_t LTC2943_write(uint8_t i2c_address, //!< Register address for the LTC2943
                     uint8_t adc_command, //!< The "command byte" for the LTC2943
                     uint8_t code         //!< Value that will be written to the register.
                    );

//! Write a 16-bit code to the LTC2943.
//! @return The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
int8_t LTC2943_write_16_bits(uint8_t i2c_address, //!< Register address for the LTC2943
                             uint8_t adc_command, //!< The "command byte" for the LTC2943
                             uint16_t code        //!< Value that will be written to the register.
                            );


//! Reads an 8-bit adc_code from LTC2943
//! @return The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
int8_t LTC2943_read(uint8_t i2c_address, //!< Register address for the LTC2943
                    uint8_t adc_command, //!< The "command byte" for the LTC2943
                    uint8_t *adc_code    //!< Value that will be read from the register.
                   );


//! Reads a 16-bit adc_code from LTC2943
//! @return The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
int8_t LTC2943_read_16_bits(uint8_t i2c_address, //!< Register address for the LTC2943
                            uint8_t adc_command, //!< The "command byte" for the LTC2943
                            uint16_t *adc_code   //!< Value that will be read from the register.
                           );

int8_t LTC2943_ara_protocol(uint8_t i2c_alert_address,
							uint8_t *response
							);


//! Calculate the LTC2943 charge in Coulombs
//! @return Returns the Coulombs of charge in the ACR register.
float LTC2943_code_to_coulombs(uint16_t adc_code,        //!< The RAW ADC value
                               float resistor,         //!< The sense resistor value
                               uint16_t prescalar      //!< The prescalar value
                              );

//! Calculate the LTC2943 charge in mAh
//! @return Returns the Coulombs of charge in the ACR register.
float LTC2943_code_to_mAh(uint16_t adc_code,            //!< The RAW ADC value
                          float resistor,       //!< The sense resistor value
                          uint16_t prescalar    //!< The prescalar value
                         );

//! Calculate the LTC2943 SENSE+ voltage
//! @return Returns the SENSE+ Voltage in Volts
float LTC2943_code_to_voltage(uint16_t adc_code              //!< The RAW ADC value
                             );

//! Calculate the LTC2943 current with a sense resistor
//! @return Returns the current through the sense resisor
float LTC2943_code_to_current(uint16_t adc_code,                //!< The RAW ADC value
                              float resistor                   //!< The sense resistor value
                             );

//! Calculate the LTC2943 temperature
//! @return Returns the temperature in Kelvin
float LTC2943_code_to_kelvin_temperature(uint16_t adc_code           //!< The RAW ADC value
                                        );

//! Calculate the LTC2943 temperature
//! @return Returns the temperature in Celcius
float LTC2943_code_to_celcius_temperature(uint16_t adc_code          //!< The RAW ADC value
                                         );

#endif   LTC2943_H
