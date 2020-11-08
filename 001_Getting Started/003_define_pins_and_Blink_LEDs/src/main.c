/* 

Define pins and Blink LEDs by AVR c 

Developed by: Walid Amriou
Last update: November 2020

*/

#include <avr/io.h> // Defines pins, ports, etc 
#include <util/delay.h> // Functions to waste time

#define Arduino_GPIN_8  (1<<0)
#define Arduino_GPIN_9  (1<<1)
#define Arduino_GPIN_10 (1<<2)
#define Arduino_GPIN_11 (1<<3)
#define Arduino_GPIN_12 (1<<4)
#define Arduino_GPIN_13 (1<<5)

int main(void) {
    // We use the register DDRB to direct the port "B" pins, and DDRB is the Data Direction 
    // register for port “B”. This means that if you set this register to 0xFF (by running 
    // DDRB |= 0xFF ), all ports or pins in the “B” I/O port act as outputs. If you set DDRB 
    // to 0x00 (it’s initialized to 0x00 by default), then ports or pins in the “B” I/O port 
    // act as inputs. on general: DDRx data-direction registers (port x).
    // Note that the default state with of all the pins is "input mode".
    // For our example we set the pins PB0 and PB1 as output so our code is 0b00000011
    // we can set by DDRB |= 0b00000011;   or we can:
    DDRB |= Arduino_GPIN_8; // for PB0, and it means DDRB = DDRB | 0b00000001 
    DDRB |= Arduino_GPIN_9; // for PB1, and it means DDRB = DDRB | 0b00000010
    DDRB |= Arduino_GPIN_10; // for PB2, and it means DDRB = DDRB | 0b00000100
    DDRB |= Arduino_GPIN_11; // for PB3, and it means DDRB = DDRB | 0b00001000
    DDRB |= Arduino_GPIN_12; // for PB4, and it means DDRB = DDRB | 0b00010000
    DDRB |= Arduino_GPIN_13; // for PB5, and it means DDRB = DDRB | 0b00100000
    // we use bitwise OR operation when we need to turn on or off a particular LED 
    // without disturbing any of the others.
    
    while (1) {
        PORTB = Arduino_GPIN_8; // set pin8 to high
        _delay_ms(500);
        PORTB &= Arduino_GPIN_8; // clear pin8 to low

        PORTB = Arduino_GPIN_9; // set pin9 to high
        _delay_ms(500);
        PORTB &= Arduino_GPIN_9; // clear pin9 to low
 
        PORTB = Arduino_GPIN_10; // set pin10 to high
        _delay_ms(500);
        PORTB &= Arduino_GPIN_10; // clear pin10 to low

        PORTB = Arduino_GPIN_11; // set pin11 to high
        _delay_ms(500); 
        PORTB &= Arduino_GPIN_11; // clear pin11 to low

        PORTB = Arduino_GPIN_12; // set pin12 to high
        _delay_ms(500);
        PORTB &= Arduino_GPIN_12; // clear pin12 to low

        PORTB = Arduino_GPIN_13; // set pin13 to high
        _delay_ms(500);
        PORTB &= Arduino_GPIN_13; // clear pin13 to low

    } 
    
    return (0); // This line is never reached 
}