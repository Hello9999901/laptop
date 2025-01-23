#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_HUSB238.h"
#include "LTC2943.h"
#include "BQ25713.h"
#include <EEPROM.h>

#define LED1 12
#define LED2 13
#define LED3 14
#define LED4 15
#define LED5 16

#define BQ25713_IBAT 11
#define BQ25713_IADPT 10
#define BQ77915_CBI 9
#define BQ77915_PRES 8
#define BQ25713_CMPOUT 7
#define BQ25713_EN_OTG 6
#define BQ25713_CHRG_OK 5
#define BQ25713_PROCHOT_N 4
#define LTC2943_ALCC 3

Adafruit_HUSB238 husb238;

uint16_t charge;
uint16_t current;
uint16_t temperature;
uint16_t voltage;

// Function to read a 16-bit register
uint16_t readRegister(uint8_t reg)
{
    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(reg); // Send register address
    Wire.endTransmission(false);

    Wire.requestFrom(BQ25713_ADDRESS, 1);
    return Wire.read(); // Combine high and low byte
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

// Function to write a 16-bit value to consecutive I2C registers
void writeRegister16(uint8_t lsbReg, uint16_t data)
{
    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(lsbReg + 1);         // Write to MSB register first
    Wire.write((data >> 8) & 0xFF); // Write MSB
    Wire.endTransmission();

    Wire.beginTransmission(BQ25713_ADDRESS);
    Wire.write(lsbReg);      // Write to LSB register
    Wire.write(data & 0xFF); // Write LSB
    Wire.endTransmission();
}

void chargingInit()
{
    // 0x020E to register 0x00
    writeRegister16(CHARGEOPTION0_LSB, 0x820E);

    // charging
    writeRegister16(CHARGECURRENT_LSB, 0x0800);
}

void dimLED(int batteryPercent)
{
    static int brightness = 0;
    static int fadeAmount = 5;
    static unsigned long lastDimTime = 0;

    unsigned long currentTime = micros(); // Use micros() for more precise timing

    // Check if enough time has passed since last dimming
    if (currentTime - lastDimTime >= 30000)
    { // 20ms = 20,000 microseconds
        lastDimTime = currentTime;

        // Change the brightness
        brightness += fadeAmount;

        // Reverse the fade direction when we reach the limits
        if (brightness <= 0 || brightness >= 255)
        {
            fadeAmount = -fadeAmount;
        }

        // Set the LED brightness
        if (batteryPercent > 90) {
            analogWrite(LED3, brightness);
            analogWrite(LED4, brightness);
            analogWrite(LED5, brightness);
        }
        else if (batteryPercent > 60) {
            analogWrite(LED3, brightness);
            analogWrite(LED4, brightness);
            digitalWrite(LED5, LOW);
        }
        else if (batteryPercent > 30) {
            analogWrite(LED3, brightness);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    Wire.begin(2, 1);
    EEPROM.begin(512); // half kb simulated flash

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);

    LTC2943_write(LTC2943_I2C_ADDRESS, LTC2943_CONTROL_REG, (LTC2943_AUTOMATIC_MODE | LTC2943_PRESCALAR_M_4096));

    chargingInit();

    delay(1000);

    Serial.println("EEPROM Stored Value: ");
    Serial.println(EEPROM.read(0));
    uint16_t storedCharge = (EEPROM.read(0) << 8) | EEPROM.read(1);
    Serial.println(storedCharge);

    LTC2943_write_16_bits(LTC2943_I2C_ADDRESS, LTC2943_ACCUM_CHARGE_MSB_REG, storedCharge);
}

bool vbusConnected = false;
int previousTime = 0;
int batteryPercent = 100;
bool charging = false;

void loop()
{
    if (millis() - previousTime >= 1000)
    {
        previousTime = millis();
        Serial.println(F("----------------------------------------------"));

        Wire.beginTransmission(HUSB238_I2CADDR_DEFAULT);
        int transmissionResult = Wire.endTransmission();

        Serial.print("HUSB Connected: ");
        Serial.println(transmissionResult == 0 ? "true" : "false");

        if (transmissionResult == 0 && !vbusConnected)
        {
            delay(500);

            husb238.begin(HUSB238_I2CADDR_DEFAULT, &Wire);
            husb238.selectPD(PD_SRC_20V);
            husb238.requestPD();

            Serial.println("REQUESTED 20V");
            Serial.println(husb238.isVoltageDetected(PD_SRC_20V));

            delay(100);
            chargingInit();

            vbusConnected = true;
        }
        else if (vbusConnected && transmissionResult != 0)
        {
            vbusConnected = false;
        }

        Serial.print("VBUS Connected: ");
        Serial.println(vbusConnected);

        Wire.beginTransmission(BQ25713_ADDRESS);
        transmissionResult = Wire.endTransmission();

        if (transmissionResult == 0)
        {
            Serial.print("VBUS: ");
            Serial.println(readRegister(0x27) * 0.064);
            Serial.print("VSYS: ");
            Serial.println(readRegister(0x2D) * 0.064);
            Serial.print("VBAT: ");
            Serial.println(readRegister(0x2C) * 0.064);

            Serial.print("CHARGING: ");
            if (readRegister(0x29) > 0)
            {
                Serial.println("YES");
                charging = true;
            }
            else
            {
                Serial.println("NO");
                charging = false;
            }
        }
        else
        {
            Serial.println("BQ25713 NOT CONNECTED");
        }

        // debugPrint("ChargerStatus 0x21:", readRegister(0x21));
        // debugPrint("ChargerStatus 0x20:", readRegister(0x20));
        // debugPrint("ChargeOption0 0x01:", readRegister(0x01));
        // debugPrint("ChargeOption0 0x00:", readRegister(0x00));
        // debugPrint("ChargeCurrent 0x03:", readRegister(0x03));
        // debugPrint("ChargeCurrent 0x02:", readRegister(0x02));
        // debugPrint("ADCOptions 0x3B:", readRegister(0x3B));
        // debugPrint("ADCOptions 0x3A:", readRegister(0x3A));
        // debugPrint("IIN_HOST 0x0F:", readRegister(IIN_HOST_MSB));
        // debugPrint("Input Current:", readRegister(ADCIINCMPIN_MSB));
        // debugPrint("CMP Voltage:", readRegister(ADCIINCMPIN_LSB));

        // debugPrint("PSYS 0x26:", readRegister(0x26));
        // debugPrint("ICHG 0x29:", readRegister(0x29));
        // debugPrint("IDCHG 0x28:", readRegister(0x28));

        LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_VOLTAGE_MSB_REG, &voltage);
        Serial.print("VOLT: ");
        Serial.println(LTC2943_code_to_voltage(voltage), 4);

        LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_ACCUM_CHARGE_MSB_REG, &charge);
        Serial.print("CHRG mAh: ");
        Serial.println(LTC2943_code_to_mAh(charge, 0.01, 4096), 4);

        if (charge > 0x9C4)
        {
            charge = 0x9C4;
            LTC2943_write_16_bits(LTC2943_I2C_ADDRESS, LTC2943_ACCUM_CHARGE_MSB_REG, charge);
        }

        EEPROM.write(0, (charge >> 8) & 0xFF); // Write high byte
        EEPROM.write(1, charge & 0xFF);        // Write low byte
        EEPROM.commit();

        LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_CURRENT_MSB_REG, &current);
        Serial.print("CURR: ");
        Serial.println(LTC2943_code_to_current(current, 0.01), 4);

        LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_TEMPERATURE_MSB_REG, &temperature);
        Serial.print("TEMP: ");
        Serial.println(LTC2943_code_to_celcius_temperature(temperature), 4);

        Serial.print("BATTERY PERCENT: ");
        batteryPercent = (LTC2943_code_to_mAh(charge, 0.01, 4096) * 100 / (float)4250);
        Serial.println(batteryPercent);

        if (LTC2943_code_to_celcius_temperature(temperature) >= 60)
        {
            // thermal shutdown
            writeRegister16(CHARGECURRENT_LSB, 0x0000);
        }
        else
        {
            // charging
            writeRegister16(CHARGECURRENT_LSB, 0x0800);
        }
    }

    if (charging) {
        dimLED(batteryPercent);
    }
    else {
        if (batteryPercent > 90) {
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(LED5, HIGH);
        }
        else if (batteryPercent > 60) {
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(LED5, LOW);
        }
        else if (batteryPercent > 30) {
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, LOW);
            digitalWrite(LED5, LOW);
        }
    }
}
