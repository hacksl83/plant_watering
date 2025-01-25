#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <util/delay.h>


//enum test {command, data} com_dat;

#define	DDR_SPI			DDRB	
#define DD_MOSI			PORTB3
#define DD_SCK			PORTB5
#define DD_SS			PORTB2
#define DD_RST			PORTD7	



/* SPI Initialization */
void spi_MasterInit(void);

/* Start Transmission */
void spi_MasterTransmit(char cData);



#endif