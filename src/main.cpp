#define FW_BOARD_UNO
#include "fw.h"

#include <avr/io.h>
#include <avr/interrupt.h>

// volatile uint32_t system_ms = 0;

// ISR(TIMER1_COMPA_vect) {
//     system_ms++;
// }

// void setup_timer1() {
//     TCCR1A = 0;
//     TCCR1B = (1 << WGM12); // CTC mode
//     OCR1A = 249; // 16 MHz / 64 / 1000 - 1
//     TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler 64
//     TIMSK1 |= (1 << OCIE1A); // enable compare interrupt
// }

volatile uint8_t button_event = 0;
void buttonEvent() {
    button_event = 1;
}

int main() {
    // setup_timer1();
 
    using LED = fw::board::PinD12;
    LED::setOutput();
    LED::high();
    
    using BUTTON = fw::board::PinD2;
    BUTTON::setInputPullup();

    using BUTTON_EVENT = fw::hal::ExternalInterrupt<fw::hal::Interrupt0, buttonEvent>;
    BUTTON_EVENT::init(fw::hal::Trigger::FALLING);

    sei();

    while(true) {
        if(button_event) {
            button_event = 0;
            LED::toggle();
        }
    }
}