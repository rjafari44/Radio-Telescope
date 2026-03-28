#include "common.h"

// variables for calculating joystick value
int stickValue{};
int pwmValue{};
int delta{}; // variable for calculating position

void setup() {
    Serial.begin(115200);

    pinMode(M1_INA, OUTPUT);
    pinMode(M1_INB, OUTPUT);
    pinMode(M1_PWM, OUTPUT);

    pinMode(M2_INA, OUTPUT);
    pinMode(M2_INB, OUTPUT);
    pinMode(M2_PWM, OUTPUT);

    // EN/DIAG pins: open-drain → pull-up
    pinMode(M1_EN, INPUT_PULLUP);
    pinMode(M2_EN, INPUT_PULLUP);

    delay(500);
    Serial.println("Starting!");
}

void loop() {

    static unsigned long stallStartM1 = 0;
    static unsigned long stallStartM2 = 0;
    static bool stalled = false;

    stickValue = analogRead(READSTICK);
    delta = stickValue - CENTER;

    // ===============================
    // STALL MODE — highest priority
    // ===============================
    if (!stalled &&
        (checkStall(M1_CS, stallStartM1) ||
         checkStall(M2_CS, stallStartM2))) {

        Serial.println("STALL CURRENT!");
        stopMotors();

        stalled = true;          // lock everything
        stallStartM1 = 0;
        stallStartM2 = 0;
    }

    // If stalled, ignore joystick until centered
    if (stalled) {

        stopMotors();   // keep forcing off

        if (abs(delta) < DEADZONE) {
            stalled = false;   // reset latch
        }

        return;   // nothing else allowed to run
    }

    // ===============================
    // NORMAL OPERATION
    // ===============================

    if (abs(delta) < DEADZONE) {
        stopMotors();
    }
    else if (delta > 0) {

        pwmValue = map(delta, DEADZONE, 512, 0, 255);
        if (pwmValue > MAXSPEED) pwmValue = MAXSPEED;

        forwardMotors(pwmValue);
    }
    else {

        pwmValue = map(-delta, DEADZONE, 512, 0, 255);
        if (pwmValue > MAXSPEED) pwmValue = MAXSPEED;

        reverseMotors(pwmValue);
    }

    // Fault pins
    if (digitalRead(M1_EN) == LOW || digitalRead(M2_EN) == LOW) {
        stopMotors();
    }
}

