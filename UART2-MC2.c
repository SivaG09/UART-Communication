
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
unsigned char input;
void recieve_init(void);
void lcdinit(void);
void lcd_data(unsigned char data);
void lcd_command(unsigned char cmd);
unsigned char arr[14]={"RECIEVED DATA:"},arr1[14]={"TRANSFER DATA:"};
unsigned int i;

void main()
{
  //calling lcdinit  and recieve_init functions  
  recieve_init();
  lcdinit();
  lcd_command(0x80);       //command to display from 80
  for(i=0;i<14;i++)        //printing the statement in line 1 using for loop
  {
      lcd_data(arr[i]);
  }
  lcd_command(0xC0);       //command to display from 80
  for(i=0;i<14;i++)        //printing the statement in line 2 using for loop
  {
      lcd_data(arr1[i]);
  }
  while(1)
  {
    if(PIR1 & 0x20)          //checking RCIF is 1 or not , if 1 , data is received
    { 
      input=RCREG;           //storing the received data in input
      switch(input)          //switch case to check data
      { 
	    case 'A':              //if data is 'A'
          lcd_command(0x8E);    //command to print in 8E
          lcd_data(0x41);       //printing 'A'
          TXREG='a';            //transmitting 'a'
          lcd_command(0xCE);    //command to print in CE
          lcd_data(0x61);       //printing 'a'
	      break;
	    case 'B':                    //if data is 'B'
          lcd_command(0x8E);         //command to print in 8E
          lcd_data(0x42);            //printing 'B'
          TXREG='b';                 //transmitting 'b'
          lcd_command(0xCE);         //command to print in CE
          lcd_data(0x62);            //printing 'b'
	      break;
	    case 'C':                    //if data is 'C'
          lcd_command(0x8E);         //command to print in 8E
          lcd_data(0x43);            //printing 'C'
          TXREG='c';                 //transmitting 'c'
          lcd_command(0xCE);         //command to print in CE
          lcd_data(0x63);            //printing 'c'
	      break;
	    case 'D':                     //if data is 'D'
		  lcd_command(0x8E);          //command to print in 8E
          lcd_data(0x44);             //printing 'D'
          TXREG='d';                  //transmitting 'd'
          lcd_command(0xCE);          //command to print in CE
          lcd_data(0x64);             //printing 'd'
	      break;	
      }
	}
  }
}

void recieve_init(void)
{  
	TRISC=0xC0;   // setting for rx and tx pins
	RCSTA=0x90;    //10010000- making serial port bit receive enable bit 1
	TXSTA=0x20;    // 00100000 - making transmit enable bit 1 and uart mode, baudrate speed bit 0
	SPBRG=0x09;    //9 =>0000 1001	- Fixing baud rate as 9
}

void lcdinit(void)
{  
 TRISB = 0x00;    //setting PORT B as output
 TRISD = 0x00;    //setting PORT D as output
 lcd_command(0x38);   //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);        //generating delay for 100ms
  lcd_command(0x38);   //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);         //generating delay for 100ms
  lcd_command(0x38);   //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);         //generating delay for 100ms
  lcd_command(0x38);  //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);        //generating delay for 100ms
 lcd_command(0x0C);  //setting display on and curson off
 __delay_ms(100);        //generating delay for 100ms
 lcd_command(0x06);    //setting entry mode, increments to right shift
 __delay_ms(100);       //generating delay for 100ms
 lcd_command(0x01);     //setting clear display
 __delay_ms(100);       //generating delay for 100ms
}

void lcd_command(unsigned char cmd)
{
    PORTB = 0x00;      //making RS as 0 
    PORTD = cmd;       //assigning the command
    PORTB = 0x04;       //making EN as 1
    PORTB = 0x00;      //making EN as 0
    __delay_ms(200);   //delay for 200 ms
}
void lcd_data(unsigned char data)
{
    PORTB = 0x08;      //making RS as 1 
    PORTD = data;       //assigning the command
    PORTB = 0x0C;       //making EN as 1
    PORTB = 0x08;      //making EN as 0
    __delay_ms(200);   //delay for 200 ms
}


