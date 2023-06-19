/*
 * TWI.c
 *
 * Created: 6/19/2023 5:58:59 PM
 *  Author: dewmithr
 */ 

#include "xc.h"
#include "TWI.h"


uint8_t count = 0;
uint8_t byte_counter = 0;


void TWI_init(){
	
	TWBR = (((F_CPU/BIT_RATE) - 16)/2)&0xff;
	TWSR &= ~0x03;
	TWCR = (1<<TWEA)|(1<<TWEN)|(1<<TWIE);
}


void TWI_WAIT(){
	while (!(TWCR & (1<<TWINT)));
}

void TWI_STOP(){
	TWI_WAIT();
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void TWI_START(){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	TWI_WAIT();
	if(!(check_status())){
		TWI_STOP();
	}
}

void TWI_REPEATED_START(){
	TWI_WAIT();
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	if(!(check_status())){
		TWI_STOP();
	}
}

void TWI_DATA_WRITE(uint8_t data ){
	TWI_WAIT();
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	if(!(check_status())){
		TWI_STOP();
	}
}


void TWI_ADDRESS_WRITE(uint8_t address , char mode ){
	
	TWI_WAIT();
	if(mode == 'R' || mode == 'r'){
		TWDR = address<<1 | 1;
	}
	else if(mode == 'W' || mode == 'w'){
		TWDR = address<<1 | 0;
	}
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	if(!(check_status())){
		TWI_STOP();
	}
}

uint8_t TWI_READ(){
	
	count++;
	TWI_WAIT();
	uint8_t tmp = TWDR;
	if(count!=byte_counter){
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	}
	else{
		TWCR = (1<<TWINT)|(1<<TWEN);
	}
	
	return tmp;
}

bool check_status(){
	uint8_t tmp = TWSR & 0xF8;
	switch(tmp){
		case 0x08: //a start condition has been transmitted
		return true;
		break;
		case 0x18: //SLA_W + ACK
		return true;
		break;
		default:
		return true;
		break;
	}
}


