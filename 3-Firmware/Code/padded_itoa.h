/* 
 * File:   padded_itoa.h
 * Author: imcinerney
 *
 * Created on November 4, 2012, 9:38 PM
 */

#ifndef PADDED_ITOA_H
#define	PADDED_ITOA_H

/**
 *
 * Function to create a padded 4 character number with a +- sign in front
 *
 * @param dest Destination string, always 5 characters including +-
 * @param integer Integer to convert
 */
void padded_itoa(char* dest, short integer);

#endif

