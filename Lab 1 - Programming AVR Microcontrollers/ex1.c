#include  <avr/io.h>
#include <util/delay.h>
#define BLINK_DELAY_MS 500


int main(void){
 
    DDRB = DDRB | 15;/*DDRB  PORT 0,1,2,3 SET AS OUTPUT*/
    while(true){
        PORTB = PORTB | 15;/*SET PORT 0,1,2,3 HIGH TO TURN ON LED*/
        _delay_ms(BLINK_DELAY_MS);/*DELAY 500ms*/
        PORTB = PORTB & (~15) ;/*SET PORT 0,1,2,3 LOW TO TURN OFF LED*/
        _delay_ms(BLINK_DELAY_MS);/*DELAY 500ms*/
    }
  return 0;
}