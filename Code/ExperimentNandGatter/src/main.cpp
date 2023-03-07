#include <Arduino.h>
#include <SPI.h>

SPIClass *vspi = new SPIClass(VSPI);

#define MASK 0b0011111111110000
#define GAIN_1 0x2000
#define ACTIVE 0x1000

#define INPUT_DAC_CS 17

void setVoltage(uint8_t cs, uint8_t value)
{
    vspi->beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(cs, LOW);
    uint16_t data = value << 4;
    data |= ACTIVE;
    data &= MASK;
    vspi->transfer16(data);
    digitalWrite(cs, HIGH);
    vspi->endTransaction();
}

void setup()
{
    pinMode(INPUT_DAC_CS, OUTPUT);
    digitalWrite(INPUT_DAC_CS, HIGH);
    vspi->begin();

    setVoltage(INPUT_DAC_CS, 128);
}

void loop()
{
    // put your main code here, to run repeatedly:
}