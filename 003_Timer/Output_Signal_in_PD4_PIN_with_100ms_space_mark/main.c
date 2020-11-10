/* 

Developed by: Walid Amriou
Last update: November 2020

*/
#include<avr/io.h>
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

For Timer 0:
The TCNT0 register hold the timer Count and it is incremented on every timer "tick". 
If the timer is turned on it ticks from 0 to 255 and overflows. If it does so, 
a Timer OverFlow Flag(TOV) is set.
We can as well load a count value in TCNT0 and start the timer from a specific count. 
We can set a value in the Output Compare Register (OCR0), and whenever TCNT0 reaches that value, 
the Output Compare Flag (OCF0) flag is Set.

registers for timer 0:
********* TCNT0
Timer/Counter 0 (put the number of ticks in this register)
D7	D6	D5	D4	D3	D2	D1	D0

********* TCCR0
There are two TCCR0:

 Timer/Counter Control Register B – TCCR0B
D7	    D6	    D5	    D4	    D3	    D2	    D1	    D0
FOC0A   FOC0B   –       –       WGM02   CS02    CS01    CS00

 Timer/Counter Control Register A – TCCR0A
D7	    D6	    D5	    D4	    D3	    D2	    D1	    D0
COM0A1  COM0A0  COM0B1  COM0B0  –       –       WGM01   WGM00

with: 

TCCR0B:

D2	    D1	    D0	    Clock Source
CS02	CS01	CS00	Freq
0	    0	    0	    No Clock (Stopped)
0	    0	    1	    Clk
0	    1	    0	    Clk/8
0	    1 	    1	    Clk/64
1	    0	    0	    Clk/256
1	    0	    1	    Clk/1024
1	    1	    0	    Clk/T0-Falling edge
1	    1	    1	    Clk/T0-Rising Edge

TCCR0A:

D1	    D0	    PWM
WGM00	WGM01	Mode
0	    0	    Normal
0	    1	    CTC (Clear timer on compare match)
1	    0	    PWM (Phase correct)
1	    1	    Fast PWM

********* TIFR
Timer/Counter 0 Flag Register
The Timer/counter Interrupt Flag Register 
holds the two basic flags we need the TOV and OVF. Other bits correspond to the timer interrupts.

D7	    D6	    D5	    D4	    D3	    D2	    D1	    D0
OCF2	TOV2	ICF1	OCF1A	OCF1B	TOV1	OCF0	TOV0

------------------------------------------------------------------------------------------------------------
***** Example:
For this work: Output Signal in PD4 PIN with 100ms space/mark

Max delay:
Ftimer = CPU Frequency/Prescalar = 16MHz/1024 = 15.625KHz 
Ttick = 1/ 15.625K = 64 useconds
Ttotal = 64us X 255 = 16.32ms
OverFlowCount = 100ms/16ms = 6.25 ≈ 6

How do we code it?
So We write a simple program which will toggle a port pin (PD4) after the timer 0 overflows 6 times.
1- Load TCNT0 with 0x00 (to start from 0)
2- Set CS00 and CS02 bits in TCCR0 register to 1. This will start the time with Clk/1024 (prescalar=1024).
3- Monitor the TOV0 flag in the TIFR0 register to check if the timer has over-flowed, keep a timerOverFlowCount.
3- If timerOverFlowCount >= 6, toggle the led on PD4 and reset the count

*/

void timer_configure(){
    // step 1 of timer configure
	TCNT0=0x00;
    // step 2 of timer configure    
	TCCR0B = (1<<CS00) | (1<<CS02);
}
int main(){
	 uint8_t timerOverflowCount=0;	
     //configure PORTD as output	
	 DDRD=0xff;         

     timer_configure();

	while(1){
        while ((TIFR0 & 0x01) == 0); 
          TCNT0 = 0x00;
		TIFR0=0x01; //clear timer1 overflow flag		              
		timerOverflowCount++;		 
		if (timerOverflowCount>=6){
            PORTD ^= (0x01 << Output_signal_pin);			 
			timerOverflowCount=0;
		} 		 
	}
    return 0;	
}


