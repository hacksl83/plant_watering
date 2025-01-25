/*
 * menu.h
 *
 * Created: 01.05.2021 11:22:35
 *  Author: hacksl
 */ 


#ifndef MENU_H_
#define MENU_H_
#include <stdint.h>
#include <stdlib.h>
#include "pcd8544.h"
#include "rotary_enc.h"
#include "Time.h"
#include "moisture_sensor.h"

#define VERSION "v1.0.0"
#define AUTHOR "Philipp Hack"
#define MOIST_FACTOR_PLOT 0.2


// Datatypes

typedef struct MENU_ITEM MENU_ITEM;
typedef struct MENU_ID MENU_ID;
typedef union PUMP_DAY PUMP_DAY;
typedef struct PUMP_DATA PUMP_DATA;
typedef struct MOIST_SENSOR_DATA MOIST_SENSOR_DATA;


struct MENU_ITEM {

	int8_t      menu_item_nr;
	char		menu_item_text[15];
	const __flash MENU_ID *pMenu;
	void (*pFunc)(int, bool);
};

struct MENU_ID {
	
	int8_t	num_items;
	const __flash MENU_ITEM *p_menu_list;
	char menu_title[15];
	void *pdata;
};


union PUMP_DAY {
	char Reg;
		
	struct{
		char monday:	1;
		char tuesday:	1;
		char wednesday:	1;
		char thursday:	1;
		char friday:	1;
		char saturday:	1;
		char sunday:	1;
		} Bit; 
};


struct PUMP_DATA {
	
	unsigned char pump_hour;
	unsigned char pump_min;
	PUMP_DAY pump_day;
	uint16_t pump_vol;		// watering amount in ml 
	float pump_calib;		// amount of litres pumped in 10sec
	bool pump_arm;			// arm the pump
	bool pump_active;		// is pump currently watering ?
	
};

struct MOIST_SENSOR_DATA {
	
	uint8_t moist_sensor_nr;
	float moist_sensor_thres;
	bool moist_sensor_arm;
	uint16_t pump_vol;			// watering amount in ml 
	unsigned char pump_hour;	// Time when the measured moisture value went below the threshold 
	unsigned char pump_min;
	unsigned char pump_sec;
	bool pump_block;
	
};


/*MENU_ITEM test;
uint16_t* pointer;
pointer = &test;
((MENU_ITEM*)pointer).menu_item_nr
*/

// Variables 

extern void *p_data;
const __flash extern  MENU_ID *p_menu;
extern int8_t menu_item;
extern int8_t func_item;
extern int8_t func_setting;
extern bool func_setting_active;
extern int8_t frame;
extern void (*p_func)(int8_t, bool);
extern const __flash MENU_ID main_menu;
extern const __flash MENU_ID pump1_menu;
extern const __flash MENU_ID pump2_menu;
extern const __flash MENU_ID pump3_menu;

extern PUMP_DATA pump1_data;
extern PUMP_DATA pump2_data;
extern PUMP_DATA pump3_data;

extern PUMP_DATA * pump_data_array[3];

extern MOIST_SENSOR_DATA moist1_data;
extern MOIST_SENSOR_DATA moist2_data;
extern MOIST_SENSOR_DATA moist3_data;

extern MOIST_SENSOR_DATA * moist_data_array[3];

// Function Declaration

void menu_func(int8_t, bool);
void version_func(int8_t val, bool press);
void lcdcontrast_func(int8_t val, bool press);	
void time_func(int8_t val, bool press);
void pump_time_func(int8_t val, bool press);
void pump_day_func(int8_t val, bool press);
void set_time_func(int8_t val, bool press);
void pump_vol_func(int8_t val, bool press);
void pump_cal_func(int8_t val, bool press);
void pump_arm_func(int8_t val, bool press);
void pump_watering();
void moist_level_func(int8_t val, bool press);
void moist_eeprom_func(int8_t val, bool press);
void moist_vol_func(int8_t val, bool press);
void moist_arm_func(int8_t val, bool press);
void moist_thres_func(int8_t val, bool press);
#endif /* MENU_H_ */