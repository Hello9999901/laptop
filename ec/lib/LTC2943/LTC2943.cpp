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

#include <Arduino.h>
#include <Wire.h>
#include "LTC2943.h"


// Write an 8-bit code to the LTC2943.
int8_t LTC2943_write(uint8_t i2c_address, uint8_t adc_command, uint8_t code)
// The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
{
  int32_t ack;

      Wire.beginTransmission(i2c_address);
      Wire.write(adc_command);
      Wire.write(code);
      ack = Wire.endTransmission();
      return(ack);
}


// Write a 16-bit code to the LTC2943.
int8_t LTC2943_write_16_bits(uint8_t i2c_address, uint8_t adc_command, uint16_t code)
// The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
{
  int8_t ack;
    union
  {
    uint8_t b[2];
    uint16_t w;
  } data;
  data.w = code;
      Wire.beginTransmission(i2c_address);
      Wire.write(adc_command);
      Wire.write(data.b[1]);
	    Wire.write(data.b[0]);
  ack = Wire.endTransmission();
  return(ack);
}

// Reads an 8-bit adc_code from LTC2943
int8_t LTC2943_read(uint8_t i2c_address, uint8_t adc_command, uint8_t *adc_code)
// The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
{
  int32_t ack;
      Wire.beginTransmission(i2c_address);
      Wire.write(adc_command);
		  Wire.endTransmission(false);
  ack=Wire.requestFrom(i2c_address,1,false);
		*adc_code=Wire.read();
//      ack=Wire.endTransmission();
  return(ack);
}


// Reads a 16-bit adc_code from LTC2943
int8_t LTC2943_read_16_bits(uint8_t i2c_address, uint8_t adc_command, uint16_t *adc_code)
// The function returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
{
    Wire.beginTransmission(i2c_address);
    Wire.write(adc_command); // Send register address
    Wire.endTransmission(false);

    Wire.requestFrom(i2c_address, 2); // Request 2 bytes from the register
    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();
    *adc_code = (highByte << 8) | lowByte; // Combine high and low byte
    return 0;
}

// Reads alert protocol 8-bit response from LTC2943
int8_t LTC2943_ara_protocol(uint8_t i2c_alert_address, uint8_t *response)
{

	  int32_t ack;
      Wire.beginTransmission(i2c_alert_address);
		  Wire.endTransmission(false);
    ack= Wire.requestFrom(i2c_alert_address,1,false);
		  *response=Wire.read();
      //ack=Wire.endTransmission();
  return(ack);

}

float LTC2943_code_to_coulombs(uint16_t adc_code, float resistor, uint16_t prescalar)
// The function converts the 16-bit RAW adc_code to Coulombs
{
  float coulomb_charge;
  coulomb_charge =  1000*(float)(adc_code*LTC2943_CHARGE_lsb*prescalar*50E-3)/(resistor*4096);
  coulomb_charge = coulomb_charge*3.6f;
  return(coulomb_charge);
}

float LTC2943_code_to_mAh(uint16_t adc_code, float resistor, uint16_t prescalar )
// The function converts the 16-bit RAW adc_code to mAh
{
  float mAh_charge;
  mAh_charge = 1000*(float)(adc_code*LTC2943_CHARGE_lsb*prescalar*50E-3)/(resistor*4096);
  return(mAh_charge);
}

float LTC2943_code_to_voltage(uint16_t adc_code)
// The function converts the 16-bit RAW adc_code to Volts
{
  float voltage;
  voltage = ((float)adc_code/(65535))*LTC2943_FULLSCALE_VOLTAGE;
  return(voltage);
}

float LTC2943_code_to_current(uint16_t adc_code, float resistor)
// The function converts the 16-bit RAW adc_code to Amperes
{
  float current;
  current = (((float)adc_code-32767)/(32767))*((float)(LTC2943_FULLSCALE_CURRENT)/resistor);
  return(current);
}

float LTC2943_code_to_kelvin_temperature(uint16_t adc_code)
// The function converts the 16-bit RAW adc_code to Kelvin
{
  float temperature;
  temperature = adc_code*((float)(LTC2943_FULLSCALE_TEMPERATURE)/65535);
  return(temperature);
}

float LTC2943_code_to_celcius_temperature(uint16_t adc_code)
// The function converts the 16-bit RAW adc_code to Celcius
{
  float temperature;
  temperature = adc_code*((float)(LTC2943_FULLSCALE_TEMPERATURE)/65535) - 273.15;
  return(temperature);
}

// Used to set and clear bits in a control register.  bits_to_set will be bitwise OR'd with the register.
// bits_to_clear will be inverted and bitwise AND'd with the register so that every location with a 1 will result in a 0 in the register.
int8_t LTC2943_register_set_clear_bits(uint8_t i2c_address, uint8_t register_address, uint8_t bits_to_set, uint8_t bits_to_clear)
{
  uint8_t register_data;
  int8_t ack = 0;

  ack |= LTC2943_read(i2c_address, register_address, &register_data);
  register_data = register_data & (~bits_to_clear);
  register_data = register_data | bits_to_set;
  ack |= LTC2943_write(i2c_address, register_address, register_data);
  return(ack);
}
