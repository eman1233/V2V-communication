/*
 * LcdService.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "Platform_Types.h"
#include "LCD.h"
#include "Dio.h"
#include "LCD_Cfg.h"
#include "LcdService.h"
void LCD_WriteString(u8 *str)
{
	for(u8 i = 0;str[i];i++)
	{
		LCD_WriteData(str[i]);
	}
}

void LCD_CursorMove(u8 row,u8 col)
{
	if(row==1)
	{
		LCD_WriteCommand(col+0x80);
	}
	else if(row==2)
	{
		LCD_WriteCommand(col+0x40+0x80);
	}
	else if(row==3)
	{
		LCD_WriteCommand(col+0X10+0x80);
	}
	else if(row==4)
	{
		LCD_WriteCommand(col+0X50+0x80);
	}

}

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_WriteNum(s16 num)
{
	u8 rem = 0;
	u8 i = 0;
	u16 arr[16]={0};
	u8 j = 0;
	if(num>0)
	{
		while(num>0)
		{
			rem=num%10;
			arr[i]=rem+'0';
			i++;
			num=num/10;
		}
		for( j=i;j>0;j--)
		{
			LCD_WriteData(arr[j-1]);
		}
	}
	else if(num<0)
	{
		LCD_WriteData('-');
		while(num<0)
		{
			rem=num%10;
			arr[i]=-rem+'0';
			i++;
			num=num/10;
		}
		for( j=i;j>0;j--)
		{
			LCD_WriteData(arr[j-1]);
		}
	}
	else
		LCD_WriteData('0');

	/*
	 * u8 reversed = 1;
	 * if(num==0)
	 * {
	 * LCD_WriteData('0');
	 * }
	 * 	if(num>0)
	{
		while(num>0)
		{
		reserved=reserved+num%10;
		num=num/10;
		}
		do
		{
		LCD_WriteData(reversed%10+'0');
		reversed/=10;
		}
		while(reversed!=1)
	}
	 */

}

void LCD_WriteNumInBinary(u8 num)
{
	u8 rem = 0;
	u8 i = 0;
	u16 arr[16]={0};
	u8 j = 0;

	if(num>0)
	{
		while(num>0)
		{
			rem=num%2;
			arr[i]=rem+'0';
			i++;
			num=num/2;
		}
		for( j=i;j>0;j--)
		{
			LCD_WriteData(arr[j-1]);
		}
		/*for(i=8;i>0;i--)
		{
			LCD_WriteData(((num>>i)&1)+'0');
		}*/
	}




}

void LCD_WriteNum_4D(u16 num)
{
	LCD_WriteData(((num%10000)/1000)+'0');
	LCD_WriteData(((num%1000)/100)+'0');
	LCD_WriteData(((num%100)/10)+'0');
	LCD_WriteData(((num%10)/1)+'0');

}

void LCD_WriteNum_2D(u16 num)
{
	LCD_WriteData(((num%100)/10)+'0');
	LCD_WriteData(((num%10)/1)+'0');

}

void LCD_DrowPattarn(u8 * pattarn,u8 address,u8 row,u8 col)
{
	LCD_WriteCommand(0x40+address*8);
	for(u8 i =0 ;i<8;i++)
	{
		LCD_WriteData(pattarn[i]);
	}
	LCD_CursorMove(row,col);
	LCD_WriteData(address);
}

void LCD_WriteFloatNum(f32 num)
{
}
