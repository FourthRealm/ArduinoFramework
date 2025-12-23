#include "sys/sys_timers.h"
#include "board/board.h"
#include <avr/interrupt.h>

namespace fw::sys {
    volatile uint32_t tickCount = 0;
    volatile uint32_t microsCount = 0;
    volatile uint32_t millisCount = 0;
}

// =================== Timer overflow functions =================== //
namespace fw::hal::internal {
    void onTimer0Overflow() {
        fw::board::CycleTimer::write(/*To overflow value*/);
        fw::sys::tickCount += 1;
    }

    void onTimer1Overflow() {
        fw::board::MicrosTimer::write(/*To overflow value*/);
        fw::sys::microsCount += 50;
    }
    
    void onTimer2Overflow() {
        fw::board::MillisTimer::write(/*To overflow value*/);
        fw::sys::millisCount += 1;
    }
}
