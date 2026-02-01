# Build Guide

This guide covers hardware wiring and bring-up for the **Hybrid Control Lab**.

---

## 1. Hardware Overview

| Node | Purpose | Interfaces |
|---|---|---|
| Control Head (Panel MCU) | Primary UI + keypad + pot | CAN (recommended) or UART |
| ECU (Arduino Uno R4 WiFi) | Control loop + safety + actuator control | CAN + PWM/GPIO |
| Raspberry Pi 5 (optional) | Logging, fuzzing, injection, analysis | CAN (2nd interface), USB/Wi-Fi |

---

## 2. Parts Required

Minimum:
- Control Head input panel (display + keypad + potentiometer)
- Arduino Uno R4 WiFi
- CAN transceivers / CAN boards (2 nodes minimum)
- Motor (servo recommended for MVP) + external power supply
- Jumper wires

Recommended:
- 120Ω termination resistors (if not already on CAN boards)
- External 5–6V supply for servo (or motor driver + supply for DC motor)

---

## 3. Electrical Safety Rules (Do This)

- **Do not** power any motor from the Arduino 5V pin.
- Use a **separate motor power supply**.
- Tie **all grounds together** (Panel GND ↔ ECU GND ↔ Motor PSU GND).
- Keep motor wiring physically separated from CAN wiring to reduce noise.

---

## 4. CAN Bus Wiring

### 4.1 Topology (2-node MVP)

- [Control Head] <-- CANH/CANL --> [ECU]


### 4.2 Wiring
- CANH ↔ CANH
- CANL ↔ CANL
- GND ↔ GND (recommended)

### 4.3 Termination
- There must be **120Ω at each end** of the bus (total ~60Ω measured across CANH/CANL when powered off).
- If your CAN boards include termination jumpers, enable termination only at the two ends.

---

## 5. Actuator Wiring (MVP Servo)

Servo is the recommended MVP actuator.

### 5.1 Power
- Servo V+ → external 5–6V supply
- Servo GND → external supply GND
- External supply GND → Arduino GND (**common ground required**)

### 5.2 Signal
- Servo signal → Arduino PWM-capable pin

---

## 6. Bring-Up Checklist (MVP)

### Phase 0 — Sanity Checks
- [ ] All nodes share common ground
- [ ] CANH/CANL not swapped
- [ ] Termination correct (~60Ω across CANH/CANL with power off)
- [ ] Motor has external power

### Phase 1 — ECU-only
- [ ] ECU boots and outputs a known-safe actuator state
- [ ] ECU periodically sends **0x100 Telemetry** at 10 Hz

### Phase 2 — Control Head RX
- [ ] Control Head receives 0x100 and updates STATUS page
- [ ] Mode, actuator %, and flags display correctly

### Phase 3 — Control Head TX
- [ ] Control Head sends **0x200 Operator Command** on user input
- [ ] ECU receives 0x200 and acknowledges by changing telemetry output

### Phase 4 — Actuator Motion
- [ ] ECU sets actuator output based on 0x200
- [ ] Servo/motor moves as expected
- [ ] Feedback value updates (even if simulated at first)

### Phase 5 — Alerts
- [ ] ECU generates a test alert using **0x110 Alert/CAS**
- [ ] Control Head displays the alert and allows ACK behavior (if implemented)

---

## 7. Known-Good Rates

| Signal | Rate |
|---|---:|
| 0x100 Telemetry | 10 Hz |
| 0x110 Alerts | Event-driven |
| 0x200 Commands | Event-driven |

---

## 8. Debugging

### 8.1 CAN Bus Not Working
- Verify termination (~60Ω across CANH/CANL, powered off)
- Verify CANH/CANL are not swapped
- Verify common ground between nodes
- Reduce cable length and separate from motor wires

### 8.2 Motor Jitter / Resets
- Motor power is insufficient or noisy
- Ensure motor power is external
- Tie grounds together
- Add decoupling near motor driver / servo PSU if needed

### 8.3 UI Updates But No Control
- Confirm 0x200 is transmitted on keypress / pot commit
- Confirm ECU accepts command only in expected mode (if restrictions exist)

---

## 9. Optional: Raspberry Pi Integration (Phase 2+)

The Raspberry Pi can be added later as:
- CAN sniffer/logger
- Fault injector
- Fuzzer interface (using the second CAN adapter)

This is not required for MVP bring-up.



