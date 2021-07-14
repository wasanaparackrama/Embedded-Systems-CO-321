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

void delay_timer1(){
  
  /*
  clock_period=1/16 microsec
  prescalar=256
  counter_clock period=((1/16)*256)= 16 microsec
  increments= 50 millisec/16 microsec =3125 ( <65535)
  Initial=1+65535-3125=62410
  
  */
  
  TCNT1=62410; //Load timer counter register(timer1) with 62410
  
  //set the Timer/Counter  control registers for Timer1
  TCCR1A |=0x00;  //set mode to normal 
  TCCR1B |=0x04;  //set prescalar to 256 
 
}

int main(void){
  
  //configure PB0(50ms) & PB5(500ms) as output
  DDRB=DDRB | ((1<<0)|(1<<5));
  
  sei(); //set global interrupts
  
  TIMSK0 |= (1<<0);//enable timer/counter interrupt
  TIMSK1 |= (1<<0);
  
  delay_timer0();//set the timer0 counter and settings
  delay_timer1();//set the timer1 counter and settings
  
  while(1){ 
       
    if(counter>=250){  //( 500ms/2ms = 250 counts)
    	PORTB=PORTB^(1<<5); //toggle PB5  
    	counter=0;   //set counter
    }
  }
  
  return 0;
}

ISR(TIMER0_OVF_vect){//timer0 overflow interrupt ISR
  counter=counter+1; //counter increment
  delay_timer0();  //set the timer counter and settings 
}

ISR(TIMER1_OVF_vect){//timer1 overflow interrupt ISR 
  PORTB=PORTB^(1<<0); //toggle PB5 
  delay_timer1();  //set the timer counter and settings 
}





