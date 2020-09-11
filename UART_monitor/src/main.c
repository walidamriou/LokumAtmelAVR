#include <avr/io.h>

//#define F_CPU 16000000
#define BUAD 9600
#define BRC ((F_CPU/16/BUAD)-1)

#include <util/delay.h>

int main(void){
    UBRR0H = (BRC >> 8);
    UBRR0L = BRC;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | ( 1 << UCSZ00);
    while (1)
    {
        UDR0 = 'W';
        UDR0 = 'A';
        UDR0 = 'L';
        UDR0 = 'I';
        UDR0 = 'D';
        UDR0 = '\n';

        _delay_ms(1000);
    }
    
}