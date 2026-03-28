#pragma once

#include <Arduino.h>

// motor 1 pins
constexpr int M1_INA{2};  // direction control A
constexpr int M1_INB{3};  // direction control B
constexpr int M1_PWM{7};  // speed (PWM)
constexpr int M1_EN {4};  // EN/DIAG fault sense — VNH5019 pulls LOW on fault
constexpr int M1_CS {14}; // current sense (analog)

// motor 2 pins
constexpr int M2_INA{5};
constexpr int M2_INB{6};
constexpr int M2_PWM{8};
constexpr int M2_EN {9};
constexpr int M2_CS {15};

// joystick
constexpr int READSTICK{16}; // analog input pin
constexpr int CENTER{512};   // 10-bit ADC midpoint
constexpr int DEADZONE{20};  // counts either side of center treated as stop
constexpr int MAXSPEED{140}; // ~55% duty cycle — mechanical limit of the platform

// current sense — VNH5019 CS pin outputs 0.14 V/A (datasheet)
constexpr float CURRENT_SENSE{0.14};    // V/A
constexpr float STALL_CURRENT{2.5};     // amps — threshold to suspect stall
constexpr unsigned long STALL_TIME{50}; // ms — sustained overcurrent before confirmed stall

// movement functions
void stopMotors();
void forwardMotors(int pwmValue);
void reverseMotors(int pwmValue);

// current sense functions
float readCurrent(int csPin);
bool checkStall(int csPin, unsigned long &stallStart);