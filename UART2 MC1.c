
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

//declaring the lcd functions and variables
unsigned char val,input;  
void init(void);    
void main()
{
  init();         //calling init functions
  while(1)
  {
    val=PORTB ;       //Switching PORTB value according to switch press
    switch(val)       //Switch case to check data
    {
	    case 0xE0:            //If Switch 1(RB4) is Pressed
		  TXREG='A';          //Store 'A' In TXREG
	      break;
	    case 0xD0:            //If Switch 2(RB5) is Pressed
		  TXREG='B';          //Store 'B' In TXREG
	      break;
	    case 0xB0:            //If Switch 3(RB6) is Pressed
		  TXREG='C';          //Store 'C' In TXREG
	      break;
	    case 0x70:            //If Switch 4(RB7) is Pressed 
		  TXREG='D';          //Store 'D' In TXREG
	      break;	
	}	
   __delay_ms(100);
   
   if(PIR1 & 0x20)    //checking RCIF is 1 or not , if 1 , data is received
    {
      input=RCREG;     //storing the received data in input
      switch(input)    //switch case to check data
      {
	    case 'a':               //if data is 'a'
		  PORTD = 0x04;         //LED1 OFF LED2 ON
	      break;               
	    case 'b':               //if data is 'b'
		  PORTD = 0x02;         //LED1 ON LED2 OFF
	      break;
	    case 'c':               //if data is 'c'
		  PORTD = 0x06;         //LED1 ON LED2 ON
	      break;
	    case 'd':               //if data is 'd'
		  PORTD = 0x00;         //LED1 OFF LED2 OFF
	      break;	
      }
   }}}
void init(void)
{
	TRISB=0xF0;   //making PORTB 4 pins as inputs
    PORTB = 0x00;       //clearing PORTB
	OPTION_REG&=0x7F;  //enable internal pullup  
    TRISD=0x00;   //etting PORTD as Output 
    PORTD = 0x00;  //Switching Off PORTD initially
	TRISC=0xC0;   // setting for rx and tx pins
	RCSTA=0x90;    //10010000- making serial port bit receive enable bit 1
	TXSTA=0x20;    // 00100000 - making transmit enable bit 1 and uart mode, baudrate speed bit 0
	SPBRG=0x09;    //9 =>0000 1001	- Fixing baud rate as 9
}


