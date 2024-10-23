#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_HUSB238.h"
#include "LTC2943.h"

// void setup() {
//     Wire.begin(2, 1);
//     Serial.begin(115200);
//     LTC2943_write(LTC2943_I2C_ADDRESS, LTC2943_CONTROL_REG, (LTC2943_AUTOMATIC_MODE | LTC2943_PRESCALAR_M_4096));
//     delay(1000);
// }

// uint16_t voltage;

// void loop() {
//     uint16_t charge;
//     uint16_t current;
//     uint16_t temperature;
//     uint16_t voltage;

//     LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_VOLTAGE_MSB_REG, &voltage);
//     Serial.print("VOLT: ");
//     Serial.println(LTC2943_code_to_voltage(voltage), 4);

//     LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_ACCUM_CHARGE_MSB_REG, &charge);
//     Serial.print("CHRG: ");
//     Serial.println(LTC2943_code_to_coulombs(charge, 0.01, 4096), 4);

//     LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_CURRENT_MSB_REG, &current);
//     Serial.print("CURR: ");
//     Serial.println(LTC2943_code_to_current(current, 0.01), 4);

//     LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_TEMPERATURE_MSB_REG, &temperature);
//     Serial.print("TEMP: ");
//     Serial.println(LTC2943_code_to_celcius_temperature(temperature), 4);

//     delay(1000);
// }

Adafruit_HUSB238 husb238;

#define BQ25713_ADDRESS 0x6B // I2C address of the BQ25713
#define VBUS_REG 0x27        // Register for VBUS voltage (as per the datasheet)

// Function to read a 16-bit register
uint16_t readRegister(uint8_t reg)
{
    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(reg); // Send register address
    Wire.endTransmission(false);

    Wire.requestFrom(BQ25713_ADDRESS, 1);
    return Wire.read(); // Combine high and low byte
}

void setup()
{
    Serial.begin(115200);
    Wire.begin(2, 1);
    while (!Serial)
        delay(10);

    // Initialize the HUSB238
    if (husb238.begin(HUSB238_I2CADDR_DEFAULT, &Wire))
    {
        Serial.println("HUSB238 initialized successfully.");
    }
    else
    {
        while (1)
            ;
    }
    // Change to that voltage
    husb238.selectPD((PD_SRC_15V));
    // Perform the actual PD voltage request!
    husb238.requestPD();
    delay(2000);

    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(0x01);
    Wire.write(0b00000000);
    Wire.endTransmission();

    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(0x03);
    Wire.write(0b00000100);
    Wire.endTransmission();

    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(0x3B);
    Wire.write(0b10100000);
    Wire.endTransmission();

    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(0x3A);
    Wire.write(0b11111111);
    Wire.endTransmission();
}

void debugPrint(String info, uint8_t data)
{
    Serial.print(info);
    Serial.print("0x");
    Serial.print(data, HEX);
    Serial.print(", 0b");
    Serial.print(data, BIN);
    Serial.print(", ");
    Serial.print(data, DEC);
    Serial.println();
    Serial.println();
}

void loop()
{
    delay(1000); // Short delay to stabilize

    Serial.println("\n\n");

    debugPrint("ChargerStatus 0x21:", readRegister(0x21));
    debugPrint("ChargerStatus 0x20:", readRegister(0x20));
    debugPrint("ChargeOption0 0x01:", readRegister(0x01));
    debugPrint("ChargeOption0 0x00:", readRegister(0x00));
    debugPrint("ADCOptions 0x3B:", readRegister(0x3B));
    debugPrint("ADCOptions 0x3A:", readRegister(0x3A));

    debugPrint("VSYS 0x26:", readRegister(0x26));
    debugPrint("ICHG 0x29:", readRegister(0x29));
    debugPrint("IDCHG 0x28:", readRegister(0x28));

    Serial.print("VBUS: ");
    Serial.println(readRegister(0x27) * 0.064);
    Serial.print("VSYS: ");
    Serial.println(readRegister(0x2D) * 0.064);
    Serial.print("VBAT: ");
    Serial.println(readRegister(0x2C) * 0.064);
}
