/* 

Developed by: Walid Amriou
Last update: November 2020

*/

#include<avr/io.h>
#include <util/delay.h>
#define Output_signal_pin PD4 

/*
------------------------------------------------------------------------------------------------------------
In AVR ATmega16 / ATmega32, there are three timers:

Timer0: 8-bit timer means it can count from 0 to 2^8 255.
Timer1: 16-bit timer means it can count from 0 to 2^16 65536. 
Timer2: 8-bit timer means it can count from 0 to 2^8 255.

Basic registers and flags of the Timers

TCNTn: Timer / Counter Register
- Every timer has a timer/counter register. It is zero upon reset. We can access value or write a value to this register. 
- It counts up with each clock pulse.

TOVn: Timer Overflow Flag
- Each timer has a Timer Overflow flag. 
- When the timer overflows, this flag will get set.

TCCRn: Timer Counter Control Register
- This register is used for setting the modes of timer/counter.

OCRn: Output Compare Register
- The value in this register is compared with the content of the TCNTn register. 
- When they are equal, the OCFn flag will get set.

------------------------------------------------------------------------------------------------------------

For Timer 1:
The TCNT0 register hold the timer Count and it is incremented on every timer "tick". 
If the timer is turned on it ticks from 0 to 65536 and overflows. 

registers for timer 1:
********* TCNT0

Timer/Counter 1
TCNT1H	                        TCNT1L
D15	D14	D13	D12	D11	D10	D9	D8	D7	D6	D5	D4	D3	D2	D1	D0

********* TCCR1A and TCCR1B

TCCR1A: Timer Counter Control Register 1A
D7	    D6	    D5	    D4	    D3	    D2	    D1	    D0
COM1A1	COM1A0	COM1B1	COM1B0	FOC1A	FOC1B	WGM11	WGM10

TCCR1B: Timer Counter Control Register 1B
D7	    D6	    D5	    D4	    D3	    D2	    D1	    D0
ICNC1	ICES1	-	    WGM13	WGM12	CS12	CS11	CS10

with: 

D2	    D1	    D0	    Clock Source
CS12	CS11	CS10	Freq
0	    0	    0	    No Clock (Stopped)
0	    0	    1	    Clk
0	    1	    0	    Clk/8
0	    1	    1	    Clk/64
1	    0 	    0	    Clk/256
1	    0	    1       Clk/1024
1	    1	    0	    Clk/T1-Falling edge
1	    1	    1	    Clk/T1-Rising Edge


********* TIFR
Timer/Counter1 Interrupt Flag Register – TIFR1
D7	    D6	    D5	    D4	    D3	    D2	    D1	    D0
–       –       ICF1    –       –       OCF1B   OCF1A   TOV1

------------------------------------------------------------------------------------------------------------
***** Example:
For this work: Output Signal in PD4 PIN with 100ms space/mark

Max delay:
Ftimer = CPU Frequency/Prescalar = 16MHz/1024 = 15.625KHz 
Ttick = 1/ 15.625K = 64 useconds
Ttotal = 64us X 65536 = 4 seconds
4 seconds is > 100ms 
so 100ms/64us=1562.5
so Ttotal = 64us * 1562.5 = 100ms but we can't work with 0.5 so 
Ttotal = 64us * 1562.5 = 0.099968 = 99.968 ms and it's good.

How do we code it?
So We write a simple program which will toggle a port pin (PD4) after the timer 1 overflows.
1- Load OCR1A by 1562
2- Run the timer with pre-scalar of 1024 by setting CS12 and CS10 bits.
3- Monitor OCF flag and if it is set, toggle the led
4- Reset the TCNT1L and TCNT1H values to zero and repeat steps 1 to 3.

*/

void timer_configure(){
	//set the pre-scalar as 1024       
	TCCR1B = (1<<CS10) | (1<<CS12); 
	// set Output Compare Register (OCR) to 1562 so it set the flag (OCF flag) when
	// the register counter = Output Compare Register valure (see the notes above) 
	OCR1A = 1562; 	  
	// clear the timer count register 
	TCNT1 = 0;
}

int main(){
	// configure Pin as output
	DDRD |= (1<<Output_signal_pin) ;  
    timer_configure();

	while(1){
		// If flag is set toggle the pin	
		// wait till the timer overflow flag is SET
		while((TIFR1 & (1<<OCF1A)) == 0);
		// PORTD_pin4 xor 1: if is 1 so be 0 and if 0 so be 1  
		PORTD ^= (1<< Output_signal_pin);
		// clear the timer count register
		TCNT1 = 0; 
		//clear timer1 overflow flag
		TIFR1 |= (1<<OCF1A) ;  
	}	
}


