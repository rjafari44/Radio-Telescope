#include "common.h"

// function for reading motor current from a CS pin, returns current in amps
float readCurrent(int csPin) {
    int sensorValue{}; // variable for storing sensor value
    float voltage{};   // variable for calculating voltage
    
    sensorValue = analogRead(csPin);
    voltage = sensorValue * (5.0 / 1023.0); // convert ADC count to volts

    return voltage / CURRENT_SENSE;                     // convert volts to amps
}

// function for checking if a motor has stalled, returns true if stall is confirmed
// stallStart is passed by reference so the timer persists across loop() calls
bool checkStall(int csPin, unsigned long &stallStart) {
    float current{}; // variable for getting current
    
    current = readCurrent(csPin);

    if (current > STALL_CURRENT) {
        if (stallStart == 0)
            stallStart = millis();               // start timing the overcurrent event

        if (millis() - stallStart > STALL_TIME)
            return true;                         // sustained overcurrent — confirmed stall
    } else {
        stallStart = 0;                          // current normal, reset timer
    }

    return false;
}