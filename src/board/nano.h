#ifndef NANO_H
#define NANO_H

#include "fw.h"

namespace fw::board {

// Port D (Pins D0 - D7)
using PinRX  = fw::hal::Pin<fw::hal::PortD, 0>;
using PinTX  = fw::hal::Pin<fw::hal::PortD, 1>;
using PinD2  = fw::hal::Pin<fw::hal::PortD, 2>;
using PinD3  = fw::hal::Pin<fw::hal::PortD, 3>;
using PinD4  = fw::hal::Pin<fw::hal::PortD, 4>;
using PinD5  = fw::hal::Pin<fw::hal::PortD, 5>;
using PinD6  = fw::hal::Pin<fw::hal::PortD, 6>;
using PinD7  = fw::hal::Pin<fw::hal::PortD, 7>;

// Port B (Pins D8 - D13)
using PinD8  = fw::hal::Pin<fw::hal::PortB, 0>;
using PinD9  = fw::hal::Pin<fw::hal::PortB, 1>;
using PinD10 = fw::hal::Pin<fw::hal::PortB, 2>;
using PinD11 = fw::hal::Pin<fw::hal::PortB, 3>;
using PinD12 = fw::hal::Pin<fw::hal::PortB, 4>;
using PinD13 = fw::hal::Pin<fw::hal::PortB, 5>;

// Port C (Analog Pins A0 - A7)
using PinA0  = fw::hal::Pin<fw::hal::PortC, 0>;
using PinA1  = fw::hal::Pin<fw::hal::PortC, 1>;
using PinA2  = fw::hal::Pin<fw::hal::PortC, 2>;
using PinA3  = fw::hal::Pin<fw::hal::PortC, 3>;
using PinA4  = fw::hal::Pin<fw::hal::PortC, 4>; // SDA
using PinA5  = fw::hal::Pin<fw::hal::PortC, 5>; // SCL
using PinA6  = fw::hal::Pin<fw::hal::PortC, 6>; // only on Nano, used as analog input
using PinA7  = fw::hal::Pin<fw::hal::PortC, 7>; // only on Nano, used as analog input

} // namespace fw::board

#endif // NANO_H