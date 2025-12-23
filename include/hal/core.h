#ifndef CORE_H
#define CORE_H

#include <stdint.h>
#include <avr/interrupt.h>

namespace fw::hal {

using InterruptState = uint8_t;

inline bool interruptsEnabled() {
    return ((SREG & (1 << 7)) != 0);
}

inline void restoreInterruptState(InterruptState state) {
    SREG = state;
}

inline void enableInterrupts() {
    sei();
}

[[nodiscard]] inline InterruptState disableInterrupts() {
    InterruptState state = SREG;
    cli();
    return state;
}

}

#endif // CORE_H