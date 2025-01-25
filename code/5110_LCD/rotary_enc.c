/*
 * rotary_enc.c
 *
 * Created: 27.09.2020 12:14:19
 *  Author: hacksl
 */ 

#include "rotary_enc.h"

#define ROTENC_PINA		PIND5
#define ROTENC_PINB		PIND6
#define ROTENC_PUSH		PIND2
#define ROTENC_PIN		PIND
#define ROTENC_DDR		DDRD
#define ROTENC_PORT		PORTD         // LEDs against VCC
		
#define PHASE_A     (ROTENC_PIN & 1<<ROTENC_PINA)
#define PHASE_B     (ROTENC_PIN & 1<<ROTENC_PINB)
#define PUSH		(ROTENC_PIN & 1<<ROTENC_PUSH)
volatile int16_t enc_delta;          // -128 ... 127
int16_t last = 0;
int16_t new = 0;
bool rotenc_press = false;
bool rotenc_press_old = false;
uint16_t push_debounce = 0;

ISR(INT0_vect){

	rotenc_press = true;
	
}

void rotenc_init( void )
{
	ROTENC_DDR &= ~(1 << ROTENC_PINA) & ~(1 << ROTENC_PINB) & ~(1 << ROTENC_PUSH);
	ROTENC_PORT &= ~(1 << ROTENC_PUSH);
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	sei();

}


int8_t rotenc_read4( void )         // read four step encoders
{
	int8_t val;

	cli();
	val = enc_delta;
	enc_delta = 0;
	sei();
}


void rotenc_poll(void){       // 1ms for manual movement
	
	if(PHASE_A){new = 1;}else{new = 0;}
	if((new == 0) && last){
		if(PHASE_B){
			enc_delta--;
		}else{
			enc_delta++;	
		}
	}
	last = new;
}