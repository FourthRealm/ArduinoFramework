#define __AVR_ATmega328P__
#include <avr/io.h>
#define F_CPU 16000000UL // For Arduino UNO/Nano running at 16 MHz
#include <util/delay.h>

#define LED_MASK (1 << 4)

int main() {
    DDRD |= LED_MASK;
    PORTD &= ~LED_MASK;

    while(1) {
        _delay_ms(250);
        PORTD ^= LED_MASK;
    }
}