#include <HardwareSerial.h>
#include "EEPROMConfig.h"
#include "EEPROM.h"

#define VA_Address 36
#define VA_MAGIC_NUMBER 44

struct TransferData {
    float cutoffVoltage;
    char cutoffDirection;
    float pVoltageInterference;
    float nVoltageInterference;
    float warningBuffer;
};

void EEPROMConfig::save() {
    struct TransferData data{};
    data.cutoffVoltage = cutoffVoltage;
    data.cutoffDirection = cutoffDirection;
    data.pVoltageInterference = pVoltageInterference;
    data.nVoltageInterference = nVoltageInterference;
    data.warningBuffer = warningBuffer;

    EEPROM.write(VA_Address, VA_MAGIC_NUMBER);
    EEPROM.put(VA_Address + 1, data);
}

bool EEPROMConfig::load() {
    uint8_t id = EEPROM.read(VA_Address);
    if (id == VA_MAGIC_NUMBER) { //  That's our cue
        struct TransferData data{};
        EEPROM.get(VA_Address + 1, data);
        cutoffVoltage = data.cutoffVoltage;
        cutoffDirection = data.cutoffDirection;
        pVoltageInterference = data.pVoltageInterference;
        nVoltageInterference = data.nVoltageInterference;
        warningBuffer = data.warningBuffer;
        return true;
    } else
        return false;
}
