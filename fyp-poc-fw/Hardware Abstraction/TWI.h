/*
 * TWI.h
 *
 * Created: 6/19/2023 5:59:15 PM
 *  Author: dewmithr
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <stdbool.h>

#define F_CPU 16000000
#define SLAVE_ADDRESS 0x68
#define BIT_RATE 100000

void TWI_init();

void TWI_WAIT();

void TWI_STOP();

void TWI_START();

void TWI_REPEATED_START();

void TWI_DATA_WRITE(uint8_t data );


void TWI_ADDRESS_WRITE(uint8_t address , char mode );

uint8_t TWI_READ();

bool check_status();

#endif /* TWI_H_ */