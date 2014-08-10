#include "padded_itoa.h"

/**
 * Function to create a padded 4 character number with a +- sign in front
 *
 * @param dest Destination string, always 5 characters including +-
 * @param integer Integer to convert
 */
void padded_itoa(char* dest, short integer) {
    // Place the sign in the very front of the array
    if (integer > 0) {
        dest[0] = '+';
    } else {
        dest[0] = '-';
        integer = ((-1)* integer);
    }

    dest[1] = '0';
    dest[2] = '0';
    dest[3] = '0';
    dest[4] = '0';

    if (integer > 999) {
        dest[1] += (integer/1000);
        integer = integer%1000;
    }
    if (integer > 99) {
        dest[2] += (integer/100);
        integer = integer%100;
    }
    if (integer > 9) {
        dest[3] += (integer/10);
        integer = integer%10;
    }
    dest[4] += integer;
    dest[5] = 0;
}