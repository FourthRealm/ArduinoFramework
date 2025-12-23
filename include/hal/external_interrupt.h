#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <avr/interrupt.h>
#include <stdint.h>

namespace fw::hal {

// ==================== External Interrupt Sources ================= //

struct Interrupt0 {
    static inline volatile uint8_t& eimsk = EIMSK;
    static inline uint8_t eimskBit = INT0;

    static inline volatile uint8_t& eicra = EICRA;
    static inline uint8_t eicraBit0 = ISC00;
    static inline uint8_t eicraBit1 = ISC01;
};

struct Interrupt1 {
    static inline volatile uint8_t& eimsk = EIMSK;
    static inline uint8_t eimskBit = INT1;

    static inline volatile uint8_t& eicra = EICRA;
    static inline uint8_t eicraBit0 = ISC10;
    static inline uint8_t eicraBit1 = ISC11;
};


// ==================== External Interrupt Template ================= //

// Trigger enum for all interrupt conditions
enum class Trigger { LOW, RISING, FALLING, CHANGE };

// Base class to hold the callback
template<typename Source>
struct ExternalInterruptBase {
    static void (*callback)();
};

// Define callback
using Callback = void(*)();

// Initialize static member as nullptr by default
template<typename Source>
void (*ExternalInterruptBase<Source>::callback)() = nullptr;

// External Interrupt class template
template<typename Source>
struct ExternalInterrupt : ExternalInterruptBase<Source> {
    // Enables interrupt
    static void configureTrigger(Trigger t) {
        // Calculate the bitmask
        uint8_t mask = 0;
        switch(t) {
            case Trigger::RISING:  mask = (1 << Source::eicraBit0) | (1 << Source::eicraBit1); break;
            case Trigger::FALLING: mask = (1 << Source::eicraBit1); break;
            case Trigger::CHANGE:  mask = (1 << Source::eicraBit0); break;
            case Trigger::LOW:     mask = 0; break;
        }

        // Clear bits
        Source::eicra &= ~((1 << Source::eicraBit0) | (1 << Source::eicraBit1));

        // Set correct trigger
        Source::eicra |= mask;
    }

    // Turn on the interrupt.
    static void attach(Callback callback = nullptr) {
        ExternalInterruptBase<Source>::callback = callback;
        Source::eimsk |= (1 << Source::eimskBit);
    }

    // Turn off the interrupt.
    static void detach() {
        Source::eimsk |= (1 << Source::eimskBit);
    }
};


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

#endif // INTERRUPT_H