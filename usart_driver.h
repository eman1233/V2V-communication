#include <avr/io.h>
//#include "Platform_Types.h"

#define       FCLK_SYSTEM     8000000UL

void          usart_init(unsigned short int baudrate);
void          usart_putc(unsigned char data);
unsigned char usart_getc(void);
void          usart_puts(char *str);
//void        USART_SendNum(u16 Num);
