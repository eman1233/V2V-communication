/*
 * LCD_Cfg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define BIT_4_MODE 0

#define BIT_8_MODE 1


#define LcdMode  BIT_4_MODE

#define RS PINA0_

#define RW PINA1_

#define E  PINA2_

#if LcdMode==BIT_8_MODE

   #define PORTLCD PA

#elif LcdMode==BIT_4_MODE

   #define D4  PINA3_

   #define D5  PINA4_

   #define D6  PINA5_

   #define D7  PINA6_

#endif

#endif /* LCD_CFG_H_ */
