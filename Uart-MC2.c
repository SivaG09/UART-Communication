
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

unsigned char input;  //VARIABLE TO RECIEVE DATA 
void recieve_init(void);   //DECLARING RECIEVE_INIT FUNCTION
void main()
{
  recieve_init();     //CALLING INIT FUNCTION
  while(1)
  {
    if(PIR1 & 0x20)    //CHECKING RCIF BIT IS 1 OR NOT, IF 1 DATA IS RECIEVED
    {
      input=RCREG;     //STORING THE RECIEVED VALUE IN INPUT VARIABLE
      switch(input)    //SWITCH CASE FOR CHECKING THE DATA
      {
	    case 'A':               //IF DATA = 'A'
		  PORTD = 0x02;         //LED1 ON LED2 OFF
	      break;               
	    case 'B':               //IF DATA = 'A'
		  PORTD = 0x10;         //LED1 OFF LED2 ON
	      break;
	    case 'C':               //IF DATA = 'A'
		  PORTD = 0x12;         //LED1 ON LED2 ON
	      break;
	    case 'D':               //IF DATA = 'A'
		  PORTD = 0x00;         //LED1 OFF LED2 OFF
	      break;	
      }
	}
  }
}

void recieve_init(void)
{
	TRISD=0x00;   //SETTING PORTD AS OUTOUT 
	TRISC=0xC0;   // SETTING FOR RX AND TX PINS
    PORTD = 0x00;  //SWITCHING OFF PORTD INITIALLY
	RCSTA=0x90;    //10010000 - MAKING SERIAL PORT AND RECIEVE BIT ENABLE
	TXSTA=0x20;    // 00100000 - MAKING TRANSMIT ENABLE BIT 1 AND UART MODE BIT 0 AND BAUD RATE LOW SPEED
	SPBRG=0x09;    //9 =>0000 1001	- FIXING BAUD RATE AS 9
}


