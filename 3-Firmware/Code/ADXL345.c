#include <i2c.h>
#include <stdio.h>
#include <GenericTypeDefs.h>

#include "ADXL345.h"
#include "Lib-I2C.h"

// Variable to hold the error code from the I2C communication
I2C_ERROR_CODE i2c_error;

// Data buffer for the I2C Communication
INT8 ADXL345_data_buffer[13];

/**
 * This function will update the specified register to reflect the given values.
 *
 * @param reg   The register to update
 * @param value The vales to be updated (OR all the values together)
 */
UINT8 adxl345_set_register(UINT8 reg, UINT8 value) {
    ADXL345_data_buffer[0] = reg;
    ADXL345_data_buffer[1] = 0x00;

    /*
     * Create the new register value
     */
    ADXL345_data_buffer[0] = reg;
    ADXL345_data_buffer[1] = value;
    
    /*
     * Transmit the updated register value
     */
    i2c_error = i2c_write(ADXL345_ADDR_WRITE, ADXL345_data_buffer, 2);
    i2c_parse_error(i2c_error);
    return(i2c_error);
}

UINT8 adxl345_data_read(ADXL345_AXIS_DATA *data) {
    data->x = 0;
    data->y = 0;
    data->z = 0;
    
    ADXL345_data_buffer[0] = ADXL345_REG_DATAX0;
    ADXL345_data_buffer[1] = 0x00;
    ADXL345_data_buffer[2] = 0x00;
    ADXL345_data_buffer[3] = 0x00;
    ADXL345_data_buffer[4] = 0x00;
    ADXL345_data_buffer[5] = 0x00;

    i2c_error = i2c_write(ADXL345_ADDR_WRITE, ADXL345_data_buffer, 1);
    if (i2c_error != I2C_NO_ERROR) {
        return(i2c_error);
    } else {
        i2c_parse_error(i2c_error);
    }

    i2c_error = i2c_read(ADXL345_ADDR_READ, ADXL345_data_buffer, 6);

    // Check for error during I2C usage
    if (i2c_error != I2C_NO_ERROR) {
        return(i2c_error);
    } else {
        i2c_parse_error(i2c_error);
    }
    data->x = (ADXL345_data_buffer[1] << 8) | ADXL345_data_buffer[0];
    data->y = (ADXL345_data_buffer[3] << 8) | ADXL345_data_buffer[2];
    data->z = (ADXL345_data_buffer[5] << 8) | ADXL345_data_buffer[4];
    return(0);
}