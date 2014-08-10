/* 
 * File:   Lib-I2C.h
 * Author: imcinerney
 *
 * Created on September 2, 2012, 12:52 AM
 */

#ifndef LIB_I2C_H
#define	LIB_I2C_H

typedef enum {
    I2C_NO_ERROR,
    I2C_WRITE_COLLISION,
    I2C_ADDRESS_NACK,
    I2C_DATA_NACK
} I2C_ERROR_CODE;

/**
 * This function initializes the 2nd I2C bus of a PIC18F series processor.
 */
void i2c_init();

/**
 * This function performs a write operation on the 2nd I2C bus of a PIC18F series
 * processor. The address must be passed in as a seperate byte than the data. It
 * will return the following error codes:
 *  0 - No error
 *  1 - Write collision occured
 *  2 - NACK received sending the address
 *  3 - NACK received sending the data
 *
 * @param addr  The address to send the data to (must include the write flag when passed)
 * @param transmit_data A character array containing the bytes to transmit
 * @param transmit_length   The number of bytes to be transmitted (length of the array)
 * @return  Error code
 */
int i2c_write(char addr, char *transmit_data, int transmit_length);

/**
 * This function performs a read operation on the 2nd I2C bus of a PIC18F series
 * processor. The address must be passed in as a seperate byte than the data. It
 * will return the following error codes:
 *  0 - No error
 *  1 - Write collision occured
 *  2 - NACK received sending the address
 *
 * @param addr  The address to receive the data from (must include the read flag when passed)
 * @param received_data A character array to place the received data in
 * @param received_length   The number of bytes to receive from the slave
 * @return  Error code
 */
int i2c_read(char addr, char *received_data, int received_length);


/**
 * Parse an I2C error code which was returned by this library
 *
 * @param erroCode The error code which was returned by a library function
 */
void i2c_parse_error(I2C_ERROR_CODE erroCode);
#endif	/* LIB_I2C_H */

