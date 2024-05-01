#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "ESP32DMASPISlave.h"
#include <FastLED.h>
#include <vector>

#define CS_PIN_SD_CARD 5
#define BUFFER_SIZE 4096
#define N_QUEUES 4

//Buttons
#define MISC_BUTTON 35
#define NEXT_SONG_BUTTON 34
#define PLAY_PAUSE_BUTTON 4
#define PREVIOUS_SONG_BUTTON 21

#define COM_C1 32
#define COM_C2 25
#define COM_C3 26
#define COM_C4 27

#define WS2812_PIN 22

/*
##### MODE ######
0 = OFF
1 = Single ALL
2 = 5 Different
*/

#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
bool led_change = false;
File audio_file;
ESP32DMASPI::Slave slave;

uint8_t *audio_buffer[N_QUEUES];
uint8_t *rx_buffer;
int next_buffer = 0;

int mode = 0;
bool mode_change = true;
std::vector<String> songs;
int num_songs = 0;
int current_song = 0;
bool play = false;

void fill_buffer(int queue_id)
{
    if (audio_file.available() <= 0)
    {
        audio_file.seek(0);
    }

    for(int i = 0; i < 8; i++){
        audio_buffer[queue_id][i] = 0;
    }

    int available_data = audio_file.available();
    int bytes_to_read = BUFFER_SIZE - 8;

    //handle pause
    if(play == false){
        for(int i = 0; i < bytes_to_read; i++){
            audio_buffer[queue_id][i + 8] = 0;
        }
        return;
    }


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
}

void setAudioFile(String filename){
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

void set_leds_black(){
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB(0,0,0);
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

    File root = SD.open("/");
    File file = root.openNextFile();
    num_songs = 0;
    while(file){
        String name = file.name();
        if(file.isDirectory() == false && name.endsWith(".bwav")){
            songs.push_back(file.path());
            num_songs++;
        }
        file.close();
        file = root.openNextFile();
    }
    root.close();

    setAudioFile(songs[current_song]);

    set_leds_black();
    leds[0] = CRGB(0,0,128);
    led_change = true;
    mode = songs[current_song][4] - 48;
    mode_change = true;
}



void setup()
{
    //Buttons
    pinMode(MISC_BUTTON, INPUT);
    pinMode(NEXT_SONG_BUTTON, INPUT);
    pinMode(PLAY_PAUSE_BUTTON, INPUT);
    pinMode(PREVIOUS_SONG_BUTTON, INPUT);

    pinMode(COM_C1, OUTPUT);
    pinMode(COM_C2, OUTPUT);
    pinMode(COM_C3, OUTPUT);
    pinMode(COM_C4, OUTPUT);

    FastLED.addLeds<WS2812B, WS2812_PIN, RGB>(leds, 4);

    //Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    setup_sd_card();
    setup_buffers();
    delay(1000);
}

bool butten_pressed = false;

void handleButtons() {

    int misc_press = digitalRead(MISC_BUTTON);
    int next_press = digitalRead(NEXT_SONG_BUTTON);
    int play_pause_press = digitalRead(PLAY_PAUSE_BUTTON);
    int previous_press = digitalRead(PREVIOUS_SONG_BUTTON);

    if(!misc_press && !next_press && !play_pause_press && !previous_press){
        butten_pressed = false;
    }

    //handle double press
    if(butten_pressed){
        return;
    }

    if(previous_press || next_press) {
        current_song = (current_song + num_songs - 1 * previous_press + 1 * next_press) % num_songs;
        setAudioFile(songs[current_song]);
        led_change = true;
        mode = songs[current_song][4] - 48;
        mode_change = true;
        set_leds_black();
        leds[current_song % NUM_LEDS] = CRGB(0,0,128);
        butten_pressed = true;
    }

    if(play_pause_press){
        play = !play;
        leds[current_song % NUM_LEDS] = CRGB(0,0,128);
        led_change = true;
        butten_pressed = true;
    }

    if(misc_press){
        butten_pressed = true;
        //todo do something
    }
}

void handleLeds(){
    if(led_change){
        FastLED.show();
        led_change = false;
    }
}

void set_mode() {
    if(mode_change){
        mode_change = false;
        digitalWrite(COM_C1, (mode & 0b1) > 0);
        digitalWrite(COM_C2, (mode & 0b10) > 0);
        digitalWrite(COM_C3, (mode & 0b100) > 0);
        digitalWrite(COM_C4, (mode & 0b1000) > 0);
    }
}

bool blink_led_on = true;
void blink(){
    if(blink_led_on){
        leds[current_song % NUM_LEDS] = CRGB(0,0,0);
    }else{
        leds[current_song % NUM_LEDS] = CRGB(0,0,128);
    }
    blink_led_on = !blink_led_on;
    led_change = true;
}

long last_millis = millis();

void loop()
{

    if(slave.available() > 0){
        slave.pop();
    }

    handleButtons();
    set_mode();
    handleLeds();
    if(last_millis + 750 < millis() && play == false){
        blink();
        last_millis = millis();
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
