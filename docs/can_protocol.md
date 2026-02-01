# CAN Protocol Specification

This document defines the CAN message format used between the Control Head (CH)
and the Electronic Control Unit (ECU).

---

## Scope

This protocol supports a hybrid safety-critical control system with distinct
phases of implementation. An explicit **Minimum Viable Protocol (MVP)** is
defined to enable early bring-up and testing.

---

## General Properties

- Standard 11-bit CAN identifiers
- Little-endian payload encoding
- Periodic telemetry + event-driven commands
- No cryptographic authentication (intentional)

---

## MVP Message Set (Phase 1)

The following messages constitute the **Minimum Viable Protocol (MVP)** required
for initial system bring-up.

### MVP Message Summary

| ID (hex) | Direction | Name |
|--------|-----------|------|
| 0x100 | ECU → CH | Telemetry Status |
| 0x110 | ECU → CH | Alert / CAS |
| 0x200 | CH → ECU | Operator Command |

Only these messages are required for Phase 1 firmware development.

---

## Message ID Map (All Phases)

| ID (hex) | Direction | Description |
|--------|----------|------------|
| 0x100 | ECU → CH | Telemetry status |
| 0x110 | ECU → CH | Alert / CAS message |
| 0x200 | CH → ECU | Operator command |
| 0x210 | CH → ECU | Setpoint update (Phase 2) |
| 0x700 | CH → ECU | Maintenance service (Phase 2) |
| 0x710 | ECU → CH | Maintenance response (Phase 2) |

---

## 0x100 – Telemetry Status (MVP)

Sent periodically by the ECU to report system state.

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

## 0x110 – Alert / CAS Message (MVP)

Sent by the ECU when an alert condition occurs.

| Byte | Field | Description |
|----|------|------------|
| 0 | Severity | INFO / CAUTION / WARNING |
| 1 | Alert Code | Subsystem-specific |
| 2 | Latch | 1 = latched, 0 = transient |
| 3 | Counter | Rolling counter |
| 4 | CRC | Checksum |
| 5–7 | Reserved | Unused |

---

## 0x200 – Operator Command (MVP)

Sent by the Control Head to command system behavior.

| Byte | Field | Description |
|----|------|------------|
| 0 | Command ID | Mode set / enable / disable |
| 1 | Argument | Command-specific |
| 2 | Counter | Rolling counter |
| 3 | CRC | Checksum |
| 4–7 | Reserved | Unused |

---

## Phase 2+ Messages

### 0x210 – Setpoint Update
Dedicated setpoint update message for higher-resolution control.

### 0x700 / 0x710 – Maintenance Services
Diagnostic and configuration services available in MAINT mode.
These services are intentionally weakly protected for security testing.

---

## Notes

- CRC and counters are advisory and may be bypassed or weakened in challenge
  scenarios.
- The ECU is the final authority on actuator commands.
