#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Rotary.h"
#include "Music.h"
#include "ArduinoHardware.h"
#include "songs.h"
#include "VoltageSensor.h"
#include "Controller.h"
#include "LCDDisplay.h"
#include "EEPROMConfig.h"
#include "LinkedSwitch.h"

#define FETPin 6

Hardware *hardware;
Rotary *rotary;
LiquidCrystal *lcd;
Display *display;
Music *warning;
Music *alarm;
VoltageSensor *loadPositiveSensor;
VoltageSensor *loadNagativeSensor;
Config *config;
LinkedSwitch *load;
LinkedSwitch *greenLight;
Switch *redLight;
Controller *controller;

void rotaryRotated() { Serial.println("rotate"); rotary->handleRotation(); }

void rotaryClicked() { Serial.println("click"); rotary->handleClick(); }

int availableMemory() {
    int size = 2048; // Use 2048 with ATmega328
    byte *buf;

    while ((buf = (byte *) malloc(--size)) == NULL)
        ;

    free(buf);

    return size;
}

void setup() {
    Serial.begin(9600);

    hardware = new ArduinoHardware();
    rotary = new Rotary(hardware, 2, 4, 3);
    lcd = new LiquidCrystal(7, 8, 9, 10, 11, 12);
    display = new LCDDisplay(lcd);
    warning = new Music(hardware, 5);
    alarm = new Music(hardware, 5);
    loadPositiveSensor = new VoltageSensor(hardware, 0);
    loadNagativeSensor = new VoltageSensor(hardware, 3);
    config = new EEPROMConfig();
    load = new LinkedSwitch(hardware, 6, false);
    greenLight = new LinkedSwitch(hardware, A5, true);
    redLight = new Switch(hardware, A6, false);
    greenLight->setNext(redLight);
    load->setNext(greenLight);
    controller = new Controller(hardware, loadPositiveSensor, loadNagativeSensor, display, rotary, config, alarm, warning, load);

    hereComesTheSun(warning);
    anotherOneBitesTheDust(alarm);

    controller->setup();

    attachInterrupt(digitalPinToInterrupt(rotary->getSW()), rotaryClicked, FALLING);
    attachInterrupt(digitalPinToInterrupt(rotary->getCLK()), rotaryRotated, FALLING);

    Serial.print("mem: ");
    Serial.println(availableMemory());

}

void loop() {
//    Serial.println(millis());
    controller->tick(millis());
}
