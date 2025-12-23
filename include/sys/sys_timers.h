#ifndef SYS_TIMERS_H
#define SYS_TIMERS_H

#include <stdint.h>
#include "hal/hal.h"

namespace fw::sys {
    extern volatile uint32_t tickCountLow;
    extern volatile uint32_t tickCountHigh;

    extern volatile uint32_t microsCountLow;
    extern volatile uint32_t microsCountHigh;

    extern volatile uint32_t millisCountLow;
    extern volatile uint32_t millisCountHigh;

    inline void ticks(uint32_t* outLow, uint32_t* outHigh = nullptr) {
        uint8_t lastState = fw::hal::disableInterrupts();
        *outLow = tickCountLow;
        if(outHigh) *outHigh = tickCountHigh;
        fw::hal::restoreLastInterruptState(lastState);
    }

    inline void micros(uint32_t* outLow, uint32_t* outHigh = nullptr) {
        uint8_t lastState = fw::hal::disableInterrupts();
        *outLow = microsCountLow;
        if(outHigh) *outHigh = microsCountHigh;
        fw::hal::restoreLastInterruptState(lastState);
    }

    inline void millis(uint32_t* outLow, uint32_t* outHigh = nullptr) {
        uint8_t lastState = fw::hal::disableInterrupts();
        *outLow = millisCountLow;
        if(outHigh) *outHigh = millisCountHigh;
        fw::hal::restoreLastInterruptState(lastState);
    }
}

#endif // SYS_TIMERS_H