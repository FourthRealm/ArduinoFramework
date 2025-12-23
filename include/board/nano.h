#ifndef NANO_H
#define NANO_H

#include "hal/hal.h"

namespace fw::board {

// =================== Pin Definitions ================= //

// Port D (Pins D0 - D7)
using PinRX  = fw::hal::Pin<fw::hal::internal::PinPortD, 0>;
using PinTX  = fw::hal::Pin<fw::hal::internal::PinPortD, 1>;
using PinD2  = fw::hal::Pin<fw::hal::internal::PinPortD, 2>;
using PinD3  = fw::hal::Pin<fw::hal::internal::PinPortD, 3>;
using PinD4  = fw::hal::Pin<fw::hal::internal::PinPortD, 4>;
using PinD5  = fw::hal::Pin<fw::hal::internal::PinPortD, 5>;
using PinD6  = fw::hal::Pin<fw::hal::internal::PinPortD, 6>;
using PinD7  = fw::hal::Pin<fw::hal::internal::PinPortD, 7>;

// Port B (Pins D8 - D13)
using PinD8  = fw::hal::Pin<fw::hal::internal::PinPortB, 0>;
using PinD9  = fw::hal::Pin<fw::hal::internal::PinPortB, 1>;
using PinD10 = fw::hal::Pin<fw::hal::internal::PinPortB, 2>;
using PinD11 = fw::hal::Pin<fw::hal::internal::PinPortB, 3>;
using PinD12 = fw::hal::Pin<fw::hal::internal::PinPortB, 4>;
using PinD13 = fw::hal::Pin<fw::hal::internal::PinPortB, 5>;

// Port C (Analog Pins A0 - A7)
using PinA0  = fw::hal::Pin<fw::hal::internal::PinPortC, 0>;
using PinA1  = fw::hal::Pin<fw::hal::internal::PinPortC, 1>;
using PinA2  = fw::hal::Pin<fw::hal::internal::PinPortC, 2>;
using PinA3  = fw::hal::Pin<fw::hal::internal::PinPortC, 3>;
using PinA4  = fw::hal::Pin<fw::hal::internal::PinPortC, 4>; // SDA
using PinA5  = fw::hal::Pin<fw::hal::internal::PinPortC, 5>; // SCL
using PinA6  = fw::hal::Pin<fw::hal::internal::PinPortC, 6>; // only on Nano
using PinA7  = fw::hal::Pin<fw::hal::internal::PinPortC, 7>; // only on Nano

// =================== Interrupt Definitions =================== //
using Interrupt0 = fw::hal::ExternalInterrupt<fw::hal::internal::Interrupt0>;
using Interrupt1 = fw::hal::ExternalInterrupt<fw::hal::internal::Interrupt1>;

// =================== Timer Definitions =================== //
using CycleTimer  = fw::hal::Timer<fw::hal::internal::Timer0Regs, 0, 0>;
using MicrosTimer = fw::hal::Timer<fw::hal::internal::Timer1Regs, (65536 - 100), 8>;
using MillisTimer = fw::hal::Timer<fw::hal::internal::Timer2Regs, (256 - 250), 64>;

} // namespace fw::board

#endif // NANO_H