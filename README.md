# Hybrid Control Lab

A safety-critical hybrid **avionics / industrial control** testbed featuring a
standalone control head with integrated display, keypad, and analog input,
interfacing with a remote ECU over CAN to command a physical actuator.

The system is designed both as a **functional embedded control platform** and
as a **security testing lab** supporting fault injection, protocol fuzzing,
and CTF-style challenges.

---

## Architecture

- **Control Head**
  - Integrated TFT display
  - Keypad + analog setpoint input
  - Maintenance & BIT interface
  - CAN bus client

- **ECU**
  - Real-time control loop
  - Safety interlocks
  - Actuator control (motor)
  - Diagnostic services

- **Engineering / Attack Workstation**
  - CAN sniffing & injection
  - Fuzzing harness
  - Log analysis

---

## Features

- Mode-based operation (NORMAL / MANUAL / MAINT)
- CAS (Caution & Warning) system
- Maintenance services & BIT
- Physical actuator integration
- Fault injection & fuzzing support
- CTF-style challenge scenarios

---

## Hardware

- Raspberry Pi 5
- Arduino Uno R4 WiFi
- HackerBox MCU Lab input panel
- CAN transceivers
- Servo or DC motor actuator

---

## Repository Layout

See [`docs/architecture.md`](docs/architecture.md) for system design details.

---

## Disclaimer

This project is for **educational and research purposes only**.
Do not deploy in real safety-critical environments.
