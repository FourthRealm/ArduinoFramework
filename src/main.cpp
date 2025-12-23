#define FW_BOARD_UNO
#include <fw.h>

using namespace fw;

volatile bool stop = false;
void onButton() {
    stop = true;
}

inline bool getStop() {
    hal::InterruptState state = hal::disableInterrupts();
    bool storedStop = stop;
    hal::restoreInterruptState(state);
    return storedStop;
}

int main() { 
    using LED_A = board::PinD3;
    LED_A::setOutput();
    LED_A::high();
    
    using BUTTON = board::PinD2;
    BUTTON::setInputPullup();

    using BUTTON_INTERRUPT = board::Interrupt0;
    BUTTON_INTERRUPT::configureTrigger(board::InterruptTrigger::FALLING);
    BUTTON_INTERRUPT::attach(onButton);

    board::MillisTimer::configure();

    hal::enableInterrupts();


    uint32_t millis;
    while(true) {
        sys::millis(millis);
        millis %= 1000;

        if(millis > 500) {
            LED_A::high();
        }
        else {
            LED_A::low();
        }

        if(getStop() == true) {
            LED_A::low();
            while(true) {}
        }
    }
}