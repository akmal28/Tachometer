#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define		LCD_DATA_PORT		PORTB
#define 	LCD_CONT_PORT		PORTA
#define 	LCD_RS 				PA0
#define 	LCD_RW 				PA1
#define 	LCD_EN 				PA2


void lcd_data_write(char data);
void lcd_command_write( char command);
void lcd_init();
void lcd_string_write( char *string);
void lcd_number_write(int number,unsigned char radix);


int main(void){

    char str[10];
	int rpmData;
	char fixData[10];
    int len = 0;
	int checking=0;

	DDRB=0xff;
	DDRA=0x07;
	DDRC=0x00;

	DDRD |= 1 << PIND1;
	DDRD &= ~(1 << PIND0);
	PORTD |= 1 << PIND0;
	UART_Init(1200);

	lcd_init();
	lcd_string_write("WELCOME WORLD");
	lcd_command_write(0xc0);
	_delay_ms(500);

	lcd_command_write(0x01);
	lcd_string_write("KELOMPOK K");
	_delay_ms(500);
	lcd_command_write(0x01);
	lcd_string_write("   TACHOMETER   ");

	while(1){

		if (PINC & (1<<PC0)){
			lcd_command_write(0x01);
			lcd_string_write("   TACHOMETER   ");
			lcd_command_write(0xc0);
			lcd_string_write("RPM: ");
			UART_TxChar('a');
			_delay_ms(100);
			checking = 1;

		}
		else if(PINC & (1<<PC1)){
			lcd_command_write(0x01);
			lcd_string_write("   TACHOMETER   ");
			lcd_command_write(0xc0);
			lcd_string_write("RPM: ");
			UART_TxChar('b');
			_delay_ms(100);
			checking = 1;

		}
		else if(PINC & (1<<PC2)){
			lcd_command_write(0x01);
			lcd_string_write("   TACHOMETER   ");
			lcd_command_write(0xc0);
			lcd_string_write("RPM: ");
			UART_TxChar('c');
			_delay_ms(100);
			checking = 1;

		}
		else if(PINC & (1<<PC3)){
			lcd_command_write(0x01);
			lcd_string_write("   TACHOMETER   ");
			UART_TxChar('d');
			_delay_ms(100);
			//checking == 1;
		}



        if (checking == 1){
        len=UART_RxString(str);
		rpmData=atoi(str);
		rpmData=rpmData*6;
		itoa(rpmData,fixData,10);
        lcd_string_write(fixData);
		_delay_ms(1000);
		checking=0;}

        //lcd_command_write(0x01);
    }
}

void lcd_data_write(char data)
{
	LCD_CONT_PORT=_BV(LCD_EN)|_BV(LCD_RS);
	LCD_DATA_PORT=data;
	_delay_ms(1);
	LCD_CONT_PORT= _BV(LCD_RS);
	_delay_ms(1);
}

void lcd_command_write(char command)
{
	LCD_CONT_PORT=_BV(LCD_EN);
	LCD_DATA_PORT=command;
	_delay_ms(1);
	LCD_CONT_PORT=0x00;
	_delay_ms(1);
}

void lcd_init()
{

	lcd_command_write(0x38);
	lcd_command_write(0x01);
	lcd_command_write(0x06);
	lcd_command_write(0x0e);
}

void lcd_string_write(char *string)
{
	while (*string)
	lcd_data_write(*string++);
}

void lcd_number_write(int number,unsigned char radix)
{
	char *number_string="00000";
	itoa(number,number_string,radix);
	lcd_string_write(number_string);
}

