/*
 * Time.c
 *
 * Created: 26.09.2020 19:55:32
 *  Author: hacksl
 */ 

#include "Time.h"

// Variable Definition
volatile uint16_t gMSECOND;
char gSECOND;
char gMINUTE;
char gHOUR;
char gDAY;
char gMONTH;
bool gSEC_CHANGE;
uint16_t gYEAR;
char gPowerSaveTimer = 0;
WeekDay_t WeekDay;

// Lookup table holding the length of each mont. The first element is a dummy.
char MonthLength[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char WeekDay_s[7][4] = {"mon","tue","wed","thu","fri","sat","sun"};
uint8_t poll = 0;

// Funtion Definition
void init_time(void){
	
	TCCR1B |= (1 << CS10) | (1 << WGM12);	//Set the prescaler to 1 and set to CTC mode
	OCR1A = F_CPU/1000 -1;					//set compare match to 1ms
	TIMSK1 = 1 << OCIE1A;					//set interrupt by CTC
	
	 // initial time and date setting
	 gMSECOND = 0;	
	 gSECOND  = 0;
	 gMINUTE  = 0;
	 gHOUR    = 12;
	 gDAY     = 01;
	 gMONTH   = 02;
	 gYEAR    = 2021;
	 WeekDay  = monday;
}

ISR(TIMER1_COMPA_vect){
	
	static char LeapMonth;
	gMSECOND++;
	
	if(poll == 3){
		rotenc_poll();
		poll = 0;
	}
	poll++;
	if(gMSECOND == 1000)
	{
		gSECOND++;
		gMSECOND = 0;
		gSEC_CHANGE = 1;
		if(gPowerSaveTimer <= LCD_TIMEOUT_SEC){
			gPowerSaveTimer++;
		}
		if (gSECOND == 60)
		{
			gSECOND = 0;
			gMINUTE++;
		
			if (gMINUTE > 59)
			{
				gMINUTE = 0;
				gHOUR++;
			
				if (gHOUR > 23)
				{
				
					gHOUR = 0;
					gDAY++;
					WeekDay++;
					
					if(WeekDay > sunday){
						WeekDay = monday;
					}

					// Check for leap year if month == February
					if (gMONTH == 2)
						if (!(gYEAR & 0x0003))              // if (gYEAR%4 == 0)
							if (gYEAR%100 == 0)
								if (gYEAR%400 == 0)
									LeapMonth = 1;
								else
									LeapMonth = 0;
							else
								LeapMonth = 1;
						else
							LeapMonth = 0;
					else
						LeapMonth = 0;

					// Now, we can check for month length
					if (gDAY > (MonthLength[gMONTH] + LeapMonth))
					{
						gDAY = 1;
						gMONTH++;

						if (gMONTH > 12)
						{
							gMONTH = 1;
							gYEAR++;
						}
					}
				}
			}
		}
	}
	
}

	
void show_time()
{
	
	show_2digit_number(gHOUR, PCD8544_Pixel_Clear);
	PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
	show_2digit_number(gMINUTE, PCD8544_Pixel_Clear);
	PCD8544_Putc(':', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
	show_2digit_number(gSECOND, PCD8544_Pixel_Clear);
	
}

void show_2digit_number(char number, PCD8544_Pixel_t color )
{
	
	char HH, HL;
	HH = CHAR2BCD2(number);
	HL = (HH & 0x0F) + '0';
	HH = (HH >> 4) + '0';
	
	PCD8544_SetArea(PCD8544_y-2, PCD8544_y+PCD8544_CHAR3x5_HEIGHT, PCD8544_x, PCD8544_x + PCD8544_CHAR3x5_WIDTH*2, color);
	PCD8544_GotoXY(PCD8544_x+1, PCD8544_y);

	PCD8544_Putc(HH, !color, PCD8544_FontSize_3x5);
	PCD8544_Putc(HL, !color, PCD8544_FontSize_3x5);
	
	
}

void show_4digit_number(uint16_t number, PCD8544_Pixel_t color )
{
	uint16_t numBCD;
	char H1, H2, H3, H4;	//4 nibbles = 4 digits
	numBCD = INT2BCD4(number);
	H4 = (numBCD & 0x0F) + '0';
	H3 = ((numBCD >> 4)  & 0x0F) + '0';
	H2  = ((numBCD >> 8)  & 0x0F) + '0';
	H1  = ((numBCD >> 12) & 0x0F) + '0';
	
	PCD8544_SetArea(PCD8544_y-2, PCD8544_y+PCD8544_CHAR3x5_HEIGHT, PCD8544_x, PCD8544_x + PCD8544_CHAR3x5_WIDTH*4, color);
	PCD8544_GotoXY(PCD8544_x+1, PCD8544_y);

	PCD8544_Putc(H1, !color, PCD8544_FontSize_3x5);
	PCD8544_Putc(H2, !color, PCD8544_FontSize_3x5);
	PCD8544_Putc(H3, !color, PCD8544_FontSize_3x5);
	PCD8544_Putc(H4, !color, PCD8544_FontSize_3x5);
}
	
void show_date()
{
	show_2digit_number(gDAY, PCD8544_Pixel_Clear);
	PCD8544_Putc('.', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
	show_2digit_number(gMONTH, PCD8544_Pixel_Clear);
	PCD8544_Putc('.', PCD8544_Pixel_Set, PCD8544_FontSize_3x5);
	show_4digit_number(gYEAR, PCD8544_Pixel_Clear);
}