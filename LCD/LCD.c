/*********************************************************

     * Name              : Eman Megahed
	 * Data              : 6/1/2021
	 * Version           : 1.0
	 * SWC               : LCD.c

**********************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "Platform_Types.h"
#include "LCD.h"
#include "E:\1\NTI\AVR\AVR\RTOS\MCAL\GPIO\Dio.h"
#include "LCD_Cfg.h"

static void LCD_WriteHalfPort(u8 data);

#if LcdMode==BIT_8_MODE
void LCD_WriteCommand(u8 Data)
{
	Dio_WriteChannel(RS,STD_LOW);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	Dio_WritePort(PORTLCD,Data);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}

void LCD_WriteData(u8 Data)
{
	Dio_WriteChannel(RS,STD_HIGH);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	Dio_WritePort(PORTLCD,Data);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}

void LCD_init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x38);
	_delay_us(50);
	LCD_WriteCommand(0x0c);
	_delay_us(50);
	LCD_WriteCommand(0x1);
	_delay_ms(2);
	LCD_WriteCommand(0x6);
	_delay_ms(2);
}

#elif LcdMode == BIT_4_MODE
static void LCD_WriteHalfPort(u8 data)
{
	Dio_WriteChannel(D4,READ_BIT(data,0));
	Dio_WriteChannel(D5,READ_BIT(data,1));
	Dio_WriteChannel(D6,READ_BIT(data,2));
	Dio_WriteChannel(D7,READ_BIT(data,3));

}

void LCD_WriteCommand(u8 Data)
{
	Dio_WriteChannel(RS,STD_LOW);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	LCD_WriteHalfPort(Data>>4);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_HIGH);
	LCD_WriteHalfPort(Data);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}

void LCD_WriteData(u8 Data)
{
	Dio_WriteChannel(RS,STD_HIGH);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	LCD_WriteHalfPort(Data>>4);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_HIGH);
	LCD_WriteHalfPort(Data);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
}

void LCD_init(void)
{
	_delay_ms(50);
	Dio_WriteChannel(RS,STD_LOW);
	Dio_WriteChannel(RW,STD_LOW);
	Dio_WriteChannel(E,STD_HIGH);
	LCD_WriteHalfPort(0x02);
	_delay_ms(1);
	Dio_WriteChannel(E,STD_LOW);
	_delay_ms(1);
	_delay_us(50);
	LCD_WriteCommand(0x28);
	_delay_us(50);
	LCD_WriteCommand(0x0c);
	_delay_us(50);
	LCD_WriteCommand(0x1);
	_delay_ms(2);
	LCD_WriteCommand(0x6);
	_delay_ms(2);
}

#endif











