#include <HardwareSerial.h>
#include "EEPROMConfig.h"
#include "EEPROM.h"

#define VA_Address 36
#define VA_MAGIC_NUMBER 43

struct TransferData {
    float cutoffVoltage;
    char cutoffDirection;
    float pVoltageInterference;
    float nVoltageInterference;
};

void EEPROMConfig::save() {
    struct TransferData data{};
    data.cutoffVoltage = cutoffVoltage;
    data.cutoffDirection = cutoffDirection;
    data.pVoltageInterference = pVoltageInterference;
    data.nVoltageInterference = nVoltageInterference;

    EEPROM.write(VA_Address, VA_MAGIC_NUMBER);
    EEPROM.put(VA_Address + 1, data);
    Serial.println("save");
}

bool EEPROMConfig::load() {
    uint8_t id = EEPROM.read(VA_Address);
    Serial.print("id: ");
    Serial.println(id);
    if (id == VA_MAGIC_NUMBER) { //  That's our cue
        struct TransferData data{};
        EEPROM.get(VA_Address + 1, data);
        cutoffVoltage = data.cutoffVoltage;
        cutoffDirection = data.cutoffDirection;
        pVoltageInterference = data.pVoltageInterference;
        nVoltageInterference = data.nVoltageInterference;
        return true;
    } else
        return false;
}