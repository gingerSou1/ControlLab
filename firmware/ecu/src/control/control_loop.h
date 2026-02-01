#pragma once
#include <stdint.h>

struct ControlState {
    uint8_t mode;
    uint8_t target_output;
    uint8_t actual_output;
};
