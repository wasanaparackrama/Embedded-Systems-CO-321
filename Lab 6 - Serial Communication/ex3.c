#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
//X is the value to be loaded to UVRR register
#define X FOSC/16/BAUD-1

//to initialize the USART to work at 9600
void usart_init(unsigned int brr)
{
	//Set baud rate (The rate of data transfer)
    //UBRRnL and UBRRnH are USART Baud Rate Registers
	UBRR0H = (unsigned char)(brr>>8);//[11:8]
	UBRR0L = (unsigned char)brr;//[7:0]
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// Select asynchronous mode
    //8-bit data, no parity, 1 stop bit
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);	
}

//to transmit a character given as the argument.
void usart_send( unsigned char data)
{
	// Wait for empty transmit buffer 
	while ( !( UCSR0A & (1<<UDRE0) ));
	// Putting data into buffer, sends the data 
	UDR0 = data;
}

//eturns a received character from the USART.
unsigned char usart_receive( void )
{
	// Wait for data to be received 
	while ( !(UCSR0A & (1<<RXC0)) );
	// Getting and return received data from buffer 
	return UDR0;
}

//Caesar cipher, key is 3
char cipher(char c){
	int encryptr;
    ////Encrypt uppercase characters 
	if(c>64 && c<91){
		encryptr=(c-65+3)%26;
		return (encryptr+65);
      
	}
     ////Encrypt lowercase characters 
    else if (c>96 && c<123){
		encryptr=(c-97+3)%26;
		return (encryptr+97);
	}else{
		return c;
	}

}



int main( void )
{
	usart_init(X);
	int i;
	while(1){
		 
		char d = usart_receive();
      //check wheather a letter or number
      //if letter
		if (isalpha(d)){
			d = cipher(d);
		}
		usart_send(d);
    
		}

return 0;

}