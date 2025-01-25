/*
 * Time.h
 *
 * Created: 27.09.2020 01:27:25
 *  Author: hacksl
 */ 


#ifndef TIME_H_
#define TIME_H_

//header

#define F_CPU	4000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "pcd8544.h"
#include <stdlib.h>
#include <stdbool.h>
#include "rotary_enc.h"
#include "BCD.h"

#define LCD_TIMEOUT_SEC 60

// Day of the week
typedef enum {
	monday,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday
} WeekDay_t;

extern volatile uint16_t gMSECOND;
extern char gSECOND;
extern bool gSEC_CHANGE;
extern char gMINUTE;
extern char gHOUR;
extern char gDAY;
extern char gMONTH;
extern unsigned int gYEAR;
extern WeekDay_t WeekDay;
extern char gPowerSaveTimer;
extern volatile bool sec_flag;				//flag is set to 1 if time (sec) changes
extern char WeekDay_s[7][4];
extern char MonthLength[13];

void init_time(void);
void show_time();
void show_date();
void show_2digit_number(char number, PCD8544_Pixel_t color);
void show_4digit_number(uint16_t number, PCD8544_Pixel_t color );

#endif /* TIME_H_ */