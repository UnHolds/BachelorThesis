#include <Arduino.h>
#include <SPI.h>
#include <ADS1X15.h>


SPIClass *vspi = new SPIClass(VSPI);

#define MASK 0b0011111111110000
#define GAIN_1 0x2000
#define ACTIVE 0x1000

#define INPUT_DAC_CS 17
#define VCC_DAC_CS 16

#define ADC_4_OUTPUT_PIN -1
#define ADC_4_VCC_PIN -1
#define ADC_4_INPUT_PIN -1

#define MAX_VCC_DAC_VALUE -1
#define MIN_VCC_DAC_VALUE -1

ADS1115 ADS(0x48);
char buffer[248];

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

double measureVoltage(uint8_t pin){
    return ADS.readADC(pin) * 0.0001875;
}



void setup()
{

    Serial.begin(115200);

    pinMode(INPUT_DAC_CS, OUTPUT);
    digitalWrite(INPUT_DAC_CS, HIGH);
    pinMode(VCC_DAC_CS, OUTPUT);
    digitalWrite(VCC_DAC_CS, HIGH);
    vspi->begin();

    ADS.begin();
    ADS.setGain(0);

    setVoltage(INPUT_DAC_CS, 128);
    setVoltage(VCC_DAC_CS, 255);
}

void reportMeasurement(int vcc, int input){
    double vOut = measureVoltage(ADC_4_OUTPUT_PIN);
    double vIn = measureVoltage(ADC_4_INPUT_PIN);
    double vVcc = measureVoltage(ADC_4_VCC_PIN);

    sprintf(buffer, "%d;%lf;%d;%lf;%lf", vcc, vVcc, input, vIn, vOut);
    Serial.println(buffer);
}

void runInputRamp(int vccS){
    for(int i = 0; i < 256; i++){
        setVoltage(INPUT_DAC_CS, i);
        delay(100);
        reportMeasurement(vccS, i);
    }
}

void runVccRamp(){
    for(int i = MAX_VCC_DAC_VALUE; i >= MIN_VCC_DAC_VALUE; i--){
        setVoltage(VCC_DAC_CS, i);
        delay(100);
        runInputRamp(i);
    }
}

void loop()
{
    String data = Serial.readStringUntil('\n');

    if(data.equals("start")){
        runVccRamp();
    }
}