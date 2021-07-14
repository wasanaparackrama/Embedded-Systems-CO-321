#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>


#define FOSC 16000000 // Clock Speed
#define BAUD 9600
/*FOSC/16/(BAUD-1)*/
unsigned int UBRRreg= 104;


void usart_initialize(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //8-bit data, no parity, 1 stop bit
}

void usart_send( unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0) ));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char usart_receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void EEPROMwrite(unsigned int address ,char data) {
	//when 	EEPE is one =>previos write not yet finished
	//wait until it finish
	while(EECR & (1<<EEPE));

	EEAR = address;//write address to the address reg EEARH+EEARL
	EEDR = data ;//write data to EEPROM data reg

	//write one to EEMPE befoe write
	EECR = EECR | (1 << EEMPE) ;
	//write 1 to EEPE TO enable EEPROM write
	EEPE = EEPE | (1 << EEPE) ;



}

char EEPROMread(unsigned int address) {
	//wait until previous writes finish
	while( EECR & (1 << EEPE)) ;

	//set up address
	EEAR = address;

	//start EEPROM read
	EECR = EECR  | (1<< EERE);
	//return data 
	return EEDE ;


}

int main(){
	
	usart_initialize(UBRRreg);
	int i=0;
	
	
	
	//while(i < 1024){
     
      
      
      // write to eeprom
      
      while (1)
      {

      	char d=usart_receive();

      	if (d=='\r')
      	{
      		/* code */
      		break;
      	}
      	
      	EEPROMwrite(i,d);
 
      
      	/* code */
      }
      
	  
      for (int i = 0; i < 1024; ++i)
      {
      	char c = EEPROMread(i);
      	usart_send(c);
      }
	  
    //  i++;
		
	//}

	return 0;
}