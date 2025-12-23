#ifndef SYS_TIMERS_H
#define SYS_TIMERS_H

#include <stdint.h>
#include "hal/hal.h"

namespace fw::sys {
    extern volatile uint32_t tickCount;
    extern volatile uint32_t microsCount;
    extern volatile uint32_t millisCount;

    inline void ticks(uint32_t& outLow) {
        uint8_t lastState = fw::hal::disableInterrupts();
        outLow = tickCount;
        fw::hal::restoreLastInterruptState(lastState);
    }

    inline void micros(uint32_t& outLow) {
        uint8_t lastState = fw::hal::disableInterrupts();
        outLow = microsCount;
        fw::hal::restoreLastInterruptState(lastState);
    }

    inline void millis(uint32_t& outLow) {
        uint8_t lastState = fw::hal::disableInterrupts();
        outLow = millisCount;
        fw::hal::restoreLastInterruptState(lastState);
    }
}

#endif // SYS_TIMERS_H