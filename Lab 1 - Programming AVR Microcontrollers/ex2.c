#include  <avr/io.h>
#include <util/delay.h>
#define BLINK_DELAY_MS 500


int main(void){
  
  	int i=8;
 
    DDRB = DDRB | 15;//configure pin 0,1,2,3 of PORTB for output
  	while(true){
        
    		while(i > 1) {/*if  current i is 8 or 4  or 2*/
              
    			PORTB =PORTB | i; //i th port sert high to turn on led
                _delay_ms(BLINK_DELAY_MS);//delay
                 PORTB =PORTB &  ~i;//i th port sert low to turn off led
                _delay_ms(BLINK_DELAY_MS);
              
                i >>= 1;//i right  shifted by 1
                    
    		}
    		while(i < 8){ /*if  current i is 4  or 2 or 1*/
              
    			PORTB =PORTB | i;//i th port sert high to turn on led
                _delay_ms(BLINK_DELAY_MS);//delay
                PORTB =PORTB &  ~i;//i th port sert low to turn off led
                _delay_ms(BLINK_DELAY_MS);
              
                i <<= 1;//i left shifted by 1
    		}
	  }

    return 0;
}
