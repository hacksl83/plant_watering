/**
 * PCD8544 LCD controller driver.
 * This controller is used in Nokia's 3310 and 5110 LCD's.
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@link		http://stm32f4-discovery.com/pcd8544-nokia-33105110-lcd-stm32f429-discovery-library/
 *	@version 	v1.0
 *	@ide		Keil uVision
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 *	


 * Includes
 */

#ifndef		PCD8544_H
#define		PCD8544_H
#include "SPI.h"
#include <avr/io.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

unsigned char PCD8544_x;
unsigned char PCD8544_y;
extern unsigned char contrast;

//Default pins used

//Default DC pin
#define PCD8544_DC_DDR			DDRB
#define PCD8544_DC_PORT			PORTB
#define PCD8544_DC_PIN			PORTB0

//Default CE pin
#define PCD8544_CE_DDR			DDRB
#define PCD8544_CE_PORT			PORTB
#define PCD8544_CE_PIN			PORTB2


//Default RST pin
#define PCD8544_RST_DDR			DDRD
#define PCD8544_RST_PORT		PORTD
#define PCD8544_RST_PIN			PORTD7

//Default BL pin
#define PCD8544_BL_DDR			DDRB
#define PCD8544_BL_PORT			PORTB
#define PCD8544_BL_PIN			PORTB1


//Set clear Bit n of PORT p
#define GPIO_SetBits(p, n)		((p) |= (1 << (n)))
#define GPIO_ResetBits(p, n)	((p) &= (~((1) << (n))))	

//Set Bits low or high macros
#define PCD8544_CE_LOW			GPIO_ResetBits(PCD8544_CE_PORT, PCD8544_CE_PIN)
#define PCD8544_CE_HIGH			GPIO_SetBits(PCD8544_CE_PORT, PCD8544_CE_PIN)

#define PCD8544_DC_LOW			GPIO_ResetBits(PCD8544_DC_PORT, PCD8544_DC_PIN)
#define PCD8544_DC_HIGH			GPIO_SetBits(PCD8544_DC_PORT, PCD8544_DC_PIN)

#define PCD8544_RST_LOW			GPIO_ResetBits(PCD8544_RST_PORT, PCD8544_RST_PIN)
#define PCD8544_RST_HIGH		GPIO_SetBits(PCD8544_RST_PORT, PCD8544_RST_PIN)

#define PCD8544_BL_LOW			GPIO_ResetBits(PCD8544_BL_PORT, PCD8544_BL_PIN)
#define PCD8544_BL_HIGH			GPIO_SetBits(PCD8544_BL_PORT, PCD8544_BL_PIN)

/*
 * Private enums
 */

typedef enum {
	PCD8544_COMMAND = 0,
	PCD8544_DATA = !PCD8544_COMMAND
} PCD8544_WriteType_t;

typedef enum {
	PCD8544_State_Low = 0,
	PCD8544_State_High = !PCD8544_State_Low
} PCD8544_State_t;

typedef enum {
	PCD8544_Pin_DC = 1,
	PCD8544_Pin_RST = 2
} PCD8544_Pin_t;

/**
 * Public enums
 */
/**
 * Used for pixel "color"
 * LCD is 2 bit, so pixel can be just set or clear
 */
typedef enum {
	PCD8544_Pixel_Clear = 0,
	PCD8544_Pixel_Set = !PCD8544_Pixel_Clear
} PCD8544_Pixel_t;

/**
 * Font size for text
 * There are 2 sizes included
 */
typedef enum {
	PCD8544_FontSize_5x7 = 0,
	PCD8544_FontSize_3x5 = !PCD8544_FontSize_5x7
} PCD8544_FontSize_t;

/**
 * Used to invert pixels
 */
typedef enum {
	PCD8544_Invert_Yes,
	PCD8544_Invert_No
} PCD8544_Invert_t;

typedef enum {
	PCD8544_Row1 = 1,
	PCD8544_Row2 = 2,
	PCD8544_Row3 = 3,
	PCD8544_Row4 = 4,
} PCD8544_SubMenuRow_t;

#define PCD8544_WIDTH				84
#define PCD8544_HEIGHT				48

// define x,y position of each menu row
#define ROW_HEIGHT					9
#define ROW_LENGTH					50

