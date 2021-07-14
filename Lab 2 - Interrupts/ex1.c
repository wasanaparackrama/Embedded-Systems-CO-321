#include <avr/io.h>
#include<util/delay.h>
#define DELAY_MS 500

int main (void){
DDRD = DDRD & ~(1<<7);//set PD7 as INPUT 
DDRB = DDRB | 0b111111;//set PB 0-5 AS OUTPUT

int count=0;
while(1){
	if(PIND & (1<<7) )//IF BUTTON PRESSED
	{
		PORTB = PORTB  & ~ (count) ;//FIRST SWITCH OFF THE PREVIOUS PATTTERN
		count++;
		PORTB = PORTB  | (count) ;//LIGHT UP THE INCREMENTED PATTERN
		
		while(PIND & (1<<7))//DELAY UNTIL PRESSED
		{
		
		}


	}
	
	
}
}
