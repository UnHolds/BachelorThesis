#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"


#define CS_PIN_SD_CARD 16
#define CS_PIN_DAC 17
#define BUFFER_SIZE 1000

SPIClass *vspi = new SPIClass(VSPI);

long sampleRate = 22050;
File audio_file;
long timing = micros();
int audio_index = 0;
int remaining_data = 0;
uint8_t audio_buffer[BUFFER_SIZE];

#define MASK 0b0011111111110000
#define GAIN_1 0x2000
#define ACTIVE 0x1000

void get_data(){
    if(audio_file.available() == false){
      audio_file.seek(0);
    }
    remaining_data = audio_file.available();
    audio_file.read(audio_buffer, sizeof(audio_buffer));
    audio_index = 0;
}

void setup() {

  vspi->begin();
  pinMode(CS_PIN_DAC, OUTPUT);
  digitalWrite(CS_PIN_DAC, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  if(!SD.begin(CS_PIN_SD_CARD, SPI, 16000000)){
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    return;
  }
  audio_file = SD.open("/CantinaBand60.bwav", FILE_READ);

  if(!audio_file){
    return;
  }

  delay(100);
  audio_file.seek(0);
}



void send(){
    vspi->beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(CS_PIN_DAC, LOW);
    uint16_t tdata = audio_buffer[audio_index] << 4;
    tdata |= ACTIVE;
    tdata &= MASK;
    vspi->transfer16(tdata);
    digitalWrite(CS_PIN_DAC, HIGH);
    vspi->endTransaction();
    audio_index++;
}

long wait;

void loop() {
  long currentTime = micros();
  if((currentTime - timing) >= (1000000 / sampleRate)){
      timing = currentTime;
      if(audio_index == remaining_data || audio_index == BUFFER_SIZE){
        get_data();
      }
      send();
  }
}
