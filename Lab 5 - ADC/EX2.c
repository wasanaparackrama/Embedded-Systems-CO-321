#include<avr/io.h>
#include<util/delay.h>
int main (){
	//PORTC=PORTC & ~(1<<1);
	//PORTD=PORTD | 11111;
	DDRC=DDRC & ~(1 << 1);
	DDRD=DDRD | (1<<1);
	//ADEN=1;//ENABLE ADC
	//ADPS2=1;//ADC PRESCALER (SPEED OF CONVERSION)=128
	//ADPS1=1;
	//ADPS0=1;
	ADCSRA |=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	//5V AS THE REFERENCE 
	//MUX3=0;MUX2=0;MUX1=0;MUX0=1;//SET THE INPUT CHANNEL ADC1
  	//ADLAR=1;//LEFT SHIFTED
	ADMUX = ADMUX |(1 << MUX0)|(1 << ADLAR) ;
	ADMUX = ADMUX & ~(1 << REFS1)& ~(1 << REFS0) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1);
	
	ADCSRA = ADCSRA |(1 << ADSC);//START CONVERSION

    while(1){
      //UNTIL CONVERSION FINISH
      while(ADCSRA & (1 << ADSC )) ;
       //LAST 8 BITS OF THE OUTPUT
       int temp = int(((ADCH<<2)|(ADCL>>6))*5/255);
       //AT FULLY DARKNESS temp IS 4 V
       //AT 3.8V IT ALSO CAN BE CONSIDERED AS DARK
       //IF DARK
       if(temp >= 3.8)
       {
         //ASSIGN 1 TO DIGITAL PIN 1
         PORTD  = PORTD | (1<<1);
       }
       else
       {
          //ELSE 0 TO DIGITAL PIN 1
          PORTD  = PORTD & ~(1<<1);
       }

      _delay_ms(10);
      //ENABLE THE ADSC
      //START CONVERSION
      ADCSRA = ADCSRA |(1 << ADSC);//START CONVERSION
    }


	return 0;
}
