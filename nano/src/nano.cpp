#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Rotary.h"
#include "Music.h"
#include "ArduinoHardware.h"
#include "songs.h"

#define Vpin 0
#define FETPin 6

// 2.5V with diode reads in at 497


int vIn;
Hardware *hardware = new ArduinoHardware();
Rotary rotary(hardware, 2, 4, 3);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Music warning(hardware, 5);
Music alarm(hardware, 5);

void handleRotary();

void rotaryRotated() { rotary.handleRotation(); }

void rotaryClicked() { rotary.handleClick(); }

void setup() {
    Serial.begin(9600);

    pinMode(FETPin, OUTPUT);

    rotary.setup();
    attachInterrupt(digitalPinToInterrupt(rotary.getSW()), rotaryClicked, FALLING);
    attachInterrupt(digitalPinToInterrupt(rotary.getCLK()), rotaryRotated, FALLING);

    warning.setup();
    hereComesTheSun(warning);
    alarm.setup();
    anotherOneBitesTheDust(alarm);


    lcd.begin(16, 2);
    lcd.print("Hello, World!");
    lcd.cursor();
    lcd.blink();
}

void loop() {

//    digitalWrite(FETPin, HIGH);

//    vIn = analogRead(Vpin);
//    Serial.println(vIn);
//    delay(500);

//    digitalWrite(FETPin, LOW);
//    delay(500);

//    warning.play();
    alarm.play();

//    lcd.setCursor(0, 1);
//    lcd.print(millis() / 1000);
//    lcd.setCursor(0, 1);

//    playPassive();

    handleRotary();

}

void handleRotary() {
    if (rotary.hasUpdate()) {
        if (rotary.wasClicked())
            rotary.setPosition(0);
        rotary.rest();

        Serial.print("rotaryPosition: ");
        Serial.println(rotary.getPosition());
    }
}

