# Radio Telescope — Altitude Motor Controller

Joystick-controlled dual motor driver for the altitude axis of a radio telescope. An Arduino Uno and Pololu Dual VNH5019 motor driver shield drive two WindyNation 20-inch linear actuators in tandem, with current-based stall detection and hardware fault monitoring to protect both the actuators and the telescope structure.

This is the standalone prototype version — the joystick is a single analog module wired directly to the Uno. A more robust version integrated into a control panel is in development.

The system is divided into three primary sections:

- [Bill of Materials](#bill-of-materials)
- [Electrical](#electrical)
- [Usage](#usage)

---

## Bill of Materials

| Component | Part |
|-----------|------|
| Microcontroller | Arduino Uno |
| Motor Driver | Pololu Dual VNH5019 Motor Driver Shield |
| Linear Actuators | WindyNation 20" Linear Actuators (×2) |
| Joystick | Analog joystick module |

<br>

Pololu Dual VNH5019 Motor Driver Shield product page: [https://www.pololu.com/product/2507](https://www.pololu.com/product/2507)

---

## Electrical

The VNH5019 shield stacks directly onto the Arduino Uno. Each linear actuator connects to one of the two motor output channels on the shield. The joystick module is wired to an analog input pin on the Uno.

The WindyNation linear actuators have built-in limit switches that cut power at the ends of travel. However, regularly driving into the limit switches puts unnecessary stress on the actuator and telescope structure — operators should stop well before the physical limits.

### Wiring Diagram

Any hardware or electrical specific constraints are mentioned in the product website.

### Actuator Direction Logic

The VNH5019 controls direction via INA and INB per channel:

| INA | INB | Result  |
|-----|-----|---------|
| HIGH | LOW | Forward |
| LOW | HIGH | Reverse |
| LOW | LOW | Coast   |

### Fault & Stall Protection

Two independent protection layers run every loop iteration, in priority order:

**1. Hardware fault (EN/DIAG pins)**  
The VNH5019 pulls EN/DIAG LOW on a driver-level fault — overcurrent, thermal shutdown, or undervoltage. This is checked first, before any joystick input is read or motor commands are sent. The motors are stopped immediately and a fault message is printed to Serial.

**2. Software stall detection (CS pins)**  
The VNH5019 CS pins output a voltage proportional to motor current (0.14 V/A). If current on either motor exceeds 2.5 A for more than 50 ms, the motors are stopped and a stall latch is set. The latch only clears once the joystick is returned to center — this forces the operator to consciously re-engage rather than immediately re-driving into a stall.

---

## Usage

**Important:**
- The WindyNation linear actuators have built-in limit switches that will cut power at the ends of travel. Do not rely on them as a normal stopping point — always stop the actuators well before the physical limits to avoid stressing the actuator internals and telescope mount.
- Do not drive both actuators to full extension or full retraction repeatedly in quick succession.
- If the Serial Monitor shows `DRIVER FAULT!`, disconnect motor power and inspect the driver and wiring before attempting to run again.
- If the Serial Monitor shows `STALL CURRENT!`, center the joystick to reset and confirm the altitude axis moves freely before re-engaging.

<br>

**Steps to run:**
1. Upload the firmware to the Arduino Uno via the Arduino IDE or CLI.
2. Connect motor power to the VNH5019 shield.
3. Push the joystick forward to extend the actuators (raise), backward to retract (lower).
4. Release the joystick to stop — the deadzone at center ensures the actuators cut off cleanly.

