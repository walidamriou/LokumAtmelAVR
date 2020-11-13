/* 

ADC (Analog to Digital converter) by AVR c 

Developed by: Walid Amriou
Last update: November 2020

*/


#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

/*
- ATmega16/32 has 8 ADC channels (we can connect 8 analog inputs at a time)
- the channels from 0 to 7 are present on PORTA.
- The controller has 10 bit ADC, so we will get digital output 0 to 1023.
   When the input is 0V => 0V 
   when input is 5V (and Vref=5V) => 1023 
- So controller ADC has 1023 steps and:
   Step size with Vref=5V :  5/1023 = 4.88 mV. 
   Step size with Vref=2.56 :  2.56/1023 = 2.5 mV.
   So Digital data output will be Dout = Vin / step size.
*/
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
