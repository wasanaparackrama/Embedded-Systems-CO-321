#include <avr/io.h>

#include <avr/interrupt.h>

int main()
{
	DDRB = DDRB |  (1<<0); //PB0 AS OUTPUT
	DDRD = DDRD & ~(1<<2);//INT0 AS INPUT(PD2)
	EICRA = EICRA & ~(1<<ISC00); //SET ACTIVITY ON PIN
	EICRA = EICRA | (1<<ISC01);
	sei();//SET I BIT IN SREG
	EIMSK = EIMSK | (1<<INT0);//INT0 SET IN EIMSK
	

	while(1)
	{

	}
	return 0;
}

ISR(INT0_vect)
{	
	PORTB = PORTB ^ (1<<0);//TOGGLR PB0
	
}
