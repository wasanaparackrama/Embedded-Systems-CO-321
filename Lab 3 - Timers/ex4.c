/*
Exercise3:

For timer0:-

  XTAL=16MHz
  clock_period=1/16 microsec
  prescalar=1024
  counter_clock period={(1/16)*1024} =16 microsec
  Max increments upto 256
  Max delay=256x(1024x(1/16))microsec= 16.38ms

*/

/*
Write a program that toggles an LED connected to PB5 pin every 
second using TIMER1,while at the same time operating a Knight
Rider style circuit of 4 LEDs (from Lab 1). For the LED toggle
you must use the timer overflow interrupts. For the Knight Rider
style circuit you are allowed use either timer interrupts, 
polling, software delays or any other method.

*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY 100


void delay_timer1(){
  
  /*
  clock_period=1/16 microsec
  prescalar=256
  counter_clock period=((1/16)*256)= 16 microsec
  increments= 1 sec/16 microsec =62500 ( <65535)
  Initial=1+65535-62500=3036
  
  */
  
  TCNT1=3036; //Load timer counter register(timer1) with 3036
  
  //set the Timer/Counter  control registers for Timer1
  TCCR1A |=0x00;  //set mode to normal 
  TCCR1B |=0x04;  //set prescalar to 1:256 (1000)
 
}

int main(void){
  
  DDRB=DDRB | (1<<5); //configure PB5 as output(for led toggle part)
 
  DDRB=DDRB |15; //for knight rider pattern(PB0-PB3)
  
  sei(); //set global interrupts(set SREG)
  TIMSK1 |= (1<<0);//enable timer/counter interrupt
    
  delay_timer1();  //sets timer settings and counter initial
  
  while(1){ 
    for(int i=0;i<4;++i){
      _delay_ms(DELAY);
      PORTB=PORTB |(1<<i);  //set pin i high to turn on led 
      _delay_ms(DELAY);
      PORTB=PORTB & ~(1<<i); //set pin i low to turn off led 
  		
     }
    
    for(int i=2;i>0;--i){
      _delay_ms(DELAY);
      PORTB=PORTB |(1<<i);  //set pin i high to turn on led 
      _delay_ms(DELAY);
      PORTB=PORTB & ~(1<<i); //set pin i low to turn off led
      
    }
  }
  return 0;
}

ISR(TIMER1_OVF_vect){  //timer overflow interupt ISR
  PORTB=PORTB^(1<<5); //toggle PB5 
  delay_timer1();  //set the timer counter and settings 
}



