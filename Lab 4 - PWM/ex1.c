/*
1.Write a program that generates a PWM waveform with a frequency of 
approximately 976.56Hz and a duty cycle of 50%. Connect one LED to 
the PWM output pin and another to the 5V output pin (LEDs and the 
resistors you use should be identical) and check if the intensity 
of the bulb connected to PWM is half of the other.

*/
#include <avr/io.h>

int main(void){
  /*
  
  Duty cycle=((OCR0+1)/256)*100=50
  Then, OCRO=127
  
  Pre-scalar(N)=16*(10^6) /(976.56*256)=64.0001(64-->011)
  
  */
  
  DDRD = DDRD | (1<<6); //pwm pin set as output
  
  TCNT0=0;//Set timer counter register
  
  //setting output compare register A
  OCR0A=127; //counts required for the given duty cycle
  
  //Setting pre-scalar(64 i.e. 011) with timer/counter control reg
  TCCR0B |= (0<<CS02)| (1<<CS01)| (1<<CS00);
  
  //Table 15-8. Waveform Generation Mode Bit Description
  TCCR0A |=(0<<WGM02)|(1<<WGM00)|(1<<WGM01);//Set fast pwm
 
  
  //Table 15-3. Compare Output Mode, Fast PWM Mode(1
  TCCR0A |=(1<<COM0A1) | (0<<COM0A0); //Non-inverting mode
  
 
  
   
  while(1){ 
    
  }
  return 0;
}
