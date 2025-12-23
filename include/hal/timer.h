#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "core.h" // For disableInterrupts / restoreInterrupts

namespace fw::hal {

namespace internal {

// ==================== Timer sources ================= //

struct Timer0Regs {
    using counter_t = uint8_t;
    using compare_t = uint8_t;

    static inline volatile uint8_t& tccra = TCCR0A;
    static inline volatile uint8_t& tccrb = TCCR0B;
    static inline volatile uint8_t& tcnt  = TCNT0;
    static inline volatile uint8_t& ocra  = OCR0A;
    static inline volatile uint8_t& ocrb  = OCR0B;
    static inline volatile uint8_t& timsk = TIMSK0;
    static inline volatile uint8_t& tifr  = TIFR0;
};

struct Timer1Regs {
    using counter_t = uint16_t;
    using compare_t = uint16_t;

    static inline volatile uint8_t& tccra = TCCR1A;
    static inline volatile uint8_t& tccrb = TCCR1B;
    static inline volatile uint8_t& tccrc = TCCR1C;
    static inline volatile uint16_t& tcnt = TCNT1;
    static inline volatile uint16_t& ocra = OCR1A;
    static inline volatile uint16_t& ocrb = OCR1B;
    static inline volatile uint16_t& icr  = ICR1;
    static inline volatile uint8_t& timsk = TIMSK1;
    static inline volatile uint8_t& tifr  = TIFR1;
};

struct Timer2Regs {
    using counter_t = uint8_t;
    using compare_t = uint8_t;

    static inline volatile uint8_t& tccra = TCCR2A;
    static inline volatile uint8_t& tccrb = TCCR2B;
    static inline volatile uint8_t& tcnt  = TCNT2;
    static inline volatile uint8_t& ocra  = OCR2A;
    static inline volatile uint8_t& ocrb  = OCR2B;
    static inline volatile uint8_t& assr  = ASSR;
    static inline volatile uint8_t& timsk = TIMSK2;
    static inline volatile uint8_t& tifr  = TIFR2;
};

// ==================== Timer traits ==================== //

template<typename TimerRegs>
struct TimerTraits;

template<>
struct TimerTraits<Timer0Regs> {
    static constexpr uint8_t wgmbits = 0b111;
    static constexpr uint8_t toie = TOIE0;
    static constexpr bool is16bit = false;
};

template<>
struct TimerTraits<Timer1Regs> {
    static constexpr uint8_t wgmbits = 0b1111;
    static constexpr uint8_t toie = TOIE1;
    static constexpr bool is16bit = true;
};

template<>
struct TimerTraits<Timer2Regs> {
    static constexpr uint8_t wgmbits = 0b111;
    static constexpr uint8_t toie = TOIE2;
    static constexpr bool is16bit = false;
};

// ==================== WGM helpers ==================== //

template<typename Regs>
static void setWGM(uint8_t wgm) {
    if constexpr (!TimerTraits<Regs>::is16bit) {
        Regs::tccra = (Regs::tccra & ~0b11) | (wgm & 0b11);
        Regs::tccrb = (Regs::tccrb & ~(1 << 3)) | ((wgm >> 2) << 3);
    } else {
        Regs::tccra = (Regs::tccra & ~0b11) | (wgm & 0b11);
        Regs::tccrb = (Regs::tccrb & ~((1<<4)|(1<<3))) | ((wgm & 0b1100) << 1);
    }
}

// Predefined modes
struct Timer0Modes { static constexpr uint8_t normal = 0b000, ctc = 0b010, fastPWM = 0b011; };
struct Timer1Modes { static constexpr uint8_t normal = 0b0000, ctc = 0b0100, fastPWM = 0b1110, phaseCorrectPWM = 0b1000; };
struct Timer2Modes { static constexpr uint8_t normal = 0b000, ctc = 0b010, fastPWM = 0b011; };

} // namespace internal

// ==================== Generic timer interface ==================== //

template<typename Regs, typename Regs::counter_t<Regs> StartTick = 0, uint16_t Prescaler = 64, uint8_t Mode = 0,
         typename Regs::compare_t CompareA = 0, typename Regs::compare_t CompareB = 0>
struct Timer {
    using counter_t = typename Regs::counter_t;
    using compare_t = typename Regs::compare_t;

    static void configure() {
        internal::setWGM<Regs>(Mode);
        write(StartTick);
        setCompareA(CompareA);
        setCompareB(CompareB);
        enableOverflowInterrupt();
        start(Prescaler);
    }

    static uint8_t prescalerBits(uint16_t prescaler) {
        switch(prescaler) {
            case 1:    return 0b001;
            case 8:    return 0b010;
            case 64:   return 0b011;
            case 256:  return 0b100;
            case 1024: return 0b101;
            default:   return 0;
        }
    }

    static void start(uint16_t prescaler = Prescaler) {
        stop();
        fw::hal::disableInterrupts();
        Regs::tccrb |= prescalerBits(prescaler);
        fw::hal::restoreInterrupts();
    }

    static void stop() {
        fw::hal::disableInterrupts();
        Regs::tccrb &= ~0x07;
        fw::hal::restoreInterrupts();
    }

    static auto read() {
        fw::hal::disableInterrupts();
        auto value = Regs::tcnt;
        fw::hal::restoreInterrupts();
        return value;
    }

    static void write(counter_t<Regs> value = StartTick) {
        fw::hal::disableInterrupts();
        Regs::tcnt = value;
        fw::hal::restoreInterrupts();
    }

    static void setCompareA(compare_t<Regs> value) { Regs::ocra = value; }
    static void setCompareB(compare_t<Regs> value) { Regs::ocrb = value; }

    static void enableOverflowInterrupt() {
        fw::hal::disableInterrupts();
        Regs::timsk |= (1 << internal::TimerTraits<Regs>::toie);
        fw::hal::restoreInterrupts();
    }

    static void disableOverflowInterrupt() {
        fw::hal::disableInterrupts();
        Regs::timsk &= ~(1 << internal::TimerTraits<Regs>::toie);
        fw::hal::restoreInterrupts();
    }
};

} // namespace fw::hal

#endif // TIMER_H