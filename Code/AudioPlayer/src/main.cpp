#include <Arduino.h>
#include "SPI.h"
#include <ESP32DMASPIMaster.h>

#define BUFFER_SIZE 1024
#define N_QUEUES 4

SPIClass *vspi = new SPIClass(VSPI);
ESP32DMASPI::Master master;
long sampleRate = 22050;
long timing = micros();
int audio_index = 0;
int current_buffer = 0;

uint8_t *audio_buffer[N_QUEUES];
uint8_t *tx_buffer;

#define MASK 0b0011111111110000
#define GAIN_1 0x2000
#define ACTIVE 0x1000

// Buttons
#define SW5 34
bool sw5_pressed = false;
#define SW6 35
bool sw6_pressed = false;
int mode = 0;

// LEDs
bool D5_on = false;
bool D5_change = false;
bool D7_on = false;
bool D7_change = false;
bool D8_on = false;
bool D8_change = false;
#define D5 32
#define D7 33
#define D8 02

//define CS pins
#define CS1 21
#define CS2 22
#define CS3 25
#define CS4 26
#define CS5 27

void setup_buffers()
{
    tx_buffer = master.allocDMABuffer(BUFFER_SIZE);
    // create and fill buffer
    for (int i = 0; i < N_QUEUES; i++)
    {
        audio_buffer[i] = master.allocDMABuffer(BUFFER_SIZE);
    }

    // setup spi
    master.setDataMode(SPI_MODE0);
    master.setFrequency(4000000);
    master.setMaxTransferSize(BUFFER_SIZE);
    master.setQueueSize(N_QUEUES);
    master.begin(HSPI);

    for (int i = 0; i < N_QUEUES; i++)
    {
        master.queue(tx_buffer, audio_buffer[i], BUFFER_SIZE);
    }

    master.yield();
}

void setup()
{
    //setup the CS pins
    pinMode(CS1, OUTPUT);
    pinMode(CS2, OUTPUT);
    pinMode(CS3, OUTPUT);
    pinMode(CS4, OUTPUT);
    pinMode(CS5, OUTPUT);
    digitalWrite(CS1, HIGH);
    digitalWrite(CS2, HIGH);
    digitalWrite(CS3, HIGH);
    digitalWrite(CS4, HIGH);
    digitalWrite(CS5, HIGH);


    //setup diodes
    pinMode(D5, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(D7, OUTPUT);
    digitalWrite(D5, LOW);
    digitalWrite(D8, LOW);
    digitalWrite(D7, LOW);

    //setup buttons
    pinMode(SW5, INPUT);
    pinMode(SW6, INPUT);


    //Serial.begin(115200);
    pinMode(VSPI_IOMUX_PIN_NUM_CS, OUTPUT);
    vspi->begin(VSPI_IOMUX_PIN_NUM_CLK, VSPI_IOMUX_PIN_NUM_MISO, VSPI_IOMUX_PIN_NUM_MOSI, VSPI_IOMUX_PIN_NUM_CS);
    digitalWrite(vspi->pinSS(), HIGH);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    delay(5000);
    setup_buffers();
    delay(1000);

}

void send(const uint8_t pins[], int numPins)
{
    vspi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    for(int i = 0; i < numPins; i++){
        digitalWrite(pins[i], LOW);
    }
    digitalWrite(vspi->pinSS(), LOW);
    uint16_t tdata = audio_buffer[current_buffer][audio_index] << 4;
    tdata |= ACTIVE;
    tdata &= MASK;
    vspi->transfer16(tdata);
    for(int i = 0; i < numPins; i++){
        digitalWrite(pins[i], HIGH);
    }
    digitalWrite(vspi->pinSS(), HIGH);
    vspi->endTransaction();
    audio_index++;
}

void handleButtons() {

    int sw5_press = digitalRead(SW5);
    int sw6_press = digitalRead(SW6);

    if(sw5_press && !sw5_pressed){
        sw5_pressed = true;
        mode = (mode + 1) % 8;
    }else if(!sw5_press){
        sw5_pressed = false;
    }

    if(sw6_press && !sw6_pressed){
        sw6_pressed = true;
        mode = (mode + 8 - 1) % 8;
    }else if(!sw6_press){
        sw6_pressed = false;
    }

    if(mode & 0b1){
        if(!D5_on){
            D5_on = true;
            D5_change = true;
        }
    }else{
         if(D5_on){
            D5_on = false;
            D5_change = true;
        }
    }

    if(mode & 0b10){
        if(!D7_on){
            D7_on = true;
            D7_change = true;
        }
    }else{
         if(D7_on){
            D7_on = false;
            D7_change = true;
        }
    }

    if(mode & 0b100){
        if(!D8_on){
            D8_on = true;
            D8_change = true;
        }
    }else{
         if(D8_on){
            D8_on = false;
            D8_change = true;
        }
    }
}

void handleLeds(){
    if(D5_change){
        digitalWrite(D5, D5_on ? HIGH : LOW);
        D5_change = false;
    }

    if(D8_change){
        digitalWrite(D8, D8_on ? HIGH : LOW);
        D8_change = false;
    }

    if(D7_change){
        digitalWrite(D7, D7_on ? HIGH : LOW);
        D7_change = false;
    }
}

void handleSend(){
    if(mode == 0){
        uint8_t pins[] = {CS1, CS2, CS3, CS4, CS5};
        send(pins ,5);
    }

    if(mode == 1){
        uint8_t pins[] = {};
        send(pins ,0);
    }

    if(mode == 2){
        uint8_t pins[] = {CS1, CS3, CS5};
        send(pins ,3);
    }

    if(mode == 3){
        uint8_t pins1[] = {CS1, CS2};
        send(pins1 ,2);
        uint8_t pins2[] = {CS3, CS4};
        send(pins2 ,2);
    }

}

void loop()
{

    long currentTime = micros();
    if ((currentTime - timing) >= (1000000 / sampleRate))
    {
        timing = currentTime;
        handleSend();
        handleButtons();
        handleLeds();

        //queue new music data
        if(audio_index == BUFFER_SIZE){
            audio_index = 8;
            master.queue(tx_buffer, audio_buffer[current_buffer], BUFFER_SIZE);
            current_buffer++;
            current_buffer %= N_QUEUES;
            master.pop_first();
        }
    }
}
