#pragma once

// motor driver pins
constexpr int M1_INA{2};
constexpr int M1_INB{3};
constexpr int M1_PWM{7};
constexpr int M1_EN {4};  // EN/DIAG sense for motor 1
constexpr int M1_CS {14}; // current sense for motor 1

constexpr int M2_INA{5};
constexpr int M2_INB{6};
constexpr int M2_PWM{8};
constexpr int M2_EN {9}; // EN/DIAG for motor 2
constexpr int M2_CS {15}; // current sense for motor 2

// joystick
constexpr int READSTICK{16};
constexpr int CENTER{512};
constexpr int DEADZONE{20};
constexpr int MAXSPEED{140};

// current sense parameters
constexpr float CURRENT_SENSE = 0.14; // V/A
constexpr float STALL_CURRENT = 2.5;   // Amps
constexpr unsigned long STALL_TIME = 50; // ms

void stopMotors();
void forwardMotors(int pwmValue);
void reverseMotors(int pwmValue);

float readCurrent(int csPin);
bool checkStall(int csPin, unsigned long &stallStart);