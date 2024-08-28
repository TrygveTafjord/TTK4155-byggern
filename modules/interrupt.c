/*
 * interrupt.c
 *
 * Created: 12.09.2023 15:15:41
 *  Author: trygvemt
 */ 

#include "interrupt.h"
#include "can_driver.h"

uint8_t button_pressed = 0;

void interrupt_init(){

	//Konfigurerer PE0 (INT0) som input
	DDRE &= ~(1 << PE0);
	//Aktiverer pull-up motstand for PE0
	PORTE |= (1 << PE0);
	//Konfigurerer INT0 for fallende edge-triggered interrupt
	//MCUCR |= (1 << ISC);
	MCUCSR &= ~(1 << ISC2);
	//Aktiverer INT0 interrupten
	GICR |= (1 << INT2);
	
	MCUCR |= (1<<ISC01);
	GICR |= (1 << INT0);
	
	sei();
	
	printf("interrupt initialized\n\r");
}


ISR(INT2_vect){
	//Interrupt håndteringskode
	button_pressed = 1;
	
}

ISR(INT0_vect){
	can_recieveMessage();
}