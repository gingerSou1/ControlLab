#include "protocol.h"

void encodeTelemetry(
    uint8_t *buf,
    uint8_t mode,
    uint8_t target,
    uint8_t actual,
    uint8_t flags,
    uint8_t counter
) {
    buf[0] = mode;
    buf[1] = target;
    buf[2] = actual;
    buf[3] = flags;
    buf[4] = counter;
    buf[5] = buf[0] ^ buf[1] ^ buf[2] ^ buf[3] ^ buf[4]; // simple CRC
    buf[6] = 0;
    buf[7] = 0;
}
