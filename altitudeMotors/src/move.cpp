#include "common.h"

// function to stop motors, returns nothing
void stopMotors(){
    // give the motors 0 power
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);

    // coast to stop
    digitalWrite(M1_INA, LOW);
    digitalWrite(M1_INB, LOW);
    digitalWrite(M2_INA, LOW);
    digitalWrite(M2_INB, LOW);
}

void forwardMotors(int pwmValue) {
    digitalWrite(M1_INA, HIGH);
    digitalWrite(M1_INB, LOW);
    digitalWrite(M2_INA, HIGH);
    digitalWrite(M2_INB, LOW);

    analogWrite(M1_PWM, pwmValue);
    analogWrite(M2_PWM, pwmValue);
}

void reverseMotors(int pwmValue) {
    digitalWrite(M1_INA, LOW);
    digitalWrite(M1_INB, HIGH);
    digitalWrite(M2_INA, LOW);
    digitalWrite(M2_INB, HIGH);

    analogWrite(M1_PWM, pwmValue);
    analogWrite(M2_PWM, pwmValue);
}