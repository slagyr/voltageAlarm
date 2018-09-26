#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Rotary.h"
#include "Music.h"
#include "ArduinoHardware.h"
#include "songs.h"
#include "VoltageSensor.h"
#include "Controller.h"
#include "LCDDisplay.h"
#include "EEPROM.h"

#define FETPin 6

Hardware *hardware;
Rotary *rotary;
LiquidCrystal *lcd;
Display *display;
Music *warning;
Music *alarm;
VoltageSensor *loadPositiveSensor;
VoltageSensor *loadNagativeSensor;
Controller *controller;

void handleRotary();

void rotaryRotated() { rotary->handleRotation(); }

void rotaryClicked() { rotary->handleClick(); }

void setup() {
    Serial.begin(9600);

    hardware = new ArduinoHardware();
    rotary = new Rotary(hardware, 2, 4, 3);
    lcd = new LiquidCrystal(7, 8, 9, 10, 11, 12);
    display = new LCDDisplay(lcd);
    warning = new Music(hardware, 5);
    alarm = new Music(hardware, 5);
    loadPositiveSensor = new VoltageSensor(hardware, 0, -0.0);
    loadNagativeSensor = new VoltageSensor(hardware, 3, -0.0);
    controller = new Controller(hardware, loadPositiveSensor, loadNagativeSensor, display);

    pinMode(FETPin, OUTPUT);

    rotary->setup();
    attachInterrupt(digitalPinToInterrupt(rotary->getSW()), rotaryClicked, FALLING);
    attachInterrupt(digitalPinToInterrupt(rotary->getCLK()), rotaryRotated, FALLING);

    warning->setup();
    hereComesTheSun(warning);
    alarm->setup();
    anotherOneBitesTheDust(alarm);

//    lcd.print("Hello, World!");
//    lcd.cursor();
//    lcd.blink();
    Serial.println("Ending setup");

    EEPROM.read(0);
}

void loop() {
    controller->tick(millis());

//    digitalWrite(FETPin, HIGH);

//    vIn = analogRead(Vpin);
//    Serial.println(vIn);
//    delay(500);

//    digitalWrite(FETPin, LOW);
//    delay(500);

//    warning.play();
//    alarm->play();

//    lcd.setCursor(0, 1);
//    lcd.print(millis() / 1000);
//    lcd.setCursor(0, 1);

//    playPassive();

    handleRotary();
}

void handleRotary() {
    if (rotary->hasUpdate()) {
        if (rotary->wasClicked())
            rotary->setPosition(0);
        rotary->rest();

        Serial.print("rotaryPosition: ");
        Serial.println(rotary->getPosition());
    }
}

