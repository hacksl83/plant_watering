/*
 * 5110_LCD.c
 *
 * Created: 19.09.2020 14:11:29
 * Author : hacksl
 */ 

//defines and includes
#include <avr/io.h>
#include "SPI.h"
#include "pcd8544.h"
#include <stdint.h>
#include <util/delay.h>
#include "Time.h"
#include "rotary_enc.h"
#include "menu.h"
#include <stdbool.h>
#include "moisture_sensor.h"

//Variable definitions
int8_t rotenc_updown = 0;
int8_t val = 0;

int main(void)
{	
		
		//Init
		spi_MasterInit();										// Init SPI interface for the LCD display
		pump_init();
		PCD8544_Init(PCD8544_LCD_CONTRAST);
		_delay_ms(100); 
		init_time();				// Init the timer for the time and ms counter
		rotenc_init();				// Init the rotary encoder
		moist_sensor_init();		// Init moisture sensor 
		sei();						// global interrupt enable
		PCD8544_Clear();			// clear display
		(*p_func)(0, 0);			// call state function (this is menu_func() at bootup)
		
		// main loop
		while (1)
		{
			// handle up/down of rotenc
			val = rotenc_read4();
			if(val < -1){val = -1;}
			if(val > 1){val = 1;}
			if (val) {
				gPowerSaveTimer = 0; 
				(*p_func)(val, 0);
				val = 0;
			};
			
			// handle button push of rotenc
			if (rotenc_press) {
					gPowerSaveTimer = 0; 
					p_func = p_menu->p_menu_list[menu_item].pFunc;				// set the function pointer to the func of the selected menu item		
					if(p_menu->p_menu_list[menu_item].pFunc == menu_func){		// apply changes below only when changing between menus 
						p_menu = p_menu->p_menu_list[menu_item].pMenu;			// reset the menu pointer 
						p_data = p_menu->pdata;									// set the data pointer to the currently active dataset
						menu_item = 0;											// set menu_items to 0 only when changing between menu and submenu
					}	
					if((p_menu->p_menu_list[menu_item].pFunc == menu_func) || (rotenc_press_old == 0) ){
						PCD8544_Clear(); //clear the screen data when menu changes or when entering a settings menu for the first time
					}
				rotenc_press = 0;
				(*p_func)(0, true); // call the state function
			}
			pump_timer_watering();
			pump_moist_sensor_watering();
			moist_sensor_read_save();
			PCD8544_Powersave();
			
			// refresh display every second. For example to see seconds updating in time menu
			if(gSEC_CHANGE){
				(*p_func)(0,false);
				gSEC_CHANGE = 0;
			}
			
			// refresh the display content
			PCD8544_UpdateArea(0, 0, PCD8544_WIDTH - 1, PCD8544_HEIGHT - 1);
			PCD8544_Refresh();
			_delay_ms(50);
			
		
			
		}

}

