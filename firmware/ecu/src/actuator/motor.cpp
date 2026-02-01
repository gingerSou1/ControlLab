#include <Arduino.h>
#include <Servo.h>

static Servo motor;

void motorInit(int pin) {
    motor.attach(pin);
    motor.write(0); // safe state
}

void motorSetPercent(uint8_t pct) {
    uint8_t angle = map(pct, 0, 100, 0, 180);
    motor.write(angle);
}
