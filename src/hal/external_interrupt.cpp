#include "hal/external_interrupt.h"

namespace fw::hal::internal {

// ==================== ISR Definitions ================= //

ISR(INT0_vect) {
    if(ExternalInterruptBase<Interrupt0>::callback)
        ExternalInterruptBase<Interrupt0>::callback();
}

ISR(INT1_vect) {
    if(ExternalInterruptBase<Interrupt1>::callback)
        ExternalInterruptBase<Interrupt1>::callback();   
}

}