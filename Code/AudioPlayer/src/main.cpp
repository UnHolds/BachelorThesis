#include <Arduino.h>
#include "SPI.h"
#include <ESP32DMASPIMaster.h>

#define BUFFER_SIZE 1024
#define N_QUEUES 2

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
    vspi->beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(vspi->pinSS(), LOW);
    uint16_t tdata = audio_buffer[current_buffer][audio_index] << 4;
    tdata |= ACTIVE;
    tdata &= MASK;
    vspi->transfer16(tdata);
    digitalWrite(vspi->pinSS(), HIGH);
    vspi->endTransaction();
    audio_index++;
}

void loop()
{
    long currentTime = micros();
    if ((currentTime - timing) >= (1000000 / sampleRate))
    {
        timing = currentTime;
        send();

        //queue new music data
        if(audio_index == BUFFER_SIZE){
            audio_index = 1;
            master.queue(tx_buffer, audio_buffer[current_buffer], BUFFER_SIZE);
            current_buffer++;
            current_buffer %= N_QUEUES;
            master.pop_first();
        }
    }
}
