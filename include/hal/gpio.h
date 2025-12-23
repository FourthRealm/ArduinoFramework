#ifndef PIN_IO_H
#define PIN_IO_H

#include <avr/io.h>
#include "stdint.h"

namespace fw::hal {

// ==================== Pin Port Definitions ================= //

struct PinPortD {
    static inline volatile uint8_t& ddr = DDRD; // Data Direction Register
    static inline volatile uint8_t& port = PORTD; // Data Register
    static inline volatile uint8_t& pin = PIND; // Input Pins Register
};

struct PinPortB {
    static inline volatile uint8_t& ddr = DDRB; // Data Direction Register
    static inline volatile uint8_t& port = PORTB; // Data Register
    static inline volatile uint8_t& pin = PINB; // Input Pins Register
};

struct PinPortC {
    static inline volatile uint8_t& ddr = DDRC; // Data Direction Register
    static inline volatile uint8_t& port = PORTC; // Data Register
    static inline volatile uint8_t& pin = PINC; // Input Pins Register
};

// ==================== Pin Definition Template ================= //

template<typename PinPort, uint8_t PinBit>
struct Pin {
    static_assert(PinBit < 8, "Pin bit must be 0-7");

    // Constant values evaluated at compile time
    static constexpr uint8_t bit = PinBit;
    static constexpr uint8_t mask = uint8_t(1) << PinBit;
    static inline volatile uint8_t& ddr = PinPort::ddr;
    static inline volatile uint8_t& port = PinPort::port;
    static inline volatile uint8_t& pin = PinPort::pin;

    // Configure the pin as an output
    inline static void setOutput() {
        PinPort::ddr |= mask;
    }

    // Configure the pin as an input
    inline static void setInput() {
        PinPort::ddr &= ~mask;
    }

    // Configure the pin as an input with pull-up resistor enabled
    inline static void setInputPullup() {
        PinPort::ddr &= ~mask;
        PinPort::port |= mask;
    }

    // Set the pin high
    inline static void high() {
        PinPort::port |= mask;
    }

    // Set the pin low
    inline static void low() {
        PinPort::port &= ~mask;
    }

    // Toggle the pin state
    inline static void toggle() {
        PinPort::pin = mask;
    }

    // Read the pin state
    inline static bool read() {
        return PinPort::pin & mask;
    }
};

} // namespace fw::hal

#endif // PIN_IO_H