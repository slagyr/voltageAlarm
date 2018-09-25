#include "Arduino.h"
#include "LiquidCrystal.h"
#include "pitches.h"
#include "Rotary.h"
#include "ArduinoHardware.h"

#define Vpin 0
#define FETPin 6
#define buzzer 5

// 2.5V with diode reads in at 497


int vIn;
Hardware *hardware = new ArduinoHardware();
Rotary rotary(hardware, 2, 4, 3);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void playPassive();

void note(unsigned int thisNote, unsigned long duration);

void handleRotary();
void rotaryRotated() {rotary.handleRotation();}
void rotaryClicked() {rotary.handleClick();}

void setup() {
    Serial.begin(9600);

    pinMode(buzzer, OUTPUT);
    pinMode(FETPin, OUTPUT);

    rotary.setup();
    attachInterrupt(digitalPinToInterrupt(rotary.getSW()), rotaryClicked, FALLING);
    attachInterrupt(digitalPinToInterrupt(rotary.getCLK()), rotaryRotated, FALLING);

    lcd.begin(16, 2);
    lcd.print("Hello, World!");
    lcd.cursor();
    lcd.blink();

    tone(buzzer, NOTE_C5, 5000);

}

void loop() {

    digitalWrite(FETPin, HIGH);

    vIn = analogRead(Vpin);
    Serial.println(vIn);
    delay(500);

    digitalWrite(FETPin, LOW);
    delay(500);

    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
    lcd.setCursor(0, 1);

//    playPassive();

    handleRotary();

}


unsigned long whole = 600;
unsigned long threeQuarters = (unsigned long) (whole * 0.75);
unsigned long half = (unsigned long) (whole * 0.5);
unsigned long quarter = (unsigned long) (whole * 0.25);
unsigned long eigth = (unsigned long) (whole * 0.125);

void playPassive() {
    note(NOTE_E5, threeQuarters);
    note(NOTE_D5, quarter);
    note(NOTE_C5, half);
    note(NOTE_D5, half);
    note(NOTE_E5, half);
    note(NOTE_E5, half);
    note(NOTE_E5, whole);
    note(NOTE_D5, half);
    note(NOTE_D5, half);
    note(NOTE_D5, whole);
    note(NOTE_E5, half);
    note(NOTE_G5, half);
    note(NOTE_G5, whole);

    note(NOTE_E5, threeQuarters);
    note(NOTE_D5, quarter);
    note(NOTE_C5, half);
    note(NOTE_D5, half);
    note(NOTE_E5, half);
    note(NOTE_E5, half);
    note(NOTE_E5, half);
    note(NOTE_E5, half);
    note(NOTE_D5, half);
    note(NOTE_D5, half);
    note(NOTE_E5, half);
    note(NOTE_D5, half);
    note(NOTE_C5, half);
    note(NOTE_G5, eigth);
    note(NOTE_F5, eigth);
    note(NOTE_E5, eigth);
    note(NOTE_D5, eigth);
    note(NOTE_C5, whole);

    delay(whole);
}

void note(unsigned int thisNote, unsigned long duration) {
    tone(buzzer, thisNote, duration);
    delay(duration + 10);
}

void handleRotary() {
    if (rotary.hasUpdate()) {
        if(rotary.wasClicked())
            rotary.setPosition(0);
        rotary.rest();

        Serial.print("rotaryPosition: ");
        Serial.println(rotary.getPosition());
    }
}

