/*
 * IncFile1.h
 *
 * Created: 29.08.2023 14:53:02
 *  Author: linuse
 */ 


#ifndef UARTinterface_H_
#define UARTinterface_H_

#include <avr/io.h>

void USART_Init( unsigned int ubrr );void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );






#endif /* UARTinterface */