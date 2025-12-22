#ifndef PIN_IO_H
#define PIN_IO_H

#define __AVR_ATmega328P__
#include <avr/io.h>

#include <cstdint>

namespace fw::hal {

struct PortD {
    static inline volatile uint8_t& ddr = DDRD;
    static inline volatile uint8_t& port = PORTD;
    static inline volatile uint8_t& pin = PIND;
};

struct PortB {
    static inline volatile uint8_t& ddr = DDRB;
    static inline volatile uint8_t& port = PORTB;
    static inline volatile uint8_t& pin = PINB;
};

struct PortC {
    static inline volatile uint8_t& ddr = DDRC;
    static inline volatile uint8_t& port = PORTC;
    static inline volatile uint8_t& pin = PINC;
};

template<typename Port, uint8_t Pin>
struct Pin {
    // Configure the pin as an output
    static void setOutput() {
        Port::ddr |= (1 << Pin);
    }

    // Configure the pin as an input
    static void setInput() {
        Port::ddr &= ~(1 << Pin);
    }

    // Configure the pin as an input with pull-up resistor enabled
    static void setInputPullup() {
        Port::ddr &= ~(1 << Pin);
        Port::port |= (1 << Pin);
    }

    // Set the pin high
    static void high() {
        Port::port |= (1 << Pin);
    }

    // Set the pin low
    static void low() {
        Port::port &= ~(1 << Pin);
    }

    // Toggle the pin state
    static void toggle() {
        Port::port ^= (1 << Pin);
    }

    // Read the pin state
    static bool read() {
        return Port::pin & (1 << Pin);
    }
};

} // namespace fw::hal

#endif // PIN_IO_H