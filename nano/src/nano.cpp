#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Rotary.h"
#include "Music.h"
#include "ArduinoHardware.h"

#define Vpin 0
#define FETPin 6

// 2.5V with diode reads in at 497


int vIn;
Hardware *hardware = new ArduinoHardware();
Rotary rotary(hardware, 2, 4, 3);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Music music(hardware, 5);


void note(unsigned int thisNote, unsigned long duration);

void handleRotary();

void rotaryRotated() { rotary.handleRotation(); }

void rotaryClicked() { rotary.handleClick(); }

void hereComesTheSun() {
    music.setWholeNoteDuration(2000);
    music.setLoop(true);
    music.setLoopDelay(music.getNoteDuration(DOUBLE_NOTE));

    music.addNote(NOTE_B5, EIGHTH_NOTE);
    music.addNote(NOTE_A5, QUARTER_NOTE);
    music.addNote(NOTE_B5, QUARTER_NOTE);

    music.addNote(NOTE_G5, HALF_NOTE);
    music.addNote(NOTE_B5, EIGHTH_NOTE);
    music.addNote(NOTE_G5, EIGHTH_NOTE);
    music.addNote(NOTE_A5, EIGHTH_NOTE);
    music.addNote(NOTE_B5, THREE_EIGHTHS_NOTE);

    music.addNote(NOTE_REST, EIGHTH_NOTE);
    music.addNote(NOTE_B5, EIGHTH_NOTE);
    music.addNote(NOTE_A5, QUARTER_NOTE);
    music.addNote(NOTE_B5, QUARTER_NOTE);

    music.addNote(NOTE_G5, HALF_NOTE);
    music.addNote(NOTE_B5, EIGHTH_NOTE);
    music.addNote(NOTE_A5, QUARTER_NOTE);
    music.addNote(NOTE_G5, THREE_EIGHTHS_NOTE);

    music.addNote(NOTE_REST, EIGHTH_NOTE);
    music.addNote(NOTE_B5, QUARTER_NOTE);
    music.addNote(NOTE_A5, QUARTER_NOTE);
    music.addNote(NOTE_G5, QUARTER_NOTE);

    music.addNote(NOTE_E6, EIGHTH_NOTE);
    music.addNote(NOTE_G6, EIGHTH_NOTE);
    music.addNote(NOTE_A6, EIGHTH_NOTE);
    music.addNote(NOTE_D6, EIGHTH_NOTE);
    music.addNote(NOTE_G6, EIGHTH_NOTE);
    music.addNote(NOTE_A6, EIGHTH_NOTE);
    music.addNote(NOTE_C6, EIGHTH_NOTE);
    music.addNote(NOTE_G6, EIGHTH_NOTE);

    music.addNote(NOTE_A6, EIGHTH_NOTE);
    music.addNote(NOTE_D6, EIGHTH_NOTE);
    music.addNote(NOTE_G6, EIGHTH_NOTE);
    music.addNote(NOTE_A6, EIGHTH_NOTE);
    music.addNote(NOTE_G6, EIGHTH_NOTE);
    music.addNote(NOTE_FS6, EIGHTH_NOTE);
    music.addNote(NOTE_E6, EIGHTH_NOTE);
    music.addNote(NOTE_D6, EIGHTH_NOTE);

    music.addNote(NOTE_G6, QUARTER_NOTE);
}

void setup() {
    Serial.begin(9600);

    pinMode(FETPin, OUTPUT);

    rotary.setup();
    attachInterrupt(digitalPinToInterrupt(rotary.getSW()), rotaryClicked, FALLING);
    attachInterrupt(digitalPinToInterrupt(rotary.getCLK()), rotaryRotated, FALLING);

    music.setup();
    hereComesTheSun();

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

    music.play();

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

