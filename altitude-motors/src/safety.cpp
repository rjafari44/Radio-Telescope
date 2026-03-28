#include "common.h"

float readCurrent(int csPin) {
    int sensorValue{};
    float voltage{};

    sensorValue = analogRead(csPin);
    voltage = sensorValue * (5.0 / 1023.0);

    return voltage / CURRENT_SENSE;
}

// --- Stall detection function ---
// Returns true if motor should be stopped
bool checkStall(int csPin, unsigned long &stallStart) {
    float current{};
    
    current = readCurrent(csPin);

    if (current > STALL_CURRENT) {
        if (stallStart == 0) {
            stallStart = millis();
        }
        if (millis() - stallStart > STALL_TIME) { 
            return true; // confirmed stall
        }
    } else {
        stallStart = 0; // reset when current drops
    }
    
    return false;
}
