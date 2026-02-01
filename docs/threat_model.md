# Threat Model

This document outlines the threat model for the Hybrid Control Lab.

---

## Assets

- Physical actuator safety
- Integrity of control logic
- Correct alerting and CAS behavior
- Configuration and maintenance data

---

## Attacker Profile

- Has physical or logical access to the CAN bus
- Can observe and inject CAN frames
- May access maintenance interfaces
- Does NOT have firmware flashing access by default

---

## Trust Assumptions

- Control Head is trusted during normal operation
- ECU firmware is static and trusted
- CAN bus has no built-in authentication
- Maintenance services enforce access control (imperfectly)

---

## Attack Surfaces

| Surface | Description |
|------|------------|
| CAN Bus | Frame spoofing, flooding, replay |
| Maintenance Services | Auth bypass, parser flaws |
| Mode Logic | State confusion, race conditions |
| Setpoint Validation | Bounds and unit errors |

---

## Security Objectives

- Prevent unsafe actuator behavior in NORMAL mode
- Ensure alerts cannot be suppressed incorrectly
- Detect degraded or faulted states
- Log security-relevant events
