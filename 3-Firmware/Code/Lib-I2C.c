#include "Lib-I2C.h"
#include <p18f27j13.h>

/**
 * This function initializes the 2nd I2C bus of a PIC18F series processor.
 */
void i2c_init() {
    // Set the MSSP status to be I2C Master with the BRG in SSP2ADD
    SSP2CON1bits.SSPM0 = 0;
    SSP2CON1bits.SSPM1 = 0;
    SSP2CON1bits.SSPM2 = 0;
    SSP2CON1bits.SSPM3 = 1;

    // Set the BRG for the MSSP to create a 400kHz clock
    SSP2ADD = 4;
    SSP2STATbits.SMP = 0;

    // Enable the MSSP pins
    SSP2CON1bits.SSPEN = 1;
}

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
int i2c_write(char addr, char *transmit_data, int transmit_length) {
    short i;    // For loop counting variable

    SSP2CON2bits.RCEN = 0; // Set the bus to be Master Transmitter
    SSP2CON2bits.SEN = 1; // Send a start condition
    while (SSP2CON2bits.SEN == 1); // Wait for the start condition to be sent

    /*
     * Transmit the address of the slave device
     */
    while (SSP2STATbits.R_NOT_W == 1); // Wait for the bus to be idle
    SSP2BUF = addr; // Move the address into the buffer
    if (SSP2CON1bits.WCOL == 1) {
        // Write collision occured
        return (I2C_WRITE_COLLISION);
    }

    while (SSP2STATbits.BF == 1); // Wait for the buffer to be sent
    if (SSP2CON2bits.ACKSTAT != 0) {
        // AN ACK was not received from the slave device, error
        SSP2CON2bits.PEN = 1; // Send a stop condition
        return (I2C_ADDRESS_NACK);
    }

    /*
     * Transmit the data to the slave
     */
    for(i=0; i < transmit_length; i++) {
        // Load the data into the buffer and then send it
        while(SSP2STATbits.R_NOT_W == 1); // Wait for the bus to be idle
        SSP2BUF = transmit_data[i]; // Load the data to send into the register
        if (SSP2CON1bits.WCOL == 1) {
            // Write collision occured
            return (I2C_WRITE_COLLISION);
        }
        while (SSP2STATbits.BF == 1); // Wait for the buffer to be sent
        if (SSP2CON2bits.ACKSTAT != 0) {
            // An ACK was not received from the slave device, error
            SSP2CON2bits.PEN = 1; // Send a stop condition
            return (I2C_DATA_NACK);
        }
    }

    SSP2CON2bits.PEN = 1; // Send a stop condition
    while (SSP2CON2bits.PEN == 1); // Wait for the stop condition to be sent
    return(I2C_NO_ERROR);
}

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
int i2c_read(char addr, char *received_data, int received_length) {
    short i;    // For loop counting variable
    
    SSP2CON2bits.RCEN = 0; // Set the bus to be Master Transmitter
    SSP2CON2bits.SEN = 1; // Send a start condition
    while (SSP2CON2bits.SEN == 1); // Wait for the start condition to be sent

    /*
     * Transmit the address of the slave device
     */
    while(SSP2STATbits.R_NOT_W == 1); // Wait for the bus to be idle
    SSP2BUF = addr; // Move the address into the buffer
    if (SSP2CON1bits.WCOL == 1) {
        // Write collision occured
        return (I2C_WRITE_COLLISION);
    }
    while (SSP2STATbits.BF == 1); // Wait for the buffer to be sent
    if (SSP2CON2bits.ACKSTAT != 0) {
        // AN ACK was not received from the slave device, error
        SSP2CON2bits.PEN = 1; // Send a stop condition
        return (I2C_ADDRESS_NACK);
    }

    /*
     * Receive the data bytes
     */
    for(i=0; i < received_length; i++) {
        SSP2CON2bits.RCEN = 1; // Request the byte of data
        while(SSP2CON2bits.RCEN == 1);   // Wait for the data to be received

        // Determine whether to send an ACK (more data expected) or a NACK (final data byte)
        if (i == received_length - 1) {
            // This is the last data byte, send a NACK once received
            SSP2CON2bits.ACKDT = 1; // Reply with a NACK
            SSP2CON2bits.ACKEN = 1;
            while(SSP2CON2bits.ACKEN == 1); // Wait for the NACK to be sent
        } else {
            // There is more data after this byte, send an ACK
            SSP2CON2bits.ACKDT = 0; // Reply with an ACK
            SSP2CON2bits.ACKEN = 1;
            while(SSP2CON2bits.ACKEN == 1); // Wait for the ACK to be sent
        }

        received_data[i] = SSP2BUF; // Copy the data in the buffer to the received data array
    }

    SSP2CON2bits.PEN = 1; // Send a stop condition
    while (SSP2CON2bits.PEN == 1); // Wait for the stop condition to be sent
    return(I2C_NO_ERROR);
}

void i2c_parse_error(I2C_ERROR_CODE errorCode) {
#ifdef PRINT_DEBUGS
    if (errorCode == I2C_NO_ERROR) {
        // No error has occured
        printf("No I2C Error Occured\n\r");
    } else if (errorCode == I2C_WRITE_COLLISION) {
        // Write collision occured
        printf("I2C Write Collision\n\r");
    } else if (errorCode == I2C_ADDRESS_NACK) {
        // NACK received on sending address
        printf("I2C NACK Received while sending address\n\r");
    } else if (errorCode == I2C_DATA_NACK) {
        // NACK received on sending data
        printf("I2C NACK Received while sending data\n\r");
    } else {
        // Unknown error code
        printf("Unknown I2C Error Code: %d", errorCode);
    }
#endif
}