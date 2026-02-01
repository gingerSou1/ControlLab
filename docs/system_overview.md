# System Overview

This project implements a **hybrid safety-critical control system** inspired by
both avionics display units and industrial control systems (ICS).

The system consists of a standalone **Control Head** with integrated display
and physical inputs, a remote **Electronic Control Unit (ECU)** responsible for
real-time control and safety enforcement, and an optional **Engineering /
Security Workstation** used for diagnostics and testing.

The platform is intentionally designed to support **fault injection, protocol
fuzzing, and adversarial testing** while remaining fully functional as a control
system.

---

## System Goals

- Provide a realistic embedded control architecture
- Separate UI, control logic, and actuation
- Implement modes, alerts, and maintenance workflows
- Enable security testing at the protocol and logic level

---

## High-Level Components

| Component | Description |
|--------|------------|
| Control Head | User-facing interface with display, keypad, and analog input |
| ECU | Executes control logic, enforces safety interlocks, drives actuator |
| CAN Bus | Primary command and telemetry transport |
| Engineering Workstation | Logging, fault injection, fuzzing, analysis |

---

## Operating Modes

- **NORMAL** – Automatic control with safety enforcement
- **MANUAL** – Direct operator control with limits
- **MAINT** – Maintenance and diagnostic access
- **TEST/BIT** – Built-In Test and validation routines
