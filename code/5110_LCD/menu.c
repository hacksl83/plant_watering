/*
 * menu.c
 *
 * Created: 01.11.2020 18:52:42
 *  Author: hacksl
 */ 

#include "menu.h"
#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))


PUMP_DATA pump1_data = {12, 0, 1, 200, 1500, true, false};
PUMP_DATA pump2_data = {12, 1, 1, 100, 1500, true, false};
PUMP_DATA pump3_data = {12, 1, 1,  50, 1500, true, false};

PUMP_DATA * pump_data_array[3] = {&pump1_data, &pump2_data, &pump3_data};

MOIST_SENSOR_DATA moist1_data = {1, 50, false, 200, 12, 0, 0, false};
MOIST_SENSOR_DATA moist2_data = {2, 60, false, 200, 12, 0, 0, false};
MOIST_SENSOR_DATA moist3_data = {3, 70, false, 200, 12, 0, 0, false};

MOIST_SENSOR_DATA * moist_data_array[3] = {&moist1_data, &moist2_data, &moist3_data};

// define moisture sensor menu list
const __flash MENU_ITEM moist_sensor1_menu_items[] = {
	//item number       //item text         //state function
	{0,             "moist level",		NULL,					moist_level_func},
	{1,             "moist eeprom",		NULL,					moist_eeprom_func},
	{2,             "moist thresh",		NULL,					moist_thres_func},
	{2,             "moist vol",		NULL,					moist_vol_func},
	{3,             "moist on/off",		NULL,					moist_arm_func},
	{4,             "back",				&pump1_menu,			menu_func}
};

const __flash MENU_ID moist_sensor1_menu = {
	ARRAY_LENGTH(moist_sensor1_menu_items),
	moist_sensor1_menu_items,
	"moist1 menu",
	&moist1_data
};

// define moisture sensor menu list
const __flash MENU_ITEM moist_sensor2_menu_items[] = {
	//item number       //item text         //state function
	{0,             "moist level",		NULL,					moist_level_func},
	{1,             "moist eeprom",		NULL,					moist_eeprom_func},
	{2,             "moist thresh",		NULL,					moist_thres_func},
	{2,             "moist vol",		NULL,					moist_vol_func},
	{3,             "moist on/off",		NULL,					moist_arm_func},
	{4,             "back",				&pump2_menu,			menu_func}
};

const __flash MENU_ID moist_sensor2_menu = {
	ARRAY_LENGTH(moist_sensor2_menu_items),
	moist_sensor2_menu_items,
	"moist2 menu",
	&moist2_data
};

// define moisture sensor menu list
const __flash MENU_ITEM moist_sensor3_menu_items[] = {
	//item number       //item text         //state function
	{0,             "moist level",		NULL,					moist_level_func},
	{1,             "moist eeprom",		NULL,					moist_eeprom_func},
	{2,             "moist thresh",		NULL,					moist_thres_func},
	{2,             "moist vol",		NULL,					moist_vol_func},
	{3,             "moist on/off",		NULL,					moist_arm_func},
	{4,             "back",				&pump3_menu,			menu_func}
};

const __flash MENU_ID moist_sensor3_menu = {
	ARRAY_LENGTH(moist_sensor3_menu_items),
	moist_sensor3_menu_items,
	"moist3 menu",
	&moist3_data
};
		
		
// define pump1 menu list
const __flash MENU_ITEM pump1_menu_items[] = {
	//item number       //item text         //state function
	{0,             "set time",			NULL,					pump_time_func},
	{1,             "set day",          NULL,					pump_day_func},
	{2,             "set vol",			NULL,					pump_vol_func},
	{3,             "pump calib",		NULL,					pump_cal_func},
	{4,             "timer on/off",			NULL,				pump_arm_func},
	{5,             "moist sensor",		&moist_sensor1_menu,	menu_func},
	{7,             "back",				&main_menu,				menu_func}

};

