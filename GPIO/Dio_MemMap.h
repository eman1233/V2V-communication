/*********************************************************

     * Name              : Eman Megahed
	 * Data              : 6/1/2021
	 * Version           : 1.0
	 * SWC               : DIO

**********************************************************/

#ifndef DIO_MEMMAP_H_
#define DIO_MEMMAP_H_

#define PORTA_REG             *((volatile u8*)0X3B)
#define DDRA_REG              *((volatile u8*)0X3A)
#define PINA_REG              *((volatile u8*)0X39)

#define PORTB_REG             *((volatile u8*)0X38)
#define DDRB_REG              *((volatile u8*)0X37)
#define PINB_REG              *((volatile u8*)0X36)

#define PORTC_REG             *((volatile u8*)0X35)
#define DDRC_REG              *((volatile u8*)0X34)
#define PINC_REG              *((volatile u8*)0X33)

#define PORTD_REG             *((volatile u8*)0X32)
#define DDRD_REG              *((volatile u8*)0X31)
#define PIND_REG              *((volatile u8*)0X30)

#define READ_PIN(PORT,PIN)    ((PORT>>PIN)&1)
#define SET_PIN(PORT,PIN)    (PORT=PORT|(1<<PIN))
#define CLEAR_PIN(PORT,PIN)  (PORT&=~(1<<PIN))
#define TOGGLE_PIN(PORT,PIN) (PORT^=(1<<PIN))

#define READ_BIT(PORT,BIT)    ((PORT>>BIT)&1)

#endif /* DIO_MEMMAP_H_ */
