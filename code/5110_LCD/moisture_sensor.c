/*
 * moisture_sensor.c
 *
 * Created: 15.07.2021 20:49:29
 *  Author: hacks
 */ 

#include "moisture_sensor.h"

#define SENSOR1_PIN		PINC3
#define SENSOR2_PIN		PINC4
#define SENSOR3_PIN		PINC5
#define SENSOR_DDR		DDRC
#define SENSOR_PORT		PORTC
#define SENSOR_PIN		PINC


uint8_t EEMEM eeprom_moisture_array[3][150] = {0};
uint8_t EEMEM eeprom_idx = 0;
bool moist_sensor_busy = false;

void moist_sensor_init(){
	
	SENSOR_DDR &= ~(1 << SENSOR1_PIN) & ~(1 << SENSOR2_PIN) & ~(1 << SENSOR3_PIN);	//set SENSOR Pins as inputs
	SENSOR_PORT &= ~(1 << SENSOR1_PIN) & ~(1 << SENSOR2_PIN) & ~(1 << SENSOR3_PIN);	 //activate internal pullups
	
	//ADC init
	ADMUX = (1 << REFS0);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);
	
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC)){
		(void) ADC;
	}
	
}

// ADC single measurement, returns 10Bit value
uint8_t moist_sensor_read( uint8_t channel){
	uint16_t temp1;
	uint8_t  temp2;
	
	ADMUX = (ADMUX & ~(0x1F)) | ((channel+2) & 0x1F);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC) ) {   // wait for the conversion to finish
	}
	temp1 = ADC;
	temp2 = (int)(temp1 * MOIST_FACTOR);
	
	return temp2;
	
}

void moist_sensor_read_save(){
	uint8_t i;
	uint8_t idx;
	uint8_t temp2;
	if((gHOUR == 12) && (gMINUTE == 0) && (gSECOND == 1) && !(moist_sensor_busy) ){
		moist_sensor_busy = true;
		idx = eeprom_read_byte(&eeprom_idx);
		for(i = 0; i <= 2; i++){
			
			temp2 = moist_sensor_read(i+1);
			eeprom_update_byte(&(eeprom_moisture_array[i][idx]), temp2);
		}
		eeprom_write_byte(&eeprom_idx, idx+1);
	}
	
	if((gHOUR == 12) && (gMINUTE == 0) && (gSECOND == 2)){
		moist_sensor_busy = false;
	}
	
}