#define X_ROW0						14 
#define Y_ROW0						0

#define X_LINE						14
#define Y_LINE						Y_ROW0 + ROW_HEIGHT

#define X_ROW1						14
#define Y_ROW1						Y_LINE + 4

#define X_ROW2						X_ROW1
#define Y_ROW2						Y_ROW1 + ROW_HEIGHT

#define X_ROW3						X_ROW1
#define Y_ROW3						Y_ROW2 + ROW_HEIGHT

#define X_ROW4						X_ROW1
#define Y_ROW4						Y_ROW3 + ROW_HEIGHT

// PCD8544 Commandset
// ------------------
// General commands
#define PCD8544_POWERDOWN			0x04
#define PCD8544_ENTRYMODE			0x02
#define PCD8544_EXTENDEDINSTRUCTION	0x01
#define PCD8544_DISPLAYBLANK		0x00
#define PCD8544_DISPLAYNORMAL		0x04
#define PCD8544_DISPLAYALLON		0x01
#define PCD8544_DISPLAYINVERTED		0x05
// Normal instruction set
#define PCD8544_FUNCTIONSET			0x20
#define PCD8544_DISPLAYCONTROL		0x08
#define PCD8544_SETYADDR			0x40
#define PCD8544_SETXADDR			0x80
// Extended instruction set
#define PCD8544_SETTEMP				0x04
#define PCD8544_SETBIAS				0x10
#define PCD8544_SETVOP				0x80
// Display presets
#define PCD8544_LCD_BIAS			0x03	// Range: 0-7 (0x00-0x07)
#define PCD8544_LCD_TEMP			0x02	// Range: 0-3 (0x00-0x03)
#define PCD8544_LCD_CONTRAST		0x38	// Range: 0-127 (0x00-0x7F)

#define PCD8544_CHAR5x7_WIDTH		6 //5*8
#define PCD8544_CHAR5x7_HEIGHT		8
#define PCD8544_CHAR3x5_WIDTH		4 //3*5
#define PCD8544_CHAR3x5_HEIGHT		6


unsigned char PCD8544_UpdateXmin, PCD8544_UpdateXmax, PCD8544_UpdateYmin, PCD8544_UpdateYmax;
/**
 * Initialize all IO pins and peripheral
 *
 */
extern void PCD8544_InitIO(void);

/**
 * Send data to LCD
 *
 */
extern void PCD8544_send(unsigned char data);

/**
 * Specify delay in microseconds
 *
 */
extern void PCD8544_Delay(unsigned long micros);

/**
 * Write data/command to LCD
 *
 */
extern void PCD8544_Write(PCD8544_WriteType_t cd, unsigned char data); 

/**
 * Set area for refresh display
 *
 */
extern void PCD8544_UpdateArea(unsigned char xMin, unsigned char yMin, unsigned char xMax, unsigned char yMax);

/**
 * Initialize LCD
 *
 * Parameters
 * - unsigned char contrast: Contrast can be software selectable, from 0x00 to 0x7F
 */
extern void PCD8544_Init(unsigned char contrast);

/**
 * Set contrast for LCD
 *
 * Parameters
 * - unsigned char contrast: Contrast can be software selectable, from 0x00 to 0x7F
 */
extern void PCD8544_SetContrast(unsigned char contrast);

/**
 * Invert LCD
 *
 * Parameters
 * - PCD8544_Invert_t invert
 * 		- PCD8544_Invert_Yes: Invert pixels on lcd
 * 		- PCD8544_Invert_No: Return pixels to orignal
 */
extern void PCD8544_Invert(PCD8544_Invert_t invert);

/**
 * Clear lcd
 */
extern void PCD8544_Clear(void);

/**
 * Set/clear pixel at specific location
 *
 * Parameters
 * - unsigned char x: x position of pixel
 * - unsigned char y: y position of pixel
 * - PCD8544_PCD8544_Pixel_t pixel: Set or clear pixel
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_DrawPixel(unsigned char x, unsigned char y, PCD8544_Pixel_t pixel);

/**
 * Set cursor on lcd at 0, 0 location
 *
 */
extern void PCD8544_Home(void);

/**
 * Put data from internal buffer to lcd
 *
 */