const __flash MENU_ID pump1_menu = {
	ARRAY_LENGTH(pump1_menu_items),
	pump1_menu_items,
	"pump1 menu",
	&pump1_data
};

// define pump2 menu list
const __flash MENU_ITEM pump2_menu_items[] = {
	//item number       //item text         //state function
	{0,             "set time",			NULL,					pump_time_func},
	{1,             "set day",          NULL,					pump_day_func},
	{2,             "set vol",			NULL,					pump_vol_func},
	{3,             "pump calib",		NULL,					pump_cal_func},
	{4,             "timer on/off",		NULL,					pump_arm_func},
	{5,             "moist sensor",		&moist_sensor2_menu,	menu_func},
	{7,             "back",				&main_menu,				menu_func}

};

 const __flash MENU_ID pump2_menu = {
	ARRAY_LENGTH(pump2_menu_items),
	pump2_menu_items,
	"pump2 menu",
	&pump2_data
};

// define pump3 menu list
const __flash MENU_ITEM pump3_menu_items[] = {
	//item number       //item text         //state function
	{0,             "set time",			NULL,					pump_time_func},
	{1,             "set day",          NULL,					pump_day_func},
	{2,             "set vol",			NULL,					pump_vol_func},
	{3,             "pump calib",		NULL,					pump_cal_func},
	{4,             "timer on/off",			NULL,					pump_arm_func},
	{5,             "moist sensor",		&moist_sensor3_menu,	menu_func},
	{7,             "back",				&main_menu,				menu_func}

};

const __flash MENU_ID pump3_menu = {
	ARRAY_LENGTH(pump3_menu_items),
	pump3_menu_items,
	"pump3 menu",
	&pump3_data
};




// define main_menu list
const __flash MENU_ITEM main_menu_items[] = {
	//item number       //item text         //state				//state func
	{0,             "time",             NULL,					time_func},
	{1,             "set time",         NULL,					set_time_func},	
	{2,             "pump1",            &pump1_menu,			menu_func},
	{3,             "pump2",            &pump2_menu,			menu_func},
	{4,             "pump3",            &pump3_menu,			menu_func},
	{5,             "LCD contrast",		NULL,					lcdcontrast_func},
	{6,             "about",			NULL,					version_func},

};

const __flash MENU_ID main_menu = {
	ARRAY_LENGTH(main_menu_items),
	main_menu_items,	
	"main menu"
};



//set the pointer to the currently active menu to -> main_menu
const __flash MENU_ID *p_menu = (const __flash MENU_ID *)&main_menu;
void (*p_func)(int8_t, bool) = menu_func;
void *p_data = NULL;


int8_t menu_item = 0; //set the currently selected menu item to 0
int8_t func_item = 0; 
int8_t func_setting = 0;
bool func_setting_active = false;
int8_t frame = 0;
int8_t rotenc_updown;

// state function that handles the main and submenus
void menu_func(int8_t val, bool press){
	int8_t i = 0;
	int8_t j = 0;
	

	// If rot-enc was turned:
	menu_item = (menu_item + val) ;	// val contains the number of pos changes of rot enc. The currently selected item (menu_item) is updated by this value    
	if (menu_item >= p_menu->num_items) {
		menu_item = p_menu->num_items-1;
	}
	if (menu_item  < 0) {
		menu_item = 0;
	}
	
	// LCD can only show 4 menu items. If the selected menu_item exceeds the last item on the page then set frame variable that contains the new top menu_item.
	if (menu_item > 3) {
		frame = menu_item - 3;		
	}
	if (menu_item < frame) {
		frame = menu_item;
	}
		
	// print Menu Title
	PCD8544_PutTitle_f(p_menu->menu_title);

	// Print Menu Items 
	// Print frame item as new top item and the 3 items that come after frame. Print the selected item with iverted color.
	for (j=0; j<4; j++){			
		if (menu_item == (frame + j)){
			PCD8544_PutSub_f(p_menu->p_menu_list[frame + j].menu_item_text, j+1, PCD8544_Pixel_Set);
		}else {
			PCD8544_PutSub_f(p_menu->p_menu_list[frame + j].menu_item_text, j+1, PCD8544_Pixel_Clear);
		}
	} 
}

