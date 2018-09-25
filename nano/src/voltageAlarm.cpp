#include "Arduino.h"
#include "LiquidCrystal.h"
#include "pitches.h"

#define DEBOUNCE_MILLIS 50
#define Vpin 0
#define FETPin 6
#define buzzer 5
#define PinCLK 3
#define PinDT 4
#define PinSW 2

// 2.5V with diode reads in at 497

volatile boolean rotaryUpdated;
int rotaryPosition = 0;
int vIn;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
unsigned long lastRotaryInturrupt = 0;

void playPassive();

void note(unsigned int thisNote, unsigned long duration);

void handleRotary();

void rotaryRotated();

void rotaryClicked();

void setup() {
    Serial.begin(9600);

    pinMode(PinCLK, INPUT);
    pinMode(PinDT, INPUT);
    pinMode(PinSW, INPUT);
    pinMode(FETPin, OUTPUT);
    digitalWrite(PinSW, HIGH);
    attachInterrupt(digitalPinToInterrupt(PinSW), rotaryClicked, FALLING);
    attachInterrupt(digitalPinToInterrupt(PinCLK), rotaryRotated, FALLING);

    pinMode(buzzer, OUTPUT);
    lcd.begin(16, 2);
    lcd.print("Hello, World!");
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

boolean rotaryNotBounced() {
    unsigned long now = millis();
    if (now > lastRotaryInturrupt + DEBOUNCE_MILLIS) {
        lastRotaryInturrupt = now;
        return true;
    } else
        return false;
}

void rotaryRotated() {
    if (rotaryNotBounced()) {
        int clk = digitalRead(PinCLK);
        int dt = digitalRead(PinDT);
        rotaryPosition = clk == dt ? rotaryPosition + 1 :  rotaryPosition - 1;
        rotaryUpdated = true;
    }
}

void rotaryClicked() {
    if (rotaryNotBounced()) {
        rotaryPosition = 0;
        rotaryUpdated = true;
    }
}

void handleRotary() {
    if (rotaryUpdated) {
        rotaryUpdated = false;

        Serial.print("rotaryPosition: ");
        Serial.println(rotaryPosition);
    }
}

