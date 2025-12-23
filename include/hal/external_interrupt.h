#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <avr/interrupt.h>
#include <stdint.h>
#include "core.h"

namespace fw::hal {

namespace internal {

// ==================== External Interrupt Sources ================= //

struct Interrupt0 {
    static inline volatile uint8_t& eimsk = EIMSK;
    static constexpr uint8_t eimskBit = INT0;

    static inline volatile uint8_t& eicra = EICRA;
    static constexpr uint8_t eicraBit0 = ISC00;
    static constexpr uint8_t eicraBit1 = ISC01;
};

struct Interrupt1 {
    static inline volatile uint8_t& eimsk = EIMSK;
    static constexpr uint8_t eimskBit = INT1;

    static inline volatile uint8_t& eicra = EICRA;
    static constexpr uint8_t eicraBit0 = ISC10;
    static constexpr uint8_t eicraBit1 = ISC11;
};

// ==================== External Interrupt Base ================= //

template<typename Source>
struct ExternalInterruptBase {
    using Callback = void(*)();
    static Callback callback;
};

// Initialize static member
template<typename Source>
typename ExternalInterruptBase<Source>::Callback ExternalInterruptBase<Source>::callback = nullptr;

} // namespace internal

// ==================== External Interrupt Template ================= //

template<typename Source>
struct ExternalInterrupt : internal::ExternalInterruptBase<Source> {

    enum class Trigger { RISING, FALLING, CHANGE };

    // Configure the trigger type
    static void configureTrigger(Trigger t) {
        uint8_t mask = 0;
        switch(t) {
            case Trigger::RISING:  mask = (1 << Source::eicraBit0) | (1 << Source::eicraBit1); break;
            case Trigger::FALLING: mask = (1 << Source::eicraBit1); break;
            case Trigger::CHANGE:  mask = (1 << Source::eicraBit0); break;
        }

        fw::hal::disableInterrupts();

        // Clear previous bits and set new mask
        Source::eicra = (Source::eicra & ~((1 << Source::eicraBit0) | (1 << Source::eicraBit1))) | mask;

        fw::hal::restoreInterrupts();
    }

    // Attach a callback and enable the interrupt
    static void attach(typename internal::ExternalInterruptBase<Source>::Callback cb = nullptr) {
        internal::ExternalInterruptBase<Source>::callback = cb;

        fw::hal::disableInterrupts();

        EIFR |= (1 << Source::eimskBit);   // Clear any pending interrupt
        Source::eimsk |= (1 << Source::eimskBit); // Enable interrupt

        fw::hal::restoreInterrupts();
    }

    // Detach the interrupt
    static void detach() {
        fw::hal::disableInterrupts();
        Source::eimsk &= ~(1 << Source::eimskBit);
        fw::hal::restoreInterrupts();
    }
};

} // namespace fw::hal

#endif // INTERRUPT_H