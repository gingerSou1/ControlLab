# CAN Protocol Specification

This document defines the CAN message format used between the Control Head and
ECU.

---

## General Properties

- Standard 11-bit CAN identifiers
- Little-endian payload encoding
- Periodic telemetry + event-driven commands
- No cryptographic authentication (intentional)

---

## Message ID Map

| ID (hex) | Direction | Description |
|--------|----------|------------|
| 0x100 | ECU → CH | Telemetry status |
| 0x110 | ECU → CH | Alert / CAS message |
| 0x200 | CH → ECU | Operator command |
| 0x210 | CH → ECU | Setpoint update |
| 0x700 | CH → ECU | Maintenance service |
| 0x710 | ECU → CH | Maintenance response |

---

## Telemetry Status (0x100)

| Byte | Field | Description |
|----|------|------------|
| 0 | Mode | Current operating mode |
| 1 | Actuator % | Commanded output (0–100) |
| 2 | Feedback % | Measured output |
| 3 | Flags | Status bitfield |
| 4 | Counter | Rolling message counter |
| 5 | CRC | Simple checksum |
| 6–7 | Reserved | Future use |

---

## Operator Command (0x200)

| Byte | Field | Description |
|----|------|------------|
| 0 | Command ID | Enable / Disable / Mode change |
| 1 | Argument | Command-specific |
| 2 | Counter | Rolling counter |
| 3 | CRC | Checksum |
| 4–7 | Reserved | Unused |

---

## Maintenance Service (0x700)

Maintenance messages provide access to diagnostic and configuration services.
These services are **restricted by mode**, but intentionally weak for testing.

