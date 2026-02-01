void handleCommand(uint8_t *data, ControlState &state) {
    uint8_t cmd = data[0];
    uint8_t arg = data[1];

    switch (cmd) {
        case CMD_SET_MODE:
            state.mode = arg;
            break;

        case CMD_SET_OUTPUT:
            if (state.mode == MODE_MANUAL) {
                state.target_output = arg;
            }
            break;

        default:
            break;
    }
}
