#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "ESP32DMASPISlave.h"
#include <FastLED.h>

#define CS_PIN_SD_CARD 5
#define BUFFER_SIZE 4096
#define N_QUEUES 4

//Buttons
#define SW1 35
#define SW2 34
#define SW3 4
#define SW4 21

// LEDs
bool change = false;
bool D1_on = false;
bool D2_on = false;
bool D3_on = false;
bool D4_on = false;
#define D1 27
#define D2 26
#define D3 25
#define D4 22
CRGB leds[4];

File audio_file;
ESP32DMASPI::Slave slave;

uint8_t *audio_buffer[N_QUEUES];
uint8_t *rx_buffer;
int next_buffer = 0;

void fill_buffer(int queue_id)
{
    digitalWrite(LED_BUILTIN, HIGH);
    if (audio_file.available() <= 0)
    {
        audio_file.seek(0);
    }

    for(int i = 0; i < 8; i++){
        audio_buffer[queue_id][i] = 0;
    }

    int available_data = audio_file.available();
    int bytes_to_read = BUFFER_SIZE - 8;
    int remaining_data = 0;
    if (available_data < BUFFER_SIZE - 8)
    {
        bytes_to_read = available_data;
        remaining_data = BUFFER_SIZE - 8 - available_data;
    }

    audio_file.read(audio_buffer[queue_id] + 8, bytes_to_read);

    if (remaining_data > 0)
    {
        audio_file.seek(0);
        audio_file.read(audio_buffer[queue_id] + bytes_to_read + 8, remaining_data);
    }
    digitalWrite(LED_BUILTIN, LOW);
}

void setAudioFile(const char* filename){
    File tmp_audio_file = SD.open(filename, FILE_READ);

    if (!tmp_audio_file)
    {
        return;
    }

    tmp_audio_file.seek(0);
    audio_file = tmp_audio_file;
}

void setup_buffers()
{
    rx_buffer = slave.allocDMABuffer(BUFFER_SIZE);

    // create and fill buffer
    for (int i = 0; i < N_QUEUES; i++)
    {
        audio_buffer[i] = slave.allocDMABuffer(BUFFER_SIZE);
        fill_buffer(i);

    }

    // setup spi
    slave.setDataMode(SPI_MODE0);
    slave.setMaxTransferSize(BUFFER_SIZE);
    slave.setQueueSize(N_QUEUES);
    slave.begin(HSPI);

    for(int i = 0; i < N_QUEUES; i++){
       slave.queue(rx_buffer, audio_buffer[i], BUFFER_SIZE);
    }
}

void setup_sd_card()
{
    if (!SD.begin(CS_PIN_SD_CARD, SPI, 2000000))
    {
        return;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        return;
    }

    leds[0] = CRGB(255,0,0);
    leds[1] = CRGB(0,0,0);
    leds[2] = CRGB(0,0,0);
    leds[3] = CRGB(0,0,0);
    change = true;
    D1_on = true;
    setAudioFile("/CacciatoreDellaNotte.bwav");
}



void setup()
{
    //Buttons
    pinMode(SW1, INPUT);
    pinMode(SW2, INPUT);
    pinMode(SW3, INPUT);
    pinMode(SW4, INPUT);

    // LEDs
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    //pinMode(D4, OUTPUT);
    FastLED.addLeds<WS2812B, D4, RGB>(leds, 4);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    setup_sd_card();
    setup_buffers();
    delay(1000);
}

void handleButtons() {

    int sw1_press = digitalRead(SW1);
    int sw2_press = digitalRead(SW2);
    int sw3_press = digitalRead(SW3);
    int sw4_press = digitalRead(SW4);

    if(sw1_press){
        if(D1_on == false){
            D1_on = true;
            D2_on = false;
            D3_on = false;
            D4_on = false;
            change = true;
            int c = random(1,8);
            leds[0] = CRGB(random(256) * ((c >> 2) & 1),random(256) * ((c >> 1) & 1),random(256) * ((c >> 0) & 1));
            leds[1] = CRGB(0,0,0);
            leds[2] = CRGB(0,0,0);
            leds[3] = CRGB(0,0,0);
            setAudioFile("/CacciatoreDellaNotte.bwav");
        }
    } else if(sw2_press){
        if(D2_on == false){
            D2_on = true;
            D1_on = false;
            D3_on = false;
            D4_on = false;
            change = true;
            int c = random(1,8);
            leds[0] = CRGB(0,0,0);
            leds[1] = CRGB(random(256) * ((c >> 2) & 1),random(256) * ((c >> 1) & 1),random(256) * ((c >> 0) & 1));
            leds[2] = CRGB(0,0,0);
            leds[3] = CRGB(0,0,0);
            setAudioFile("/CantinaBand.bwav");
        }
    } else if(sw3_press){
        if(D3_on == false){
            D3_on = true;
            D1_on = false;
            D2_on = false;
            D4_on = false;
            change = true;
            int c = random(1,8);
            leds[0] = CRGB(0,0,0);
            leds[1] = CRGB(0,0,0);
            leds[2] = CRGB(random(256) * ((c >> 2) & 1),random(256) * ((c >> 1) & 1),random(256) * ((c >> 0) & 1));
            leds[3] = CRGB(0,0,0);
            setAudioFile("/merged.bwav");
        }

    } else if(sw4_press){
        if(D4_on == false){
            D4_on = true;
            D1_on = false;
            D2_on = false;
            D3_on = false;
            change = true;
            int c = random(1,8);
            leds[0] = CRGB(0,0,0);
            leds[1] = CRGB(0,0,0);
            leds[2] = CRGB(0,0,0);
            leds[3] = CRGB(random(256) * ((c >> 2) & 1),random(256) * ((c >> 1) & 1),random(256) * ((c >> 0) & 1));
            setAudioFile("/Merge5.bwav");
        }

    }
}

void handleLeds(){
    if(change){
        FastLED.show();
        change = false;
    }
}

void loop()
{

    if(slave.available() > 0){
        slave.pop();
    }

    handleButtons();
    handleLeds();

    if(slave.remained() >= N_QUEUES){
        return;
    }

    fill_buffer(next_buffer);
    slave.queue(rx_buffer, audio_buffer[next_buffer], BUFFER_SIZE);
    delay(10);

    //fill up the next buffer
    next_buffer++;
    next_buffer %= N_QUEUES;
}
