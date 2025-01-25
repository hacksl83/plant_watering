/*
 * moisture_sensor.h
 *
 * Created: 15.07.2021 20:49:47
 *  Author: hacks
 */ 


#ifndef MOISTURE_SENSOR_H_
#define MOISTURE_SENSOR_H_

#define MOIST_FACTOR 0.09775 // 100/1024 -> convert 0 to 1024 ADC moist sensor value into percent

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include "Time.h"

extern uint8_t EEMEM eeprom_moisture_array[3][150];
extern uint8_t EEMEM eeprom_idx;

void moist_sensor_init();
uint8_t moist_sensor_read(uint8_t channel);
void moist_sensor_read_save();

#endif /* MOISTURE_SENSOR_H_ */