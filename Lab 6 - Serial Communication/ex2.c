/*
Exercise 2
*/

#include <avr/io.h>
#include <util/delay.h>

/*
Desired baud Rate =Fosc/(16 (X + 1)
Then,
9600=16x(10^6)/(16(x+1))

x=103.1(103)

*/

void usart_init(){
  
   //9600 baud i.e. set UBRR (USART Baud rate Register) to x=103
	UBRR0L = 103%256; //bits [7:0] of baud rate
	UBRR0H = 103/256; //bits [11:8] of baud rate
  
  //(USART Control Status Registers) 
  
  //Asynchronous i.e. set UMSELn Bits (00)
  //Table 20-8. UMSELn Bits Settings
    UCSR0C &= ~(1<<UMSEL01 | 1<<UMSEL00);
  
  //8-bit data i.e. set UCSZn Bits of UCSR0C(011 for 8 bit)
  //Table 20-11. UCSZn Bits Settings)
    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0B &= ~(1<<UCSZ02);
  
  //no parity i.e. set UPMn Bits of UCSR0C(00)
  //Table 20-9. UPMn Bits Settings
    UCSR0C &= ~(1<<UPM01 | 1<<UPM00);
  
  //1 stop bit i.e. set USBS Bit Settings(0)
  //Table 20-10. USBS Bit Settings
     UCSR0C &= ~(1<<USBS0);
  
}
  
void usart_send(char c){
  //Enable the USART transmitter(Set TXEN0 bit in UCSR0B to 1).
     UCSR0B |= (1<<TXEN0);
  
  // character byte written into the UDR0 register
      UDR0=c;
  
  //wait till UDR0 is ready for next cycle i.e. 
  //monitor UDRE0 bit of UCSR0A register
  while(!(UCSR0A& (1<<UDRE0))){}//waiting    (polling)
	
 }
            
char usart_receive(){
      char c;
   //Enable the USART receiver (SetRXEN0 bit in UCSR0B to 
       UCSR0B |= (1<<RXEN0);
   
   //wait till an entire character is received
  //monitor RXC0 flag bit  of UCSR0A register
       while(!(UCSR0A& (1<<RXC0))){}
   
   //when RXC0 is raised, the UDR register has the byte
       c=UDR0;
   
	return c;
  }
   
void passChars(char char_arr[]){
	int i=0;
        while(char_arr[i]){
	    	usart_send(char_arr[i]);
			i++;
		}
	usart_send('\0');
}
   
 int main(){
	usart_init();
   
   passChars("Dulmini  E/16/096\n");
   passChars("Wasana E/16/273\n");
   passChars("Kalani E/16/290\n");
   
   
 }
   

  
  
