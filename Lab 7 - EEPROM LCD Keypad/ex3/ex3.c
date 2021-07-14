//Exercise 3

#include <avr/io.h>
#include <ctype.h>
#include <delay.h>
#include <stdlib.h>
#include "lcd.h"
#include "Keypad.h"


//(Exercise 1)
// takes the EEPROM address and the data as arguments and write to the EEPROM
void EEPROMwrite(unsigned int address, char data){

    //wait for completion of previous write
    while (EECR & (1 << EEPE));
       
    //set up address and data regs
    EEAR = address;
    EEDR = data;

    //write logical 1 to EEMPE
    EECR |= (1 << EEMPE);

    //start eeprom write
    EECR |= (1 << EEPE);
}


//takes the EEPROM address as an argument and returns the data in that memory location
char EEPROMread(unsigned int address){

    //wait for completion of writes
    while (EECR & (1 << EEPE));
       
    //set up address
    EEAR = address;

    //start eeprom read
    EECR |= (1 << EERE);

    //return data
    return EEDR;
}

//Function to apply caesar cipher to character
char caesarCipher(char rec,int secretKey){
		unsigned char c;
  		//Upper case letter 		  
		if (rec < 91 && rec > 64){
			c = (((rec - 'A') + secretKey)%26)+'A';
		}
  
  		
		return c;
	}



int main()
{
    KP_Setup();  //Setup for keypad.
	lcd_init(LCD_DISP_ON); //initialize
    lcd_clrscr(); //clear the display
    
	char key = Key_None; //Key_None	= 0x00(Keypad.h)
	
    uint8_t setKey=0; //To know once the user sets the key
	 
  while(1){
	lcd_clrscr(); // clear the display 
	lcd_puts("To Change key input 1.To encrypt input 2.\n");
		
    
    //get the key(input via keypad)
	key=KP_GetKey();//Read key from keypad without debounce. Returns Key_0 to Key_F(keypad.c)
       
    //do as required
    if(key=='1'){//change the key required
        lcd_clrscr(); // clear the display 
        lcd_puts("Enter the new key: \n"); //put string to display 
        lcd_gotoxy(0,1);  //Next line(move cursor to position 1 of line 2)
	    _delay_ms(1000);
      
     //getting the new secret key
		while(1){
			key = KP_GetKey();
			if(key != Key_None){
				lcd_putc(key);
				EEPROMwrite(0,key-48);//write the new secret key to EEPROM(address 0)(48-ascii of 0)
				_delay_ms(2000);
				break;
			}
		}
		  
		lcd_clrscr();//clear display
		lcd_puts("Key Successfully Changed.\n");
		setKey=1;//As the key is set, user will be asked for the plain text to be encrypted
		_delay_ms(1000);
	
    }
	
	else if(key=='2' || setKey==1){//encrypting required
        lcd_clrscr();//clear display
		lcd_puts("Enter the text:\n");//put string to display 
		lcd_gotoxy(0,1);//move cursor to position 1 of line 2
		_delay_ms(1000);
		char buffer[10] = "";//keeps a 10 character plaintext
		uint8_t count =0;
		 
		while(1){
			if(count>9){ //Till 10 characters
				break;
			 }
             key = KP_GetKey();//Get the key/input
				if(key != Key_None){
					lcd_putc(key); // write single char to display 
					buffer[count]=key;
					count++;
					_delay_ms(1000);
				}
		   } 
		   _delay_ms(1000);
		   lcd_clrscr();//clear display
		   lcd_puts("Cipher Text:\n");
		   lcd_gotoxy(0,1); //move cursor to position 1 of line 2
		   _delay_ms(1000);
		   char secretKey =EEPROMread(0); //read the Secret Key from the EEPROM(address 0)
		   for(int i=0;i<10;i++){ 
			   lcd_putc(caesarCipher(buffer[i],secretKey));//apply caesar cipher and display
			   
		   }
		   _delay_ms(1000);
	
			setKey=0;
  	
	}
		
  }

	return 0;
}
  