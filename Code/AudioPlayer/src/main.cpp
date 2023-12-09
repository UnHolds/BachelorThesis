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
#define SW6 35

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
    pinMode(D5, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(D7, OUTPUT);
    digitalWrite(D5, LOW);
    digitalWrite(D8, LOW);
    digitalWrite(D7, LOW);

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

void send()
{
    vspi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(vspi->pinSS(), LOW);
    uint16_t tdata = audio_buffer[current_buffer][audio_index] << 4;
    tdata |= ACTIVE;
    tdata &= MASK;
    vspi->transfer16(tdata);
    digitalWrite(vspi->pinSS(), HIGH);
    vspi->endTransaction();
    audio_index++;
}

void handleButtons() {

    int sw5_press = digitalRead(SW5);
    int sw6_press = digitalRead(SW6);

    if(sw5_press && sw6_press == 0){
        if(D5_on == false) {
            D5_on = true;
            D5_change = true;
        }
    }else{
        if(D5_on == true) {
            D5_on = false;
            D5_change = true;
        }
    }

    if(sw5_press == 0 && sw6_press){
        if(D7_on == false) {
            D7_on = true;
            D7_change = true;
        }
    }else{
        if(D7_on == true) {
            D7_on = false;
            D7_change = true;
        }
    }

    if(sw5_press && sw6_press){
        if(D8_on == false) {
            D8_on = true;
            D8_change = true;
        }
    }else{
        if(D8_on == true) {
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

void loop()
{

    long currentTime = micros();
    if ((currentTime - timing) >= (1000000 / sampleRate))
    {
        timing = currentTime;
        send();
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
