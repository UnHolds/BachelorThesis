#include <Arduino.h>
#include <SPI.h>
#include <ADS1X15.h>


SPIClass *vspi = new SPIClass(VSPI);

#define MASK 0b0011111111110000
#define GAIN_1 0x2000
#define ACTIVE 0x1000

#define INPUT_DAC_CS 17
#define VCC_DAC_CS 16

#define ADC_4_OUTPUT_DAC_VCC_PIN 1
#define ADC_4_OUTPUT_VCC_VCC_PIN 0
#define ADC_4_VCC_PIN 2
#define ADC_4_INPUT_PIN 3

#define MAX_VCC_DAC_VALUE 255
#define MIN_VCC_DAC_VALUE 128

ADS1115 ADS(0x48);
char buffer[248];

void setVoltage(uint8_t cs, uint8_t value)
{
    vspi->beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(cs, LOW);
    uint16_t data = value << 4;
    data |= ACTIVE;
    data &= MASK;
    vspi->transfer16(data);
    digitalWrite(cs, HIGH);
    vspi->endTransaction();
}

double measureVoltage(uint8_t pin){
    return ADS.readADC(pin) * 0.0001875;
}
/*
void runInputRamp(int vccS){
    for(int i = 0; i < 256; i++){
        setVoltage(INPUT_DAC_CS, i);
        delay(100);
        reportMeasurement(vccS, i);
    }
}

void runVccRamp(){
    for(int i = MAX_VCC_DAC_VALUE; i >= MIN_VCC_DAC_VALUE; i--){
        setVoltage(VCC_DAC_CS, i);
        delay(100);
        runInputRamp(i);
    }
}
*/

void setup()
{

    Serial.begin(115200);

    pinMode(INPUT_DAC_CS, OUTPUT);
    digitalWrite(INPUT_DAC_CS, HIGH);
    pinMode(VCC_DAC_CS, OUTPUT);
    digitalWrite(VCC_DAC_CS, HIGH);
    vspi->begin();

    ADS.begin();
    ADS.setGain(0);

    setVoltage(INPUT_DAC_CS, 0);
    setVoltage(VCC_DAC_CS, 255);

    delay(1000);
    Serial.print("CMD: ");
}


String command = "";
int idx = 0;

int ampleState = 0;
bool simulate = false;

void printHelp(){
    Serial.println("help - display this");
    Serial.println("toggle - switch traffic light state");
    Serial.println("metastable - set metastable state");
    Serial.println("set <bits> - set custom input DAC value");
    Serial.println("simulate - switch between traffic light states");
}


void handleCommand (){
    if(command == "help"){
        printHelp();
    }else if (command == "toggle"){
        Serial.println("Toogleing traffic light");
        setVoltage(INPUT_DAC_CS, ampleState == 0 ? 255 : 0);
        ampleState = ampleState == 0 ? 1 : 0;
    }else if(command == "metastable"){
        Serial.println("Setting metastable voltage");
        setVoltage(INPUT_DAC_CS, 140);
    }else if(command.startsWith("set ")){
        int voltage = command.substring(4).toInt();
        Serial.print("Setting voltage to: ");
        Serial.println(voltage);
        setVoltage(INPUT_DAC_CS, voltage);
    }else if(command == "simulate"){
        Serial.println("Enabling simulation");
        simulate = true;
    }else{
        Serial.println(command);
        Serial.println("Unknown Command: " + command + " type 'help' to view all commands");
    }
}

long currentMillis = millis();
void handleSimulation(){
    if(millis() - currentMillis > 3000){
        setVoltage(INPUT_DAC_CS, ampleState == 0 ? 255 : 0);
        ampleState = ampleState == 0 ? 1 : 0;
        currentMillis = millis();
    }
}

void loop()
{

    if(Serial.available() && simulate){
        Serial.print("\nExiting simulation mode\n");
        simulate = false;
    } else if (simulate){
        handleSimulation();
    }


    if(Serial.available()){
        char input = Serial.read();

        if(input == '\n' || input == '\r'){

            while(Serial.read() != -1){
                continue;
            }
            Serial.print("\n");
            handleCommand();
            command = "";
            Serial.print("\nCMD: ");
        }else{
            Serial.print(input);
            command += input;
        }
    }
}