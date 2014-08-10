/* 
 * File:   defines.h
 * Author: imcinerney
 *
 * Created on August 24, 2012, 11:33 AM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#include <p18f27j13.h>

// Decide whether to print the watermark debug statements
//#define PRINT_DEBUGS

// Defines to provide oscillator frequency
#define FOSC 8000000
#define _XTAL_FREQ 8000000

// Defines to create a boolean type
typedef enum { FALSE=0 , TRUE } boolean;

#endif	/* DEFINES_H */

