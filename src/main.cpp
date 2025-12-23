#define FW_BOARD_UNO
#include <fw.h>

volatile uint8_t button_event = 0;
void buttonEvent() {
    button_event = 1;
}

uint64_t getTicks() {
    cli();
    uint64_t ticks = fw::sys::tick_count;
    sei();
    return ticks;
}

int main() { 
    // Initialize components

    using LED = fw::board::PinD12;
    LED::setOutput();
    LED::high();
    
    using BUTTON = fw::board::PinD2;
    BUTTON::setInputPullup();

    using BUTTON_INTERRUPT = fw::board::Interrupt0;
    BUTTON_INTERRUPT::configureTrigger(fw::hal::Trigger::FALLING);
    BUTTON_INTERRUPT::attach(buttonEvent);

    // Setup timers

    fw::board::Timer0::configure(fw::hal::Timer0Modes::normal, 64);

    sei();

    bool isLedOn = true;
    while(true) {
        if(button_event) {
            button_event = 0;
            isLedOn = !isLedOn;
        }

        if(isLedOn) {
            if(getTicks() % 1000 < 500)
                LED::high();
            else
                LED::low();
        } 
        else
            LED::low();
    }
}