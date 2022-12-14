
#ifndef USART_LIB
#define USART_LIB

#include <avr/io.h>
#include <avr/interrupt.h>


void USART_Init( unsigned int ubrr);

void USART_Transmit( unsigned char data );

unsigned char USART_Receive( void );

#endif