/*
Write a C program to toggle an LED connected to pin 5 of 
PORTB register (PB5) every 2ms.
Use TIMER0, normal mode, and a suitable pre-scalar to create 
the delay. Assume XTAL= 16MHz.
*/

#include <avr/io.h>
#include <util/delay.h>


void delay_timer0(){
  
  /*
  clock_period=1/16 microsec
  prescalar=256
  counter_clock period={(1/16)*256} =16 microsec
  increments= 2 ms/16 microsec =125 ( <255)
  Initial=1+255-125=131
  
  */
  
  
  TCNT0=131; //Load timer counter register with 131
  
  //set the Timer0
  TCCR0A=0x00;  //set mode to normal 
  TCCR0B=0x04;  //set prescalar to 256 
  
  
  
  //wait till timer overflow bit (T0V0) is set
  //while((TIFR0&0x01)==0);
  while(TCNT0<255);

  //clear timer settings(stops the timer)
  TCCR0A=0x00;
  TCCR0B=0x00;
  
  //clear the timer overflow bit(T0V0) for next round
  TIFR0=0x01;
  
}

int main(void){
  
  DDRB=DDRB | (1<<5); //configure PB5 as output
  
  while(1){
    
    PORTB=PORTB^(1<<5); //toggle PB5
   // for(int i=0;i<100;++i){
    delay_timer0();
    //}
  	//_delay_ms(200);
  }
	
  return 0;
}

