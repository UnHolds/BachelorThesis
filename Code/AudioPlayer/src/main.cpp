#include <Arduino.h>
#include "SPI.h"
#include <ESP32DMASPIMaster.h>
#include <FastLED.h>

#define BUFFER_SIZE 4096
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
CRGB leds[4];
bool change = true;
bool D5_on = false;
bool D7_on = false;
bool D8_on = false;
#define D5 32
#define D7 33
#define D8 02

//define CS pins
#define CS1 21
#define CS2 22
#define CS3 25
#define CS4 26
#define CS5 27

//channel
uint8_t** channel;
uint8_t* pinNums;

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

void setupChannelBuffer(){
        channel = (uint8_t**) malloc(5 * sizeof(uint8_t*));
        for(int i = 0; i < 5; i++){
            channel[i] = (uint8_t*) malloc(5 * sizeof(uint8_t));
        }
        pinNums = (uint8_t*) malloc(5 * sizeof(uint8_t));
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
    //pinMode(D7, OUTPUT);
    digitalWrite(D5, LOW);
    digitalWrite(D8, LOW);
    //digitalWrite(D7, LOW);


    FastLED.addLeds<WS2812B, D7, RGB>(leds, 4);

    //setup buttons
    pinMode(SW5, INPUT);
    pinMode(SW6, INPUT);

    //setup buffer
    setupChannelBuffer();

    change = true;


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

void update_audio_buffer_queue(){
    //queue new music data
    if(audio_index == BUFFER_SIZE){
        audio_index = 8;
        master.queue(tx_buffer, audio_buffer[current_buffer], BUFFER_SIZE);
        current_buffer++;
        current_buffer %= N_QUEUES;
        master.pop_first();
    }
}

void send2(uint8_t** pins, uint8_t* numPins, uint8_t numChannel){
    vspi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(vspi->pinSS(), LOW);

    for(int channel = 0; channel < numChannel; channel++){
        for(int pin = 0; pin < numPins[channel]; pin++){
            digitalWrite(pins[channel][pin], LOW);
        }

        uint16_t tdata = audio_buffer[current_buffer][audio_index] << 4;
        tdata |= ACTIVE;
        tdata &= MASK;
        vspi->transfer16(tdata);

        for(int pin = 0; pin < numPins[channel]; pin++){
            digitalWrite(pins[channel][pin], HIGH);
        }

        audio_index++;
        update_audio_buffer_queue();
    }

    digitalWrite(vspi->pinSS(), HIGH);
    vspi->endTransaction();
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
        change = true;
    }else if(!sw5_press){
        sw5_pressed = false;
    }

    if(sw6_press && !sw6_pressed){
        sw6_pressed = true;
        mode = (mode + 8 - 1) % 8;
        change = true;
    }else if(!sw6_press){
        sw6_pressed = false;
    }

    if(change){
        int c = random(1,8);
        int node = mode + 1;
        leds[0] = CRGB(random(256) * ((c >> 2) & 1) * ((node >> 0) & 1),random(256) * ((c >> 1) & 1)  * ((node >> 0) & 1),random(256) * ((c >> 0) & 1)  * ((node >> 0) & 1));
        leds[1] = CRGB(random(256) * ((c >> 2) & 1) * ((node >> 1) & 1),random(256) * ((c >> 1) & 1)  * ((node >> 1) & 1),random(256) * ((c >> 0) & 1)  * ((node >> 1) & 1));
        leds[2] = CRGB(random(256) * ((c >> 2) & 1) * ((node >> 2) & 1),random(256) * ((c >> 1) & 1)  * ((node >> 2) & 1),random(256) * ((c >> 0) & 1)  * ((node >> 2) & 1));
        leds[3] = CRGB(random(256) * ((c >> 2) & 1) * ((node >> 3) & 1),random(256) * ((c >> 1) & 1)  * ((node >> 3) & 1),random(256) * ((c >> 0) & 1)  * ((node >> 3) & 1));
    }
}

void handleLeds(){
    if(change){
        FastLED.show();
        change = false;
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

    if(mode == 4) {
        uint8_t pins1[] = {CS1};
        send(pins1 ,1);
    }

    if(mode == 5){
        channel[0][0] = CS1;
        channel[0][1] = CS2;
        channel[1][0] = CS3;
        channel[1][1] = CS4;
        //channel[0][4] = CS5;
        pinNums[0] = 2;
        pinNums[1] = 2;
        send2(channel, pinNums, 2);
    }

    if(mode == 6){
        channel[0][0] = CS1;
        channel[1][0] = CS2;
        channel[2][0] = CS3;
        channel[3][0] = CS4;
        channel[4][0] = CS5;

        pinNums[0] = 1;
        pinNums[1] = 1;
        pinNums[2] = 1;
        pinNums[3] = 1;
        pinNums[4] = 1;
        send2(channel, pinNums, 5);
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
        update_audio_buffer_queue();
    }
}
