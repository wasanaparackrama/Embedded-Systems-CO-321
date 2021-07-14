#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 10
//N=16 MHz /(256 *976.56)=64 prescaler
//OCRO=((50*256)/100)-1=127

int main(void) {

	unsigned char i;
    //set PD6(PMW output pin) for output
	DDRD |= (1<<6);
   
    // set prescaler to 64 and starts PWM
	TCCR0B |= (0 << CS02)  | (1 << CS01)|(1 << CS00); 
	// set fast PWM Mode(set waveform generation bits to 11)
	TCCR0A = (1 << WGM01) | (1 << WGM00);
    // set none-inverting mode
	TCCR0A |= (1 << COM0A1)| (0 << COM0A0); 
    
	
	
	while(1){
		for (i = 0; i < 255; i++){//off->on
            _delay_ms(BLINK_DELAY_MS);	
			OCR0A = i;//setting output compare register A(to generate another interrupt)
					
		}
		for (i = 255; i >0 ; i--){//on->off
             _delay_ms(BLINK_DELAY_MS);	
			OCR0A = i;//setting output compare register A
						
		}
	};

	return 0;
}