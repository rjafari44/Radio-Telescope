#!/bin/bash

# Ask the user for their arduino board
read -p "Enter your Arduino Port (e.g., /dev/ttyACM0): " PORT

arduino-cli compile --fqbn arduino:avr:uno --build-property "compiler.cpp.extra_flags=-Iinclude" .

# Upload the code to the board
arduino-cli upload -p $PORT --fqbn arduino:avr:uno .

# open the Serial Monitor at baudrate of 115200 for user input
arduino-cli monitor -p $PORT --config baudrate=115200