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

********* TIMSK1
Timer/Counter1 Interrupt Mask Register – TIMSK1

D7	    D6	    D5	    D4	    D3	    D2	    D1	    D0
–       –       ICIE1   –       –       OCIE1B  OCIE1A  TOIE1

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
TCNT1_valure = 65536 - 1562 = 63974

How do we code it?
So We write a simple program which will toggle a port pin (PD4) after the timer 1 overflows.
- Load the TCNT1 register with 63974.
- Set CS10 and CS12 bits to configure pre-scalar of 1024.
- Enable timer1 overflow interrupt(TOIE1).
- Enable global interrupts by setting global interrupt enable bit in SREG
- Toggle the LED in the ISR and reload the TCNT value.

------------------------------------------------------------------------------------------------------------
*/

void timer_interrupts_configure(){
	// 65536 - 1562 = 63974
	TCNT1 = 63974;   	
	// Don't use TCCR1A
	TCCR1A = 0x00;
	// Timer mode with 1024 prescler
	TCCR1B = (1<<CS10) | (1<<CS12);  
	// Enable timer1 overflow interrupt(TOIE1)
	TIMSK1 = (1 << TOIE1);   
	// Enable global interrupts by setting global interrupt enable bit in SREG
	sei();    
}


// Timer1 ISR
ISR(TIMER1_OVF_vect){
	PORTD ^= (1 << Output_signal_pin);	
	// 65536 - 1562 = 63974
	TCNT1 = 63974;   
}

int main(){
	// Configure the PORTD4 as output
	DDRD = (1 << Output_signal_pin);     
    
	timer_interrupts_configure();
	
	while(1){}
}

