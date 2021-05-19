/*
 * LcdService.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#ifndef LCDSERVICE_H_
#define LCDSERVICE_H_

void LCD_WriteString(u8 *str);

void LCD_CursorMove(u8 row,u8 col);

void LCD_Clear(void);

void LCD_WriteNum(s16 num);

void LCD_WriteNumInBinary(u8 num);

void LCD_DrowPattarn(u8 * pattarn,u8 address,u8 row,u8 col);

void LCD_WriteNum_4D(u16 num);

void LCD_WriteNum_2D(u16 num);

void LCD_WriteFloatNum(f32 num);

#endif /* LCDSERVICE_H_ */
