/*
 * can_driver.c
 *
 * Created: 03.10.2023 16:53:08
 *  Author: trygvemt
 */ 

#include "can_driver.h"
#include "mcp2515.h"


void can_init(){
	mcp2515_init();
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK); //loopback mode
	mcp2515_write(MCP_CANINTE, MCP_RX0IF|MCP_RX1IF);
	MCUCR |= (1<<ISC01);
	GICR |= (1 << INT0);
	sei();
	CAN_message_t message;
	message.id = 0x00;
	message.length = 2;
	message.data[0] = 0xF0;
	message.data[1] = 0xF0;
}

void can_sendMessage(CAN_message_t *msg){
	//Assuming TX buffer 0 is used for simplicity
	// TODO: Ideally, check which TX buffer is free
	
	mcp2515_write(TXB0SIDH, (uint8_t)(msg->id >> 3));
	mcp2515_write(TXB0SIDL, (uint8_t)(msg->id << 5));
	mcp2515_write(TXB0DLC, msg->length);
	for (uint8_t i=0;i<msg->length;i++){
		mcp2515_write(TXB0D0+i, msg->data[i]);
	}
	mcp2515_request_to_send(0b001);
}

CAN_message_t can_recieveMessage(){
	printf("message recieved\n\r");
	uint8_t buffer = 0x3;
	CAN_message_t msg;
	buffer = buffer & mcp2515_read(MCP_CANINTF);
	msg = mcp2515_read_rx_buffer(buffer);
	printf("data1: %d\n\r", msg.data[0]);
	return msg;
}