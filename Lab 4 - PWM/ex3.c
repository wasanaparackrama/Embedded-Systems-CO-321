#include<avr/io.h>
#include<util/delay.h>


void scalar(unsigned char value){
	TCCR0B = value;//set prescalar
    OCR0A  =25;//duty cycle changed to (25+1/256-%
    // SET WGM02:0 AS 11  (FAST PWM)
    // AND COM0A 1:0  AS 1 0(NON INVERTING)
	TCCR0A &= ~(0<<COM0A0);
	TCCR0A |= (1<<WGM01)|(1<<WGM00)|(1<<COM0A1);
    TCCR0B &= ~(1<<WGM02);//WGM02=0 
  
  
  
}

int main (void){

	

	DDRD = DDRD | (1<<6);//SET DDRD6 AS OUTPUT
	

	while(1){
      
      /*f(GENERATED WAVE)=F(OSCILLATOR)/(256*N)*/
		
		scalar(2);//SCALAR SET TO 8->  7812.5Hz
		_delay_ms(1000);
		scalar(3);//SCALAR SET TO 64-> 976.5625Hz
		_delay_ms(1000);
		scalar(4);//SCALAR SET TO 256->244.14Hz
		_delay_ms(1000);
		scalar(5);//SCALAR SET TO 1024->61.035Hz
		_delay_ms(1000);
		
       
	}
	

}
