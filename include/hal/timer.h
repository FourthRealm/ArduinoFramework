#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

namespace fw::hal {

// ==================== Timer sources ================= //

// Registers for Timer0
struct Timer0Regs {
    using counter_t = uint8_t;
    using compare_t = uint8_t;

    static inline volatile uint8_t& tccra = TCCR0A; // Timer/Counter Control Register A
    static inline volatile uint8_t& tccrb = TCCR0B; // Timer/Counter Control Register B
    static inline volatile uint8_t& tcnt = TCNT0;    // Timer/Counter Register
    static inline volatile uint8_t& ocra = OCR0A;   // Output Compare Register A
    static inline volatile uint8_t& ocrb = OCR0B;   // Output Compare Register B
    static inline volatile uint8_t& timsk = TIMSK0; // Timer Interrupt Mask Register
    static inline volatile uint8_t& tifr = TIFR0;   // Timer Interrupt Flag Register
};

// Registers for Timer1
struct Timer1Regs {
    using counter_t = uint16_t;
    using compare_t = uint16_t;

    static inline volatile uint8_t& tccra = TCCR1A; // Timer/Counter Control Register A
    static inline volatile uint8_t& tccrb = TCCR1B; // Timer/Counter Control Register B
    static inline volatile uint8_t& tccrc = TCCR1C; // Timer/Counter Control Register C
    static inline volatile uint16_t& tcnt = TCNT1;   // Timer/Counter Register
    static inline volatile uint16_t& ocra = OCR1A;  // Output Compare Register A
    static inline volatile uint16_t& ocrb = OCR1B;  // Output Compare Register B
    static inline volatile uint16_t& icr = ICR1;    // Input capture register
    static inline volatile uint8_t& timsk = TIMSK1; // Timer Interrupt Mask Register
    static inline volatile uint8_t& tifr = TIFR1;   // Timer Interrupt Flag Register
};

// Registers for Timer2
struct Timer2Regs {
    using counter_t = uint8_t;
    using compare_t = uint8_t;

    static inline volatile uint8_t& tccra = TCCR2A; // Timer/Counter Control Register A
    static inline volatile uint8_t& tccrb = TCCR2B; // Timer/Counter Control Register B
    static inline volatile uint8_t& tcnt = TCNT2;    // Timer/Counter Register
    static inline volatile uint8_t& ocra = OCR2A;   // Output Compare Register A
    static inline volatile uint8_t& ocrb = OCR2B;   // Output Compare Register B
    static inline volatile uint8_t& assr = ASSR;    // Asynchronous Control Register
    static inline volatile uint8_t& timsk = TIMSK2; // Timer Interrupt Mask Register
    static inline volatile uint8_t& tifr = TIFR2;   // Timer Interrupt Flag Register
};

// ==================== Timer traits ==================== //

template<typename TimerRegs>
struct TimerTraits;

// Specialization for Timer0
template<>
struct TimerTraits<Timer0Regs> {
    static constexpr uint8_t wgmbits = 0b111;
    static constexpr uint8_t toie = TOIE0;
    static constexpr bool is16bit = false;
};

// Specialization for Timer1
template<>
struct TimerTraits<Timer1Regs> {
    static constexpr uint8_t wgmbits = 0b1111;
    static constexpr uint8_t toie = TOIE1;
    static constexpr bool is16bit = true;
};

// Specialization for Timer2
template<>
struct TimerTraits<Timer2Regs> {
    static constexpr uint8_t wgmbits = 0b111;
    static constexpr uint8_t toie = TOIE2;
    static constexpr bool is16bit = false;
};

// ==================== Timer WGM Configuration ==================== //

// Set the Waveform Generation Mode (WGM) bits (works for both 8-bit and 16-bit timers)
template<typename Regs>
static void setWGM(uint8_t wgm) {
    if constexpr (!TimerTraits<Regs>::is16bit) {
        // 8-bit timer
        Regs::tccra = (Regs::tccra & ~0b11) | (wgm & 0b11);
        Regs::tccrb = (Regs::tccrb & ~(1 << 3)) | ((wgm >> 2) << 3);        
    }
    else {
        // 16-bit timer
        Regs::tccra = (Regs::tccra & ~0b11) | (wgm & 0b11);
        Regs::tccrb = (Regs::tccrb & ~((1<<4)|(1<<3))) | ((wgm & 0b1100) << 1);
    }
}

// Predefined WGM modes for Timer0
struct Timer0Modes {
    static constexpr uint8_t normal = 0b000;
    static constexpr uint8_t ctc = 0b010;
    static constexpr uint8_t fastPWM = 0b011;
};

// Predefined WGM modes for Timer1
struct Timer1Modes {
    static constexpr uint8_t normal = 0b0000;
    static constexpr uint8_t ctc = 0b0100;
    static constexpr uint8_t fastPWM = 0b1110;
    static constexpr uint8_t phaseCorrectPWM = 0b1000;
};

// Predefined WGM modes for Timer2
struct Timer2Modes {
    static constexpr uint8_t normal = 0b000;
    static constexpr uint8_t ctc = 0b010;
    static constexpr uint8_t fastPWM = 0b011;
};


// ==================== Generic timer interface ==================== //

// Interface for timers
template<typename Regs>
struct Timer {
    using counter_t = typename Regs::counter_t;
    using compare_t = typename Regs::compare_t;

    // Configure the timer with mode, prescaler, and optional compare values.
    static void configure(uint8_t mode, uint8_t prescaler, compare_t compareA = 0, compare_t compareB = 0) {
        setWGM<Regs>(mode);
        write(0);
        setCompareA(0);
        setCompareB(0);
        start(prescaler);
    }

    // Start the timer with the given prescaler. Should call configure first.
    static void start(uint8_t prescaler) {
        stop();
        Regs::tccrb |= prescaler;
    }

    // Stop the timer.
    static void stop() {
        Regs::tccrb &= ~0x07;
    }

    // Direct read of timer counter.
    static auto read() {
        return Regs::tcnt;
    }
    
    // Direct write to timer counter. Use with caution.
    static void write(counter_t value) {
        Regs::tcnt = value;
    }

    // Set Output Compare Register A
    static void setCompareA(compare_t value) {
        Regs::ocra = value;
    }

    // Set Output Compare Register B
    static void setCompareB(compare_t value) {
        Regs::ocrb = value;
    }

    static void enableOverflowInterrupt() {
        Regs::timsk |= (1 << TimerTraits<Regs>::toie);
    }
};

// ==================== ISR Definitions ================= //

ISR(TIMER0_OVF_vect) {
    fw::hal::onTimer0Overflow();
}

ISR(TIMER1_OVF_vect) {
    fw::hal::onTimer1Overflow();
}

ISR(TIMER2_OVF_vect) {
    fw::hal::onTimer2Overflow();
}

} // namespace fw::hal

#endif // TIMER_H