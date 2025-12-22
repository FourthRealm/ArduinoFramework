#ifndef PIN_IO_H
#define PIN_IO_H

#include <avr/io.h>

#include "stdint.h"

namespace fw::hal {

// ==================== Pin Port Definitions ================= //

struct PinPortD {
    static inline volatile uint8_t& ddr = DDRD;
    static inline volatile uint8_t& port = PORTD;
    static inline volatile uint8_t& pin = PIND;
};

struct PinPortB {
    static inline volatile uint8_t& ddr = DDRB;
    static inline volatile uint8_t& port = PORTB;
    static inline volatile uint8_t& pin = PINB;
};

struct PinPortC {
    static inline volatile uint8_t& ddr = DDRC;
    static inline volatile uint8_t& port = PORTC;
    static inline volatile uint8_t& pin = PINC;
};

// ==================== Pin Definition Template ================= //

template<typename PinPort, uint8_t PinBit>
struct Pin {
    // Configure the pin as an output
    static void setOutput() {
        PinPort::ddr |= (1 << PinBit);
    }

    // Configure the pin as an input
    static void setInput() {
        PinPort::ddr &= ~(1 << PinBit);
    }

    // Configure the pin as an input with pull-up resistor enabled
    static void setInputPullup() {
        PinPort::ddr &= ~(1 << PinBit);
        PinPort::port |= (1 << PinBit);
    }

    // Set the pin high
    static void high() {
        PinPort::port |= (1 << PinBit);
    }

    // Set the pin low
    static void low() {
        PinPort::port &= ~(1 << PinBit);
    }

    // Toggle the pin state
    static void toggle() {
        PinPort::pin = (1 << PinBit);
    }

    // Read the pin state
    static bool read() {
        return PinPort::pin & (1 << PinBit);
    }
};

} // namespace fw::hal

#endif // PIN_IO_H