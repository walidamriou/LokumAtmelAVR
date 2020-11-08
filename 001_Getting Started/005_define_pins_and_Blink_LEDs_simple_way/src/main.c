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
    int i=0;
    while(i<7){
        DDRB |= (1<<i); 
        i++;
    }
    while (1) {
        PORTB |= Arduino_GPIN_8 | Arduino_GPIN_9 | Arduino_GPIN_10 | Arduino_GPIN_11 | Arduino_GPIN_12 | Arduino_GPIN_13; // set pin8 to high
        _delay_ms(500);
        PORTB = 0x00; // clear pin8 to low
        _delay_ms(500);

    } 
    
    return (0); // This line is never reached 
}