// state function that shows the FW version page
void version_func(int8_t val, bool press){

	PCD8544_Clear();	
	PCD8544_GotoXY(0, Y_ROW1);
	PCD8544_Puts(strcat("FW Ver: ", VERSION), PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
	PCD8544_GotoXY(0, Y_ROW2);
	PCD8544_Puts(strcat("Author: ", AUTHOR), PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
	PCD8544_GotoXY(X_ROW4, Y_ROW4);
	PCD8544_SetArea(PCD8544_y-2, PCD8544_y+6, 14, 65, 1);	
	PCD8544_Puts("back", PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
	
	if (press && rotenc_press_old){
		p_func = menu_func;
		p_menu = &main_menu;
		PCD8544_Clear();
		(*p_func)(0,0);
		rotenc_press_old = 0;
		return;
	}
	rotenc_press_old = 1;
	
};

// state function that shows the LCD contrast page
void lcdcontrast_func(int8_t val, bool press) {

	if (val){
		func_item += val;
		contrast = PCD8544_LCD_CONTRAST + func_item * 2;
	
	
		// set VOP
		if (contrast > 0x7F) {
			contrast = 0x7F;
		}
		if (contrast <  0){
			contrast = 0;
		}
	
	PCD8544_Init(contrast);
	} 
	
	// print Menu Title
	PCD8544_PutTitle("LCDcontrast");
	
	PCD8544_GotoXY(X_ROW2, Y_ROW2);	// Go to Pixel x=0, y=0 position on the LCD display
	PCD8544_SetArea(PCD8544_y-2, PCD8544_y + ROW_HEIGHT, X_ROW0, X_ROW0 + ROW_LENGTH, 0);	// Clear previous content in that row
	show_4digit_number(contrast, PCD8544_Pixel_Clear );
	
	PCD8544_GotoXY(X_ROW4, Y_ROW4);
	PCD8544_SetArea(PCD8544_y-2, PCD8544_y+6, 14, 65, 1);	// Set the row of the selected item to black then write the item text in white
	PCD8544_Puts("back", PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
	
	if (press && rotenc_press_old){
		p_func = menu_func;
		p_menu = &main_menu;
		PCD8544_Clear();
		(*p_func)(0,0);
		rotenc_press_old = 0;
		func_item = 0;
		
		return;
	}
	rotenc_press_old = 1;
};

void time_func(int8_t val, bool press){
	
	if(rotenc_press_old == 0){
		PCD8544_Clear();
	}
	
	// print Menu Title
	PCD8544_PutTitle("Time");
	PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
	PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
	PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	
	PCD8544_GotoXY(X_ROW1+25, Y_ROW1); show_time();
	PCD8544_GotoXY(X_ROW2+25, Y_ROW2); show_date();
	PCD8544_GotoXY(X_ROW3+25, Y_ROW3); PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
	PCD8544_Refresh();
	
	if (press && rotenc_press_old){
		p_func = menu_func;
		PCD8544_Clear();
		rotenc_press_old = 0;
		rotenc_press = 0;
		(*p_func)(0,0);
		return;
	}
	rotenc_press_old = 1;
}

void pump_time_func(int8_t val, bool press) {
	
	if(rotenc_press_old == 0){
			PCD8544_Clear();	
	}

	int8_t temp = 0;

	// If rot-enc was turned:
	if (val && !func_setting_active){
		func_item += val ;	// val contains the number of pos changes of rot enc. The currently selected item (func_item) is updated by this value
		if (func_item < 0) {
			func_item = 2;
		}
		func_item = func_item % 3;
	} 
	
	// print Menu Title
	PCD8544_PutTitle("set time");	

	switch (func_item) {
		case 0: {

			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
					func_setting = ((PUMP_DATA*)(p_data))->pump_hour;
	
				if(val){
					func_setting += val;
					if(func_setting < 0){ func_setting = 23;}
					func_setting = func_setting % 24;
					((PUMP_DATA*)(p_data))->pump_hour = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;	
			}
		
		// plot	
		PCD8544_PutSub("Time:", PCD8544_Row2, PCD8544_Pixel_Clear);
		PCD8544_GotoXY(X_ROW2+25, Y_ROW2);
		show_2digit_number(((PUMP_DATA*)(p_data))->pump_hour , PCD8544_Pixel_Set);
		PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
		show_2digit_number(((PUMP_DATA*)(p_data))->pump_min , PCD8544_Pixel_Clear);
		PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);		
		break;
		}
		case 1: {
			
			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
					func_setting = ((PUMP_DATA*)(p_data))->pump_min;
				
				if(val){
					func_setting += val;
					if(func_setting < 0){ func_setting = 59;}
					func_setting = func_setting % 60;
					((PUMP_DATA*)(p_data))->pump_min = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;
			}
		
		// plot
		PCD8544_PutSub("Time:", PCD8544_Row2, PCD8544_Pixel_Clear);
		PCD8544_GotoXY(X_ROW2+25, Y_ROW2);
		show_2digit_number(((PUMP_DATA*)(p_data))->pump_hour , PCD8544_Pixel_Clear);
		PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
		show_2digit_number(((PUMP_DATA*)(p_data))->pump_min , PCD8544_Pixel_Set);
		PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
		break;
		}
		
		case 2: {
			// plot
			PCD8544_PutSub("Time:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2);
			show_2digit_number(((PUMP_DATA*)(p_data))->pump_hour , PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(((PUMP_DATA*)(p_data))->pump_min , PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			
			if (press && rotenc_press_old){
				p_func = menu_func;
				PCD8544_Clear();
				(*p_func)(0,0);
				rotenc_press_old = 0;
				return;
			}		
		break;
		}				
	}
	rotenc_press_old = 1;
	
}

void set_time_func(int8_t val, bool press) {
	
	if(rotenc_press_old == 0){
		PCD8544_Clear();
	}

	int8_t temp = 0;

	// If rot-enc was turned:
	if (val && !func_setting_active){
		func_item += val ;	// val contains the number of pos changes of rot enc. The currently selected item (func_item) is updated by this value
		if (func_item < 0) {
			func_item = 6;
		}
		func_item = func_item % 7;
	}
	

	

	switch (func_item) {
		case 0: {

			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
				func_setting = gHOUR;
				
				if(val){
					func_setting += val;
					if(func_setting < 0){ func_setting = 23;}
					func_setting = func_setting % 24;
					gHOUR = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;
			}
			
			// plot
				// print Menu Title
			PCD8544_PutTitle("set time");
			PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW1+25, Y_ROW1);
			show_2digit_number(gHOUR , PCD8544_Pixel_Set);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMINUTE, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2); 
			show_2digit_number(gDAY, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMONTH, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_4digit_number(gYEAR, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW3+25, Y_ROW3);
			PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
			break;
		}
		case 1: {
			
			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
				func_setting = gMINUTE;
				
				if(val){
					func_setting += val;
					if(func_setting < 0){ func_setting = 59;}
					func_setting = func_setting % 60;
					gMINUTE = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;
			}
			
			// plot
			PCD8544_PutTitle("set time");
			PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW1+25, Y_ROW1);
			show_2digit_number(gHOUR , PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMINUTE , PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2); 
			show_2digit_number(gDAY, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMONTH, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_4digit_number(gYEAR, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW3+25, Y_ROW3);
			PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
			break;
		}
		
		case 2: {

			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
				func_setting = gDAY;
				uint8_t length;
				length = month_length(gYEAR, (uint8_t)gMONTH);
				
				if(val){
					func_setting += val;
					if(func_setting < 1){ func_setting = length;}
					func_setting = func_setting % (length+1);
					if(func_setting == 0){func_setting = 1;}
					gDAY = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;
			}
			
			// plot
			PCD8544_PutTitle("set time");
			PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW1+25, Y_ROW1);
			show_2digit_number(gHOUR , PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMINUTE, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2); 
			show_2digit_number(gDAY, PCD8544_Pixel_Set);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMONTH, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_4digit_number(gYEAR, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW3+25, Y_ROW3); 
			PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
			break;
		}
		
		case 3: {

			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
				func_setting = gMONTH;
				
				if(val){
					func_setting += val;
					if(func_setting < 1){ func_setting = 12;}
					func_setting = func_setting % (13);
					if(func_setting == 0){func_setting = 1;}
					gMONTH = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;
			}
			
			// plot
			PCD8544_PutTitle("set time");
			PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW1+25, Y_ROW1);
			show_2digit_number(gHOUR , PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMINUTE, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2); 
			show_2digit_number(gDAY, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMONTH, PCD8544_Pixel_Set);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_4digit_number(gYEAR, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW3+25, Y_ROW3); 
			PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
			break;
		}
		
		case 4: {

			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
				func_setting = gYEAR;
				
				if(val){
					func_setting += val;
					if(func_setting < 1){ func_setting = 2000;}
						if(func_setting > 9999){ func_setting = 2000;}
					gYEAR = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;
			}
			
			// plot
			PCD8544_PutTitle("set time");
			PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW1+25, Y_ROW1);
			show_2digit_number(gHOUR , PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMINUTE, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2); 
			show_2digit_number(gDAY, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMONTH, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_4digit_number(gYEAR, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW3+25, Y_ROW3); 
			PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
			break;
		}
		
		case 5: {

			if ((press && rotenc_press_old) || (rotenc_press_old && func_setting_active)){
				func_setting = WeekDay;
				
				if(val){
					func_setting += val;
					if(func_setting < 0){ func_setting = 6;}
					func_setting = func_setting % (7);
					WeekDay = func_setting;
				}
				if (press && func_setting_active) {
					func_setting_active = false;
					func_setting = 0;
					break;
				}
				func_setting_active = true;
			}
			
			// plot
			PCD8544_PutTitle("set time");
			PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW1+25, Y_ROW1);
			show_2digit_number(gHOUR , PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMINUTE, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2); 
			show_2digit_number(gDAY, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMONTH, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_4digit_number(gYEAR, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW3+25, Y_ROW3); 
			PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
			break;
		}
		
		case 6: {
			// plot
			PCD8544_PutTitle("set time");
			PCD8544_PutSub("Time:", PCD8544_Row1, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Date:", PCD8544_Row2, PCD8544_Pixel_Clear);
			PCD8544_PutSub("Day:", PCD8544_Row3, PCD8544_Pixel_Clear);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			PCD8544_GotoXY(X_ROW1+25, Y_ROW1);
			show_2digit_number(gHOUR , PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMINUTE, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW2+25, Y_ROW2); 
			show_2digit_number(gDAY, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_2digit_number(gMONTH, PCD8544_Pixel_Clear);
			PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
			show_4digit_number(gYEAR, PCD8544_Pixel_Clear);
			PCD8544_GotoXY(X_ROW3+25, Y_ROW3); 
			PCD8544_PutString(WeekDay_s[WeekDay], PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
			PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
			
			if (press && rotenc_press_old){
				p_func = menu_func;
				PCD8544_Clear();
				func_setting_active = 0;
				rotenc_press_old = 0;
				rotenc_press = 0;
				(*p_func)(0,0);
				return;
			}
			break;
		}
	}
	rotenc_press_old = 1;
	
}

void pump_day_func(int8_t val, bool press){
	
	int8_t i;
	if (val){
		func_item += val ;	// val contains the number of pos changes of rot enc. The currently selected item (func_item) is updated by this value
		if (func_item < 0) {
			func_item = 7;
		}
		func_item = func_item % 8;
	}
	char pump_day = ((PUMP_DATA*)p_data)->pump_day.Reg;
	
	// plot
	PCD8544_PutTitle("pump day"); 
	PCD8544_GotoXY(0, Y_ROW1);
	for(i = 0 ; i < 8; i++){
		PCD8544_GotoXY(i*12, Y_ROW1);
		if(pump_day & (1 << i)){
			PCD8544_PutString("\x02 ", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
			} else {
			PCD8544_PutString("\x01 ", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
		}
	}
	PCD8544_GotoXY(0, Y_ROW2);
	PCD8544_PutString("M T W T F S S", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Clear);
	
	if(func_item != 7){
		PCD8544_PutSub("", PCD8544_Row3, PCD8544_Pixel_Clear);
		PCD8544_GotoXY(func_item*2*PCD8544_CHAR5x7_WIDTH, Y_ROW3);
		PCD8544_PutString("\x7D", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
		
		if(press && rotenc_press_old){
			pump_day ^= 1 << func_item;
			((PUMP_DATA*)p_data)->pump_day.Reg = pump_day;
			PCD8544_GotoXY(0, Y_ROW1);
			for(i = 0 ; i < 7; i++){
				PCD8544_GotoXY(i*12, Y_ROW1);
				if(pump_day & (1 << i)){
					PCD8544_PutString("\x02 ", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
				} else {
					PCD8544_PutString("\x01 ", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
				}	
			}
			PCD8544_GotoXY(0, Y_ROW2);
			PCD8544_PutString("M T W T F S S", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
		}
	} else {
		PCD8544_PutSub("", PCD8544_Row3, PCD8544_Pixel_Clear);
		PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
		if(press && rotenc_press_old){
			p_func = menu_func;
			PCD8544_Clear();
			(*p_func)(0,0);
			rotenc_press_old = 0;
			func_item = 0;
			return;	
		}
	}

rotenc_press_old = 1;
}

void pump_vol_func(int8_t val, bool press){
	
	uint16_t pump_vol = ((PUMP_DATA*)p_data)->pump_vol;
	
	if (val){
		pump_vol += val*10 ;	// val contains the number of pos changes of rot enc. The currently selected item (func_item) is updated by this value
	    if(pump_vol > 1000){
			pump_vol = 1000;
		} 
		if(pump_vol < 0){
			pump_vol = 0;	
		}
	}

	// plot
	PCD8544_PutTitle("pump vol"); 
	PCD8544_PutSub("Vol in ml: ", PCD8544_Row2, PCD8544_Pixel_Clear);
	show_4digit_number(pump_vol, PCD8544_Pixel_Clear);
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	
	((PUMP_DATA*)p_data)->pump_vol = pump_vol; 
	
	if(press && rotenc_press_old){
			p_func = menu_func;
			PCD8544_Clear();
			(*p_func)(0,0);
			rotenc_press_old = 0;
			func_item = 0;
			return;	
		}
	
	rotenc_press_old = 1;
}		

void pump_cal_func(int8_t val, bool press){
	
	uint16_t pump_cal = ((PUMP_DATA*)p_data)->pump_calib;
	
	if (val){
		pump_cal += val*10 ;	// val contains the number of pos changes of rot enc. The currently selected item (func_item) is updated by this value
	    if(pump_cal > 9999){
			pump_cal = 9999;
		} 
		if(pump_cal < 0){
			pump_cal = 0;	
		}
	}

	// plot
	PCD8544_PutTitle("pump cal"); 
	PCD8544_PutSub("ml\x2Fmin: ", PCD8544_Row2, PCD8544_Pixel_Clear);
	show_4digit_number(pump_cal, PCD8544_Pixel_Clear);
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	
	((PUMP_DATA*)p_data)->pump_calib = pump_cal; 
	
	if(press && rotenc_press_old){
			p_func = menu_func;
			PCD8544_Clear();
			(*p_func)(0,0);
			rotenc_press_old = 0;
			func_item = 0;
			return;	
		}
	
	rotenc_press_old = 1;
	
	
}

void pump_arm_func(int8_t val, bool press){
	
	bool pump_arm = ((PUMP_DATA*)p_data)->pump_arm;
	
	if (val){
		pump_arm = !pump_arm; 
		((PUMP_DATA*)p_data)->pump_arm = pump_arm;
	}

	// plot
	PCD8544_PutTitle("pump arm"); 
	PCD8544_PutSub("status: ", PCD8544_Row2, PCD8544_Pixel_Clear);
	
	if(pump_arm){
		PCD8544_PutString("on", PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
	} else {
		PCD8544_PutString("off", PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
	}
	
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	
	if(press && rotenc_press_old){
			p_func = menu_func;
			PCD8544_Clear();
			(*p_func)(0,0);
			rotenc_press_old = 0;
			func_item = 0;
			return;	
		}
		
	rotenc_press_old = 1;	
}

void moist_level_func(int8_t val, bool press){
	
	uint8_t sensor_nr;
	uint8_t moisture;
	float temp;
	sensor_nr = ((MOIST_SENSOR_DATA*)p_data)->moist_sensor_nr;
	moisture = moist_sensor_read(sensor_nr);
	
	// plot
	PCD8544_PutTitle("moist level");
	PCD8544_PutSub("level in %: ", PCD8544_Row2, PCD8544_Pixel_Clear);
	show_4digit_number(moisture, PCD8544_Pixel_Clear);
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	
	
	if(press && rotenc_press_old){
		p_func = menu_func;
		PCD8544_Clear();
		(*p_func)(0,0);
		rotenc_press_old = 0;
		func_item = 0;
		return;
	}
	
	rotenc_press_old = 1;
	
	
}

void moist_eeprom_func(int8_t val, bool press){
	
	PCD8544_SetArea(13, 33, 5, 75, PCD8544_Pixel_Clear);
	PCD8544_Refresh();
	uint8_t sensor_nr;
	uint16_t offset = 0;
	uint8_t data;
	int16_t idx;
	uint8_t i;
	uint16_t j;
	sensor_nr = ((MOIST_SENSOR_DATA*)p_data)->moist_sensor_nr;
	idx= eeprom_read_byte(&eeprom_idx);
	
	
	if(idx > 70){offset = idx - 69;}
	
	for(i= 0; i < 70; i++){
		j = i + offset;
		data = eeprom_read_byte(&(eeprom_moisture_array[sensor_nr-1][j]));
		data =  (int) data * MOIST_FACTOR_PLOT;
		PCD8544_DrawLine(5+i+1, 33-data, 5+i+1, 33, PCD8544_Pixel_Set);
		
	}
	
	
	// plot
	PCD8544_PutTitle("moist ee");
	
	//Draw coordinate system
	PCD8544_DrawLine(5, 33, 75, 33, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5, 13, 5, 33, PCD8544_Pixel_Set);
	
	//Draw y label
	PCD8544_DrawLine(3, 13, 5, 13, PCD8544_Pixel_Set);
	PCD8544_DrawLine(4, 13+5, 5, 13+5, PCD8544_Pixel_Set);
	PCD8544_DrawLine(3, 13+10, 5, 13+10, PCD8544_Pixel_Set);
	PCD8544_DrawLine(4, 13+15, 5, 13+15, PCD8544_Pixel_Set);
	PCD8544_DrawLine(3, 13+20, 5, 13+20, PCD8544_Pixel_Set);
	
	//Draw x label
	PCD8544_DrawLine(5, 33, 5, 33, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+7, 33, 5+7, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+14, 33, 5+14, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+21, 33, 5+21, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+28, 33, 5+28, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+35, 33, 5+35, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+42, 33, 5+42, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+49, 33, 5+49, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+56, 33, 5+56, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+63, 33, 5+63, 35, PCD8544_Pixel_Set);
	PCD8544_DrawLine(5+70, 33, 5+70, 35, PCD8544_Pixel_Set);
	
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	
	
	if(press && rotenc_press_old){
		p_func = menu_func;
		PCD8544_Clear();
		(*p_func)(0,0);
		rotenc_press_old = 0;
		func_item = 0;
		return;
	}
	rotenc_press_old = 1;
}

void moist_vol_func(int8_t val, bool press){
	
	uint16_t pump_vol = ((MOIST_SENSOR_DATA*)p_data)->pump_vol;
	
	if (val){
		pump_vol += val*10 ;	// val contains the number of pos changes of rot enc. The currently selected item (func_item) is updated by this value
		if(pump_vol > 1000){
			pump_vol = 1000;
		}
		if(pump_vol < 0){
			pump_vol = 0;
		}
	}

	// plot
	PCD8544_PutTitle("pump vol");
	PCD8544_PutSub("Vol in ml: ", PCD8544_Row2, PCD8544_Pixel_Clear);
	show_4digit_number(pump_vol, PCD8544_Pixel_Clear);
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	((MOIST_SENSOR_DATA*)p_data)->pump_vol = pump_vol;
	
	if(press && rotenc_press_old){
		p_func = menu_func;
		PCD8544_Clear();
		(*p_func)(0,0);
		rotenc_press_old = 0;
		func_item = 0;
		return;
	}	
	rotenc_press_old = 1;
}

void moist_arm_func(int8_t val, bool press){
	
	bool pump_arm = ((MOIST_SENSOR_DATA*)p_data)->moist_sensor_arm;
	
	if (val){
		pump_arm = !pump_arm;
		((MOIST_SENSOR_DATA*)p_data)->moist_sensor_arm = pump_arm;
	}

	// plot
	PCD8544_PutTitle("moist arm");
	PCD8544_PutSub("status: ", PCD8544_Row2, PCD8544_Pixel_Clear);
	
	if(pump_arm){
		PCD8544_PutString("on", PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
		} else {
		PCD8544_PutString("off", PCD8544_Pixel_Clear, PCD8544_FontSize_3x5);
	}
	
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	
	if(press && rotenc_press_old){
		p_func = menu_func;
		PCD8544_Clear();
		(*p_func)(0,0);
		rotenc_press_old = 0;
		func_item = 0;
		return;
	}
	
	rotenc_press_old = 1;
}

void moist_thres_func(int8_t val, bool press){
	
	uint16_t moist_thres = ((MOIST_SENSOR_DATA*)p_data)->moist_sensor_thres;
	
	if (val){
		moist_thres += val ;	// val contains the number of pos changes of rot enc. The currently selected item (func_item) is updated by this value
		if(moist_thres > 100){
			moist_thres = 100;
		}
		if(moist_thres < 0){
			moist_thres = 0;
		}
	}

	// plot
	PCD8544_PutTitle("pump vol");
	PCD8544_PutSub("thres in %: ", PCD8544_Row2, PCD8544_Pixel_Clear);
	show_4digit_number(moist_thres, PCD8544_Pixel_Clear);
	PCD8544_PutSub("\x3C\x2D" "back", PCD8544_Row4, PCD8544_Pixel_Set);
	((MOIST_SENSOR_DATA*)p_data)->moist_sensor_thres = moist_thres;
	
	if(press && rotenc_press_old){
		p_func = menu_func;
		PCD8544_Clear();
		(*p_func)(0,0);
		rotenc_press_old = 0;
		func_item = 0;
		return;
	}
	rotenc_press_old = 1;
}