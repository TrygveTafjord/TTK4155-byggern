/*
 * byggernNode1.c
 *
 * Created: 29.08.2023 08:43:04
 * Author : linuse
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "UARTinterface.h"
#include "RAM.h"
#include "ADC.h"
#include "OLED.h"

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



ADC_Calibration ADC_calibrated_values;
ADC_readings ADC_read_values; 

int main(void)
{
	USART_Init(MYUBRR);
	printf("initializing ADC\n\r");
	adc_init();
	xmem_init();
	OLED_init();
	ADC_calibrated_values = pos_calibration(ADC_calibrated_values);
	char* ch = "Hello World!";
	char* ch1 = (char *) 'B';
	volatile char *ext_mem1 = (char *) 0x1000;
	volatile char *ext_mem2 = (char *) 0x1200;
	//ADC_readings data;
	while (1) {
		OLED_reset();
		while(1){
			OLED_write_string(ch, 4, 10);
			_delay_ms(1000);
		}
/*
	printf(" data from channel-0: ");
	data = adc_read(&ADC_calibrated_values);
	
	printf("joystick_x: %8d",data.joystick_x);
	printf("\n\r");
	
	printf("joystick_y: %8d",data.joystick_y);
	printf("\n\r");

	printf("slider_left: %8d",data.slider_left);
	printf("\n\r");
	
	printf("slider_right: %8d",data.slider_right);
	printf("\n\r");*/
	
	
	//OLED_write();
	_delay_ms(100);
	}

}

