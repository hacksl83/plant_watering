/*
 * pump.h
 *
 * Created: 06.06.2021 16:50:35
 *  Author: hacks
 */ 


#ifndef PUMP_H_
#define PUMP_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "Time.h"
#include "menu.h"

#define PUMP_BLOCK_TIME_SEC 20

void pump_init();
void pump_switch(uint8_t pump, bool pump_sw);
void pump_watering();



#endif /* PUMP_H_ */