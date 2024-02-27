
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

unsigned char val;     //VARIABLE TO STORE SWITCH PRESS VALUE
void init(void);         //DECLARING INIT FUNCTION
void main()
{
  init();             //CALLING INIT FUNCTION
  while(1)
  {
    val=PORTB ;       //STORING THE PORTB VALUE ACCORDING TO SWITCH PRESS
    switch(val)       //SWITCH CASE FOR CHECKING THE DATA
    {
	    case 0xE0:            //IF SWITCH 1(RB4) IS PRESSED 
		  TXREG='A';          //STORE 'A' IN TXREG
	      break;
	    case 0xD0:            //IF SWITCH 2(RB5) IS PRESSED 
		  TXREG='B';          //STORE 'B' IN TXREG
	      break;
	    case 0xB0:            //IF SWITCH 3(RB6) IS PRESSED 
		  TXREG='C';          //STORE 'C' IN TXREG
	      break;
	    case 0x70:            //IF SWITCH 4(RB7) IS PRESSED 
		  TXREG='D';          //STORE 'D' IN TXREG
	      break;	
	}	
   __delay_ms(100);
  }
}

void init(void)
{
	TRISB=0xF0;   //MAKING TRISB 4 PINS AS INPUT FOR SWITCH 
    PORTB = 0x00;       //CLEARING PORTB
	OPTION_REG&=0x7F;  //ENABLE INTERNAL PULLUP
	TRISC=0xC0;  // SETTING FOR RX AND TX PINS
	RCSTA=0x90;   //10010000 - MAKING SERIAL PORT AND RECIEVE BIT ENABLE
	TXSTA=0x20;   // 00100000 - MAKING TRANSMIT ENABLE BIT 1 AND UART MODE BIT 0 AND BAUD RATE LOW SPEED
	SPBRG=0x09;      //9 =>0000 1001 - FIXING BAUD RATE AS 9
}

