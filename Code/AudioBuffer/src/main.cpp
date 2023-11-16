#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "ESP32DMASPISlave.h"

#define CS_PIN_SD_CARD 5
#define BUFFER_SIZE 1024
#define N_QUEUES 4

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
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    setup_sd_card();
    setup_buffers();
    delay(1000);
}

void loop()
{
    
    if(slave.available() > 0){
        slave.pop();
    }

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
