#include "SPI.h"




void spi_MasterInit(void){
	
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	//DDR_SPI &= ~(1<<DD_MISO);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//SPCR &= ~(1 << DORD) ;
}

void spi_MasterTransmit(char cData)
{
	//PORTB &= ~(1 << DD_SS);
	//switch(com_dat) {
		
	//	case command: PORTB &= ~(1 << DD_DC); break;
	//	case data: PORTB |= (1 << DD_DC); break;
	//}
	
	_delay_us(10);
	/* Start Transmission */
	SPDR = cData;
	/* Wait for transmission complete*/
	while (!(SPSR & (1<<SPIF)))
	;
	_delay_us(10);
	//PORTB |= (1 << DD_SS);
	//PORTB |= (1 << DD_DC);
}