extern void PCD8544_Refresh(void);

/**
 * Set cursor to desired position
 *
 * Parameters:
 * - unsigned char x: x from 0 to 83
 * - unsigned char y: y from 0 to 47
 */
extern void PCD8544_GotoXY(unsigned char x, unsigned char y);

/**
 * Put character on LCD
 *
 * Parameters:
 * - char c: char to display
 * - PCD8544_FontSize_t size: Font size
 * 		- PCD8544_FontSize_5x7
 * 		- PCD8544_FontSize_3x5
 * - PCD8544_PCD8544_Pixel_t color
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_Putc(char c, PCD8544_Pixel_t color, PCD8544_FontSize_t size);

/**
 * Put string on LCD
 *
 * Parameters:
 * - char *c: pointer to first character of string
 * - PCD8544_FontSize_t size: Font size
 * 		- PCD8544_FontSize_5x7
 * 		- PCD8544_FontSize_3x5
 * - PCD8544_PCD8544_Pixel_t color
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_Puts(char *c, PCD8544_Pixel_t color, PCD8544_FontSize_t size);

extern void PCD8544_Puts_f(const __flash char *c, PCD8544_Pixel_t color, PCD8544_FontSize_t size);

/**
 * Draw line on LCD
 *
 * Parameters:
 * - unsigned char x0: X coordinate of starting point
 * - unsigned char y0: Y coordinate of starting point
 * - unsigned char x1: X coordinate of ending point
 * - unsigned char y1: Y coordinate of ending point
 * - PCD8544_PCD8544_Pixel_t color
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, PCD8544_Pixel_t color);

/**
 * Draw rectangle on LCD
 *
 * Parameters:
 * - unsigned char x0: X coordinate of top left point
 * - unsigned char y0: Y coordinate of top left point
 * - unsigned char x1: X coordinate of bottom right point
 * - unsigned char y1: Y coordinate of bottom right point
 * - PCD8544_PCD8544_Pixel_t color
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, PCD8544_Pixel_t color);

/**
 * Draw filled rectangle on LCD
 *
 * Parameters:
 * - unsigned char x0: X coordinate of top left point
 * - unsigned char y0: Y coordinate of top left point
 * - unsigned char x1: X coordinate of bottom right point
 * - unsigned char y1: Y coordinate of bottom right point
 * - PCD8544_PCD8544_Pixel_t color
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_DrawFilledRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, PCD8544_Pixel_t color);

/**
 * Draw circle on LCD
 *
 * Parameters:
 * - char x0: X coordinate of center circle point
 * - char y0: Y coordinate of center circle point
 * - char r: circle radius
 * - PCD8544_PCD8544_Pixel_t color
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_DrawCircle(char x0, char y0, char r, PCD8544_Pixel_t color);

/**
 * Draw filled circle on LCD
 *
 * Parameters:
 * - char x0: X coordinate of center circle point
 * - char y0: Y coordinate of center circle point
 * - char r: circle radius
 * - PCD8544_PCD8544_Pixel_t color
 * 		- PCD8544_Pixel_Set
 * 		- PCD8544_Pixel_Clear
 */
extern void PCD8544_DrawFilledCircle(char x0, char y0, char r, PCD8544_Pixel_t color);

void PCD8544_ClearRow(unsigned char y);
void PCD8544_SetArea(unsigned char yMin, unsigned char yMax, unsigned char xMin, unsigned char xMax, bool color);

extern void PCD8544_PutTitle_f(const __flash char *c);
extern void PCD8544_PutTitle(char *c);
extern void PCD8544_PutString_f(const __flash char *c, PCD8544_Pixel_t color, PCD8544_FontSize_t size);
extern void PCD8544_PutString(char *c, PCD8544_Pixel_t color, PCD8544_FontSize_t size);
extern void PCD8544_PutSub_f(const __flash char *c, PCD8544_SubMenuRow_t row, PCD8544_Pixel_t color);
extern void PCD8544_PutSub(char *c, PCD8544_SubMenuRow_t row, PCD8544_Pixel_t color);

/*
* If there is no activity for LCD_TIMEOUT_SEC seconds then the LCD backlight is turned off to save power
*/
void PCD8544_Powersave();

#endif


