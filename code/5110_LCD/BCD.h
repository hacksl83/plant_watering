//***************************************************************************
//
//  File........: BCD.h
//
//  Author(s)...: ATMEL Norway
//
//  Target(s)...: ATmega169
//
//  Compiler....: IAR EWAAVR 2.28a
//
//  Description.: AVR Butterfly main module
//
//  Revisions...: 1.0
//
//  YYYYMMDD - VER. - COMMENT                                       - SIGN.
//
//  20030116 - 1.0  - Created                                       - KS
//
//***************************************************************************

#ifndef BCD_H_
#define BCD_H_

#include <stdint.h>

// Function declarations
char CHAR2BCD2(char input);
unsigned int CHAR2BCD3(char input);
uint16_t INT2BCD4(uint16_t input);

#endif /* BCD_H_ */
