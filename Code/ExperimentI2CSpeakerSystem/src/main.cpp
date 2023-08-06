#include <Arduino.h>
#include <SPI.h>
#include <ADS1X15.h>


SPIClass *vspi = new SPIClass(VSPI);

//ADS1115 ADS(0x48);


void setup()
{

    Serial.begin(115200);
    vspi->begin();
    //ADS.begin();
    //ADS.setGain(0);
}

void loop()
{

}