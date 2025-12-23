#ifndef SYS_H
#define SYS_H

#include <stdint.h>

namespace fw::sys {
    extern volatile uint64_t tick_count;
}

namespace fw::hal {
    inline void onTimer0Overflow() {
        fw::sys::tick_count++;
    }

    inline void onTimer1Overflow() {

    }
    
    inline void onTimer2Overflow() {

    }
}

#endif // SYS_H