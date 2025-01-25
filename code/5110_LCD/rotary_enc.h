/*
 * rotary_enc.h
 *
 * Created: 27.09.2020 12:54:47
 *  Author: hacksl
 */ 


#ifndef ROTARY_ENC_H_
#define ROTARY_ENC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pcd8544.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

extern int8_t rotenc_updown;
extern bool rotenc_press;
extern bool rotenc_press_old;


void rotenc_poll(void);
void rotenc_init(void);
int8_t rotenc_read4( void ) ;





#endif /* ROTARY_ENC_H_ */