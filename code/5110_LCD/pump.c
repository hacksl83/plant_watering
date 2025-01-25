/*
 * pump.c
 *
 * Created: 06.06.2021 15:24:43
 *  Author: hacksl
 */ 

#include "pump.h"

#define PUMP1_PIN		PINC0
#define PUMP2_PIN		PINC1
#define PUMP3_PIN		PINC2
#define PUMP_DDR		DDRC
#define PUMP_PORT		PORTC         



void pump_init()
{
	PORTC |= (1 << PUMP1_PIN) | (1 << PUMP2_PIN) | (1 << PUMP3_PIN);
	PUMP_DDR |= (1 << PUMP1_PIN) | (1 << PUMP2_PIN) | (1 << PUMP3_PIN);
	//PORTC &= ~(1 << PUMP1_PIN) & ~(1 << PUMP2_PIN) & ~(1 << PUMP3_PIN);
	
	
}

void pump_switch(uint8_t pump, bool pump_sw){
	pump_sw = !pump_sw;
	
	switch(pump){
		case 1: PORTC = (PORTC & ~(1 << PUMP1_PIN)) | (pump_sw << PUMP1_PIN);break;
		case 2: PORTC = (PORTC & ~(1 << PUMP2_PIN)) | (pump_sw << PUMP2_PIN);break;
		case 3: PORTC = (PORTC & ~(1 << PUMP3_PIN)) | (pump_sw << PUMP3_PIN);break;
		}
		
}


void pump_timer_watering(){
	
	unsigned char weekday_bin = 1 << WeekDay;
	float temp;
	uint16_t temp1;
	uint8_t i;
	
	// --------------------------------
	// ---------- PUMP1 ---------------
	// --------------------------------
	uint8_t water_min = 0;
	uint16_t water_sec = 0;
	uint8_t stoptime_hour = 0;
	uint8_t stoptime_min = 0;
	uint8_t stoptime_sec = 0;
	
	
	for (i = 0; i < 3; i++){
		// start pump1
		if(pump_data_array[i]->pump_arm){
			if((pump_data_array[i]->pump_hour == gHOUR) && (pump_data_array[i]->pump_min == gMINUTE) && (gSECOND == 0) && (pump_data_array[i]->pump_day.Reg & weekday_bin) && (pump_data_array[i]->pump_active == 0)){
				pump_data_array[i]->pump_active = true;
				pump_switch(i+1, true);			
			}	
		}
		
		//stop pump1
		if(pump_data_array[i]->pump_active){
			temp = pump_data_array[i]->pump_vol / pump_data_array[i]->pump_calib * 60; //watering time in sec
			water_sec = (int)temp; // round to int to get seconds
			while(water_sec >= 60){
				water_min++;
				water_sec -= 60;
			}
			
			stoptime_sec = water_sec; // calculate the stop time as the pump_time + watering_time
			stoptime_min = pump_data_array[i]->pump_min + water_min;
			while(stoptime_min >= 60){
				stoptime_hour++;
				stoptime_min -= 60;
			}
			stoptime_hour += pump_data_array[i]->pump_hour;
			
			if((stoptime_hour == gHOUR) && (stoptime_min == gMINUTE) && (stoptime_sec == gSECOND)){		// if the stop time is reached then stop watering
				pump_data_array[i]->pump_active = false;		// set the pump active status to low
				pump_switch(i+1, false);				// stop the pump
			}	
		}
	}
};


void pump_moist_sensor_watering(){
	uint8_t water_min = 0;
	uint16_t water_sec = 0;
	uint8_t stoptime_hour = 0;
	uint8_t stoptime_min = 0;
	uint8_t stoptime_sec = 0;
	float temp;
	uint8_t data;
	uint8_t i;
	
	for (i = 0; i < 3; i++){
		
		// check if moisture value is below moist threshold. If yes then start the pump
		if (moist_data_array[i]->moist_sensor_arm && !pump_data_array[i]->pump_active && !moist_data_array[i]->pump_block){
			data = moist_sensor_read(moist_data_array[i]->moist_sensor_nr);
			if (data <= moist_data_array[i]->moist_sensor_thres){
				pump_data_array[i]->pump_active = true;
				moist_data_array[i]->pump_hour = gHOUR;
				moist_data_array[i]->pump_min = gMINUTE;
				moist_data_array[i]->pump_sec = gSECOND;
				pump_switch(i+1, true);	
			}
		}
		
		//stop pump
		if(pump_data_array[i]->pump_active){
			temp = moist_data_array[i]->pump_vol/pump_data_array[i]->pump_calib * 60; //watering time in sec
			water_sec = (int)temp; // round to int to get seconds
			while(water_sec >= 60){
				water_min++;
				water_sec -= 60;
			}
			
			stoptime_sec = water_sec + moist_data_array[i]->pump_sec; // calculate the stop time as the pump_time + watering_time
			stoptime_min = moist_data_array[i]->pump_min + water_min;
			while(stoptime_min >= 60){
				stoptime_hour++;
				stoptime_min -= 60;
			}
			stoptime_hour += moist_data_array[i]->pump_hour;
			
			if((stoptime_hour == gHOUR) && (stoptime_min == gMINUTE) && (stoptime_sec == gSECOND)){		// if the stop time is reached then stop watering
				pump_data_array[i]->pump_active = false;		// set the pump active status to low
				pump_switch(i+1, false);				// stop the pump
				moist_data_array[i]->pump_block = true;
			}
			
			
		}
		
		// Check pump block
		if(moist_data_array[i]->pump_block){
			temp = moist_data_array[i]->pump_vol/pump_data_array[i]->pump_calib * 60; //watering time in sec
			water_sec = (int)temp; // round to int to get seconds
			
			stoptime_sec = moist_data_array[i]->pump_sec + PUMP_BLOCK_TIME_SEC;
			
			while(stoptime_sec >= 60){
				stoptime_min++;
				stoptime_sec -= 60;
			}
			
			stoptime_min += moist_data_array[i]->pump_min;
			while(stoptime_min >= 60){
				stoptime_hour++;
				stoptime_min -= 60;
			}
			stoptime_hour += moist_data_array[i]->pump_hour;
			
			if((stoptime_hour == gHOUR) && (stoptime_min == gMINUTE) && (stoptime_sec == gSECOND)){		// if the stop time is reached then stop watering
				moist_data_array[i]->pump_block = false;
			}
			
			
		}
	}
}