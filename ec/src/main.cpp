#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_HUSB238.h"
#include "LTC2943.h"

#define CHARGEOPTION0_MSB 0x01
#define CHARGEOPTION0_LSB 0x00

#define CHARGECURRENT_MSB 0x03
#define CHARGECURRENT_LSB 0x02

#define MAXCHARGEVOLTAGE_MSB 0x05
#define MAXCHARGEVOLTAGE_LSB 0x04

#define CHARGEOPTION1_MSB 0x31
#define CHARGEOPTION1_LSB 0x30

#define CHARGEOPTION2_MSB 0x33
#define CHARGEOPTION2_LSB 0x32

#define CHARGEOPTION3_MSB 0x35
#define CHARGEOPTION3_LSB 0x34

#define PROCHOTOPTION0_MSB 0x37
#define PROCHOTOPTION0_LSB 0x36

#define PROCHOTOPTION1_MSB 0x39
#define PROCHOTOPTION1_LSB 0x38

#define ADCOPTION_MSB 0x3B
#define ADCOPTION_LSB 0x3A

#define CHARGERSTATUS_MSB 0x21
#define CHARGERSTATUS_LSB 0x20

#define PROCHOTSTATUS_MSB 0x23
#define PROCHOTSTATUS_LSB 0x22

#define IIN_DPM_MSB 0x25
#define IIN_DPM_LSB 0x24

#define ADCVBUSPSYS_MSB 0x27
#define ADCVBUSPSYS_LSB 0x26

#define ADCIBAT_MSB 0x29
#define ADCIBAT_LSB 0x28

#define ADCIINCMPIN_MSB 0x2B
#define ADCIINCMPIN_LSB 0x2A

#define ADCVSYSVBAT_MSB 0x2D
#define ADCVSYSVBAT_LSB 0x2C

#define OTGVOLTAGE_MSB 0x07
#define OTGVOLTAGE_LSB 0x06

#define OTGCURRENT_MSB 0x09
#define OTGCURRENT_LSB 0x08

#define INPUTVOLTAGE_MSB 0x0B
#define INPUTVOLTAGE_LSB 0x0A

#define MINSYSTEMVOLTAGE_MSB 0x0D
#define MINSYSTEMVOLTAGE_LSB 0x0C

#define IIN_HOST_MSB 0x0F
#define IIN_HOST_LSB 0x0E

#define MANUFACTURERID 0x2E
#define DEVICEID 0x2F

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

// Function to write a 16-bit value to consecutive I2C registers
void writeRegister16(uint8_t lsbReg, uint16_t data)
{
    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(lsbReg + 1); // Write to MSB register first
    Wire.write((data >> 8) & 0xFF); // Write MSB
    Wire.endTransmission();

    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(lsbReg); // Write to LSB register
    Wire.write(data & 0xFF); // Write LSB
    Wire.endTransmission();
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
    husb238.selectPD((PD_SRC_20V));
    // Perform the actual PD voltage request!
    husb238.requestPD();
    delay(2000);

    // 0x020E to register 0x00

    writeRegister16(CHARGEOPTION0_LSB, 0x020E);

    // ADC configurations

    writeRegister16(ADCOPTION_LSB, 0xa0ff);

    // charging

    writeRegister16(CHARGECURRENT_LSB, 0x0800);

    // set input current to
    writeRegister16(IIN_HOST_LSB, 0x4000); // 3200mA input current
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
    debugPrint("ChargeCurrent 0x03:", readRegister(0x03));
    debugPrint("ChargeCurrent 0x02:", readRegister(0x02));
    debugPrint("ADCOptions 0x3B:", readRegister(0x3B));
    debugPrint("ADCOptions 0x3A:", readRegister(0x3A));
    debugPrint("IIN_HOST 0x0F:", readRegister(IIN_HOST_MSB));
    debugPrint("Input Current:", readRegister(ADCIINCMPIN_MSB));
    debugPrint("CMP Voltage:", readRegister(ADCIINCMPIN_LSB));

    debugPrint("PSYS 0x26:", readRegister(0x26));
    debugPrint("ICHG 0x29:", readRegister(0x29));
    debugPrint("IDCHG 0x28:", readRegister(0x28));

    Serial.print("VBUS: ");
    Serial.println(readRegister(0x27) * 0.064);
    Serial.print("VSYS: ");
    Serial.println(readRegister(0x2D) * 0.064);
    Serial.print("VBAT: ");
    Serial.println(readRegister(0x2C) * 0.064);

    writeRegister16(CHARGECURRENT_LSB, 0x0800);
}
