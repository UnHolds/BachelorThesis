#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "ESP32DMASPISlave.h"

#define CS_PIN_SD_CARD 5
#define BUFFER_SIZE 1024
#define N_QUEUES 4

//Buttons
#define SW1 35
#define SW2 34
#define SW3 4
#define SW4 21

// LEDs
bool D1_on = false;
bool D1_change = false;
bool D2_on = false;
bool D2_change = false;
bool D3_on = false;
bool D3_change = false;
bool D4_on = false;
bool D4_change = false;
#define D1 27
#define D2 26
#define D3 25
#define D4 22

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
    if (!SD.begin(CS_PIN_SD_CARD, SPI, 1000000))
    {
        return;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        return;
    }
    audio_file = SD.open("/CantinaBand60.bwav", FILE_READ);

    if (!audio_file)
    {
        return;
    }

    audio_file.seek(0);
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
    pinMode(D4, OUTPUT);

    //pinMode(LED_BUILTIN, OUTPUT);
    //digitalWrite(LED_BUILTIN, LOW);
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
            D1_change = true;
        }
    }else{
        if(D1_on){
            D1_on = false;
            D1_change = true;
        }
    }

    if(sw2_press){
        if(D2_on == false){
            D2_on = true;
            D2_change = true;
        }
    }else{
        if(D2_on){
            D2_on = false;
            D2_change = true;
        }
    }

    if(sw3_press){
        if(D3_on == false){
            D3_on = true;
            D3_change = true;
        }
    }else{
        if(D3_on){
            D3_on = false;
            D3_change = true;
        }
    }

    if(sw4_press){
        if(D4_on == false){
            D4_on = true;
            D4_change = true;
        }
    }else{
        if(D4_on){
            D4_on = false;
            D4_change = true;
        }
    }
}

void handleLeds(){
    if(D1_change){
        digitalWrite(D1, D1_on ? HIGH : LOW);
        D1_change = false;
    }

   if(D2_change){
        digitalWrite(D2, D2_on ? HIGH : LOW);
        D2_change = false;
    }

    if(D3_change){
        digitalWrite(D3, D3_on ? HIGH : LOW);
        D3_change = false;
    }

    if(D4_change){
        digitalWrite(D4, D4_on ? HIGH : LOW);
        D4_change = false;
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
