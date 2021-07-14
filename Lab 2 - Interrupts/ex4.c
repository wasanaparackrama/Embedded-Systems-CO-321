/*
4. Connect two push buttons (A and B) to two external interrupt 
pins. Connect 6 LEDs to a GPIO port. Write a program where a user 
can input a binary number using the two push buttons (press A to 
input a '0', press B to input a '1') through external interrupts,
and display that number using the LEDs. The number must be updated
and displayed every time one of the buttons are pressed.
*/

#include <avr/io.h>
#include <avr/interrupt.h>


static unsigned char number=0;

int main(){
  
  DDRB=0x3F;//set PB0-PB5  as output (0x3F= b'00111111)
  
  DDRD=DDRD &~ ((1<<2)|(1<<3));//set PD2,PD3 as input
  
  //rising edge(for both INT0 and INT1)
  EICRA=EICRA |((1<<ISC00)|(1<<ISC01)|(1<<ISC10)|(1<<ISC11));
	
  sei();//enable global interrupt
  
  EIMSK=EIMSK|((1<<INT0)|(1<<INT1));//enable extrnal interupts
  
  while(1){    //To not let the main method terminate
    
  }
  return 0;
  
  
}


ISR(INT0_vect){//TO give 0
  PORTB=PORTB & (0xC0);//switch off the previous pattern
  //(0xC0=b'11000000)
  number=(number<<1)|0; //left shift and set the last bit to 0
  
  PORTB=PORTB | number; //display the number in binary 
  
  if(number>=32){ //(only 6 bits)
    number=0;
  }
   
} 


ISR(INT1_vect){//TO give 1
  PORTB=PORTB & (0xC0); //switch off the previous pattern
  number=(number<<1)|1; //left shift and set the last bit to 0
  
  PORTB=PORTB | number; //display the number in binary
  
  
  if(number>=32){//(only 6 bits)
    number=0;
  }
  
} 
  
  
  
  
  
  
  
  
  