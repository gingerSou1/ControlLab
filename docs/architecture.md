# System Architecture

This system follows a **distributed control architecture** where user
interaction, control logic, and actuation are separated into independent nodes
connected via a CAN bus.

---

## Block Diagram (Logical)

Control Head
- UI rendering
- Input processing
- Mode selection
- Maintenance interface

        ⇅ CAN Bus

ECU
- Control loop
- Safety interlocks
- Diagnostic services
- Actuator control

        ⇅

Physical Actuator
- Motor (fan / pump / valve analog)

---

## Trust Boundaries

| Boundary | Description |
|-------|------------|
| User Input Boundary | Physical keypad, potentiometer |
| Field Bus Boundary | CAN traffic between nodes |
| Maintenance Boundary | Diagnostic and configuration services |
| Actuation Boundary | Physical motor output |

Each boundary represents a potential attack surface for fault injection or
malicious control.

---

## Design Assumptions

- CAN bus traffic is unauthenticated by default
- ECU is the final authority on actuator commands
- Control Head is trusted for normal operations
- Maintenance interfaces are intentionally exposed for testing
