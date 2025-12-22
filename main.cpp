#define FW_BOARD_UNO
#include "fw.h"

#include <util/delay.h>

using namespace fw;

using Led = board::PinD13;

int main() {
    Led::setOutput();

    while(true) {
        Led::high();
        _delay_ms(500);
        Led::low();
        _delay_ms(500);
    }
}