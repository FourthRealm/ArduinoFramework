#include "hal/hal.h"

namespace fw::hal::internal {

// ==================== ISR defenitions ==================== //

ISR(TIMER0_OVF_vect) {
    internal::onTimer0Overflow();
}

ISR(TIMER1_OVF_vect) {
    onTimer1Overflow();
}

ISR(TIMER2_OVF_vect) {
    onTimer2Overflow();
}

}