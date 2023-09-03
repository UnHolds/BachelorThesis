#include <Arduino.h>
#include <SPI.h>
#include <ADS1X15.h>
#include "AudioData.h"

SPIClass *vspi = new SPIClass(VSPI);


long sampleRate = SAMPLE_RATE;

//ADS1115 ADS(0x48);
long timing = micros();
int cs = 17;
int i = 0;


#define MASK 0b0011111111110000
#define GAIN_1 0x2000
#define ACTIVE 0x1000

void setup()
{

    //Serial.begin(115200);
    vspi->begin();
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
}

void send(){
    vspi->beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(cs, LOW);
    uint16_t tdata = data[i] << 4;
    tdata |= ACTIVE;
    tdata &= MASK;
    vspi->transfer16(tdata);
    digitalWrite(cs, HIGH);
    vspi->endTransaction();
    i = (i + 1) % length;
}

void loop()
{
    if(micros() % (1000000 / sampleRate) == 0){
        send();
    }
}