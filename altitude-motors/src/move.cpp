#include "common.h"

// function for driving both motors forward, returns nothing
void forwardMotors(int pwmValue) {
    digitalWrite(M1_INA, HIGH);
    digitalWrite(M1_INB, LOW);
    digitalWrite(M2_INA, HIGH);
    digitalWrite(M2_INB, LOW);
    analogWrite(M1_PWM, pwmValue);
    analogWrite(M2_PWM, pwmValue);
}

// function for driving both motors in reverse, returns nothing
void reverseMotors(int pwmValue) {
    digitalWrite(M1_INA, LOW);
    digitalWrite(M1_INB, HIGH);
    digitalWrite(M2_INA, LOW);
    digitalWrite(M2_INB, HIGH);
    analogWrite(M1_PWM, pwmValue);
    analogWrite(M2_PWM, pwmValue);
}

// function for stopping both motors, returns nothing
void stopMotors() {
    // zero PWM first, then coast
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);
    digitalWrite(M1_INA, LOW);
    digitalWrite(M1_INB, LOW);
    digitalWrite(M2_INA, LOW);
    digitalWrite(M2_INB, LOW);
}