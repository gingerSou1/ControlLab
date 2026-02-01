#include "comms/can_iface.h"
#include "control/control_loop.h"
#include "actuator/motor.h"
#include "alerts/cas.h"

ControlState state;
uint8_t tx_counter = 0;
unsigned long last_telemetry = 0;

void setup() {
    state.mode = MODE_NORMAL;
    state.target_output = 0;
    state.actual_output = 0;

    motorInit(9);   // example pin
    canInit();      // your CAN init here
}

void loop() {
    canPoll(state); // RX commands

    if (state.mode == MODE_MANUAL) {
        motorSetPercent(state.target_output);
        state.actual_output = state.target_output;
    } else {
        motorSetPercent(0);
        state.actual_output = 0;
    }

    if (millis() - last_telemetry >= 100) {
        sendTelemetry(state, tx_counter++);
        last_telemetry = millis();
    }
}
