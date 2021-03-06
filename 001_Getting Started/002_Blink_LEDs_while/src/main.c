/* 

Blink LEDs by while by AVR c 

Developed by: Walid Amriou
Last update: November 2020

*/

#include <avr/io.h> // Defines pins, ports, etc 
#include <util/delay.h> // Functions to waste time

void control_leds( uint8_t data_byte){
    PORTB = data_byte;
    _delay_ms(1000);
}

int main(void) {
    // We use the register DDRB to direct the port "B" pins, and DDRB is the Data Direction 
    // register for port “B”. This means that if you set this register to 0xFF (by running 
    // DDRB |= 0xFF ), all ports or pins in the “B” I/O port act as outputs. If you set DDRB 
    // to 0x00 (it’s initialized to 0x00 by default), then ports or pins in the “B” I/O port 
    // act as inputs. on general: DDRx data-direction registers (port x).
    // Note that the default state with of all the pins is "input mode".
    // For our example we set the pins PB0 and PB1 as output so our code is 0b00000011
    // we can set by DDRB |= 0b00000011;   or we can:
    DDRB |= (1<<0); // for PB0, and it means DDRB = DDRB | 0b00000001 
    DDRB |= (1<<1); // for PB1, and it means DDRB = DDRB | 0b00000010
    DDRB |= (1<<2); // for PB2, and it means DDRB = DDRB | 0b00000100
    DDRB |= (1<<3); // for PB3, and it means DDRB = DDRB | 0b00001000
    DDRB |= (1<<4); // for PB4, and it means DDRB = DDRB | 0b00010000
    DDRB |= (1<<5); // for PB5, and it means DDRB = DDRB | 0b00100000
    // we can't do DDRB |= 0xFF because when we use arduino uno board the pins PB7 and PB8 used for crystal
    // we use bitwise OR operation when we need to turn on or off a particular LED 
    // without disturbing any of the others.
    
    int i=0;
    while (1) {
        while(i<6){
            PORTB|= (1<<i);
            _delay_ms(500);
            PORTB=0x00;
            i++;
        }
        i=0;
    } 
    
    return (0); // This line is never reached 
}