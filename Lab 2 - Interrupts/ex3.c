#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char count = 0;//to get the count of push button press



int main(void) {

	DDRD &= ~(1<<2);	///PD2 (INTO) is input
	DDRB |= 0xFF;		//PB0-PB5 as output
    EICRA |= EICRA |(0<<ISC00);	//Set Falling edge to release the push button
    EICRA |= EICRA |(1<<ISC01);

	
	EIMSK |= (1<<INT0);//Enable external interrupt 

	sei();//enable globle interrupts

	while(1){};

	return 0;
}
ISR(INT0_vect){ //handle INT0 interrupt
	count  = (count+1) % 64;//number of time push buttton pressed
	PORTB = count;
}