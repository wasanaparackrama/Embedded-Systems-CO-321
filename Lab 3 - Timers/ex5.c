/*
You found out the maximum interval you can implement using 
TIMER0 in exercise 4.However, by using an 8-bit counter variable
and interrupts, you can make this interval much longer. Develop
a program to blink an LED with a 100ms interval using TIMER0 .

*/

#include <avr/io.h>
#include <util/delay.h>

static unsigned char counter=0;

void delay_timer0(){
  
  /*
  clock_period=1/16 microsec
  prescalar=256
  counter_clock period=((1/16)*256)= 16 microsec
  increments= 2 millisec/16 microsec =125 
  Initial=1+255-125=131
  
  */
  
  TCNT0=131; //Load timer counter register(timer0) with 131
  
  //set the Timer/Counter  control registers for Timer0
  TCCR0A |=0x00;  //set mode to normal 
  TCCR0B |=0x04;  //set prescalar to 256
 
}

int main(void){
  
  DDRB=DDRB | (1<<5); //configure PB5 as output
	
  sei(); //set global interrupts
  
  TIMSK0 |= (1<<0);//enable timer/counter interrupt
  
  delay_timer0();
  
  
  while(1){ 
      
    if(counter>=50){  //( 100ms/2ms = 50 counts)
    	PORTB=PORTB^(1<<5); //toggle PB5  
    	counter=0;   //set counter
    }
  }
  
  return 0;
}

ISR(TIMER0_OVF_vect){ //timer0 overflow interrupt ISR
  
  counter=counter+1; //counter increment
  delay_timer0();  //set the timer counter and settings 
}



