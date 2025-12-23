#include "sys/sys_timers.h"
#include "board/board.h"
#include <avr/interrupt.h>

namespace fw::sys {
    volatile uint32_t tickCountLow = 0;
    volatile uint32_t tickCountHigh = 0;
    volatile uint32_t microsCountLow = 0;
    volatile uint32_t microsCountHigh = 0;
    volatile uint32_t millisCountLow = 0;
    volatile uint32_t millisCountHigh = 0;
}

// =================== Timer overflow functions =================== //
namespace fw::hal {
    void onTimer0Overflow() {
        fw::board::CycleTimer::write(/*To overflow value*/);
        fw::sys::tickCountLow += 256;
        if(fw::sys::tickCountLow == 0)
            fw::sys::tickCountHigh++;
    }

    void onTimer1Overflow() {
        fw::board::MicrosTimer::write(/*To overflow value*/);
        fw::sys::microsCountLow += 50;
        if(fw::sys::microsCountLow == 0)
            fw::sys::microsCountHigh++;
    }
    
    void onTimer2Overflow() {
        fw::board::MillisTimer::write(/*To overflow value*/);
        fw::sys::millisCountLow += 1;
        if(fw::sys::millisCountLow == 0)
            fw::sys::millisCountHigh++;
    }

    // ==================== ISR defenitions ==================== //
    
    ISR(TIMER0_OVF_vect) {
        onTimer0Overflow();
    }
    
    ISR(TIMER1_OVF_vect) {
        onTimer1Overflow();
    }
    
    ISR(TIMER2_OVF_vect) {
        onTimer2Overflow();
    }
}
