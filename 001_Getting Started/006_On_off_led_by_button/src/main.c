#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

int main(void){
    initUSART();
    
    // Output
    // DDRB to direct the port "B" pins
    DDRB |= (1<<5); 

    // make the LED pin an output for PORTB5
    PORTD |= (1<<2);

    while (1){
        //_delay_ms(500);
        if(bit_is_clear(PIND, PD2)){
            printString("Button press!\r\n");
            PORTB |= (1<<5); // set pin8 to high
        }
        else{
            PORTB &= ~(1<<5); // set pin8 to Low
        } 
    }
    return 0;
}
