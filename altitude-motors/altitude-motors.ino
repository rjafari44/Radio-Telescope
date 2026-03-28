#include "common.h"

// function for setting up the arduino code, runs once, returns nothing
void setup() {
    // set motor direction and speed pins as output
    pinMode(M1_INA, OUTPUT);
    pinMode(M1_INB, OUTPUT);
    pinMode(M1_PWM, OUTPUT);
    pinMode(M2_INA, OUTPUT);
    pinMode(M2_INB, OUTPUT);
    pinMode(M2_PWM, OUTPUT);

    // EN/DIAG are open-drain — INPUT_PULLUP holds them HIGH until the driver faults
    pinMode(M1_EN, INPUT_PULLUP);
    pinMode(M2_EN, INPUT_PULLUP);

    delay(500);
    Serial.begin(115200);
    Serial.println("Starting!");
}

// function for running the arduino code, loops, returns nothing
void loop() {
    static unsigned long stallStartM1 = 0; // variable to track stall timer for motor 1
    static unsigned long stallStartM2 = 0; // variable to track stall timer for motor 2
    static bool stalled = false;           // variable to track stall latch state
    int stickValue{};                      // variable of integer type for raw joystick ADC reading
    int delta{};                           // variable of integer type for joystick deflection from center
    int pwmValue{};                        // variable of integer type for calculated PWM output

    // VNH5019 pulls EN/DIAG LOW on a driver fault — check before anything else
    if (digitalRead(M1_EN) == LOW || digitalRead(M2_EN) == LOW) {
        stopMotors();
        Serial.println("DRIVER FAULT!");
        return;
    }

    stickValue = analogRead(READSTICK); // store joystick position
    delta      = stickValue - CENTER;   // positive = forward, negative = reverse

    // check both motors for sustained overcurrent
    if (!stalled &&
        (checkStall(M1_CS, stallStartM1) ||
         checkStall(M2_CS, stallStartM2))) {

        Serial.println("STALL CURRENT!");
        stopMotors();
        stalled = true; // latch — operator must center joystick to re-engage
    }

    // keep motors off until joystick returns to center
    if (stalled) {
        stopMotors();
        if (abs(delta) < DEADZONE)
            stalled = false;
        return;
    }

    // map joystick deflection to PWM with deadzone at center
    if (abs(delta) < DEADZONE) {
        stopMotors();
    }
    else if (delta > 0) {
        pwmValue = map(delta, DEADZONE, 512, 0, MAXSPEED);
        forwardMotors(pwmValue);
    }
    else {
        pwmValue = map(-delta, DEADZONE, 512, 0, MAXSPEED);
        reverseMotors(pwmValue);
    }
}
