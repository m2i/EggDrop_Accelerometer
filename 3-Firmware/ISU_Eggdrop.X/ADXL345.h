/* 
 * File:   ADXL345.h
 * Author: imcinerney
 *
 * Created on August 20, 2012, 10:58 PM
 */

#ifndef ADXL345_H
#define	ADXL345_H

#include <GenericTypeDefs.h>

// Data structure to hold one data reading
typedef struct{
    signed short x;
    signed short y;
    signed short z;
} ADXL345_AXIS_DATA;

/*
 * Port information for the interrupts & alternate address pin
 */
#define ADXL345_INT1_PORT   PORTBbits.RB2
#define ADXL345_INT1_TRIS   TRISBbits.TRISB2
#define ADXL345_INT1_LAT    LATBbits.LATB2

#define ADXL345_INT2_PORT   PORTBbits.RB1
#define ADXL345_INT2_TRIS   TRISBbits.TRISB1
#define ADXL345_INT2_LAT    LATBbits.LATB1

#define ADXL345_ALT_PORT    PORTBbits.RB0
#define ADXL345_ALT_TRIS    TRISBbits.TRISB0
#define ADXL345_ALT_LAT     LATBbits.LATB0

#define ADXL345_CS_PORT     PORTBbits.RB3
#define ADXL345_CS_TRIS     TRISBbits.TRISB3
#define ADXL345_CS_LAT      LATBbits.LATB3


/*
 * I2C Addresses for the ADXL345 when ALT_ADDRESS is low (base address 0x53)
 */
#define ADXL345_ADDR_READ    0xA7
#define ADXL345_ADDR_WRITE   0xA6

/*
 * Register locations on the ADXL345
 */
#define ADXL345_REG_DEVID          0x00
#define ADXL345_REG_THRESH_TAP     0x1D
#define ADXL345_REG_OFSX           0x1E
#define ADXL345_REG_OFSY           0x1F
#define ADXL345_REG_OFSZ           0x20
#define ADXL345_REG_DUR            0x21
#define ADXL345_REG_LATENT         0x22
#define ADXL345_REG_WINDOW         0x23
#define ADXL345_REG_THRESH_ACT     0x24
#define ADXL345_REG_THRESH_INACT   0x25
#define ADXL345_REG_TIME_INACT     0x26
#define ADXL345_REG_ACT_INACT_CTL  0x27
#define ADXL345_REG_THRESH_FF      0x28
#define ADXL345_REG_TIME_FF        0x29
#define ADXL345_REG_TAP_AXES       0x2A
#define ADXL345_REG_ACT_TAP_STATUS 0x2B
#define ADXL345_REG_BW_RATE        0x2C
#define ADXL345_REG_POWER_CTL      0x2D
#define ADXL345_REG_INT_ENABLE     0x2E
#define ADXL345_REG_INT_MAP        0x2F
#define ADXL345_REG_INT_SOURCE     0x30
#define ADXL345_REG_DATA_FORMAT    0x31
#define ADXL345_REG_DATAX0         0x32
#define ADXL345_REG_DATAX1         0x33
#define ADXL345_REG_DATAY0         0x34
#define ADXL345_REG_DATAY1         0x35
#define ADXL345_REG_DATAZ0         0x36
#define ADXL345_REG_DATAZ1         0x37
#define ADXL345_REG_FIFO_CTL       0x38
#define ADXL345_REG_FIFO_STATUS    0x39

/*
 * Configuration bits for the accelerometer
 */
#define ADXL345_CONFIG_LOW_POWER    0x10
#define ADXL345_CONFIG_LINK         0x20
#define ADXL345_CONFIG_AUTO_SLEEP   0x10
#define ADXL345_CONFIG_MEASURE      0x08
#define ADXL345_CONFIG_STANDBY      0x00
#define ADXL345_CONFIG_SLEEP        0x04

/*
 * Data collection rate values for the ADXL345
 * Rates above 400Hz are not available in low power mode
 */
#define ADXL345_RATE_3200HZ      0x0F
#define ADXL345_RATE_1600HZ      0x0E
#define ADXL345_RATE_800HZ       0x0D
#define ADXL345_RATE_400HZ       0x0C
#define ADXL345_RATE_200HZ       0x0B
#define ADXL345_RATE_100HZ       0x0A
#define ADXL345_RATE_50HZ        0x09
#define ADXL345_RATE_25HZ        0x08
#define ADXL345_RATE_12HZ5       0x07
#define ADXL345_RATE_6HZ25       0x06

/*
 * Data collection rate values for when the ADXL345 is in sleep mode
 */
#define ADXL345_SLEEP_RATE_8HZ  0x00
#define ADXL345_SLEEP_RATE_4HZ  0x01
#define ADXL345_SLEEP_RATE_2HZ  0x10
#define ADXL345_SLEEP_RATE_1HZ  0x11

/*
 * Interrupt generation and location register values
 * Use these to either
 *  1) Enable the interrupt
 *  2) Place the interrupt on the INT2 pin
 *  3) As a bit mask for reading the INT_SOURCE register
 *      (AND with the register value to determine if the interrupt occured)
 */
#define ADXL345_INT_DATA_READY  0x80
#define ADXL345_INT_SINGLE_TAP  0x40
#define ADXL345_INT_DOUBLE_TAP  0x20
#define ADXL345_INT_ACTIVITY    0x10
#define ADXL345_INT_INACTIVITY  0x08
#define ADXL345_INT_FREE_FALL   0x04
#define ADXL345_INT_WATERMARK   0x02
#define ADXL345_INT_OVERRUN     0x01

/*
 * Configuration options placed in the format register
 */
#define ADXL345_FORMAT_SELFTEST_EN  0x80
#define ADXL345_FORMAT_3WIRE_SPI    0x40
#define ADXL345_FORMAT_4WIRE_SPI    0x00
#define ADXL345_FORMAT_INT_LOW      0x20
#define ADXL345_FORMAT_INT_HIGH     0x00
#define ADXL345_FORMAT_FULL_RES     0x08
#define ADXL345_FORMAT_MSB_LEFT     0x04
#define ADXL345_FORMAT_LSB_LEFT     0x00

/*
 * Control the range of the accelerometer when FULL_RES is not used
 */
#define ADXL345_RANGE_2G    0x00
#define ADXL345_RANGE_4G    0x01
#define ADXL345_RANGE_8G    0x02
#define ADXL345_RANGE_16G   0x03

/*
 * Set the FIFO mode
 */
#define ADXL345_FIFO_MODE_BYPASS    0x00
#define ADXL345_FIFO_MODE_FIFO      0x40
#define ADXL345_FIFO_MODE_STREAM    0x80
#define ADXL345_FIFO_MODE_TRIGGER   0xC0

/*
 * Determine which interrupt pin the FIFO trigger event uses
 */
#define ADXL345_FIFO_TRIGGER_INT1   0x00
#define ADXL345_FIFO_TRIGGER_INT2   0x20

/*
 * Set the number of samples the FIFO will collect before interrupting
 */
#define ADXL345_FIFO_SAMPLES_1      0x01
#define ADXL345_FIFO_SAMPLES_2      0x02
#define ADXL345_FIFO_SAMPLES_3      0x03
#define ADXL345_FIFO_SAMPLES_4      0x04
#define ADXL345_FIFO_SAMPLES_5      0x05
#define ADXL345_FIFO_SAMPLES_6      0x06
#define ADXL345_FIFO_SAMPLES_7      0x07
#define ADXL345_FIFO_SAMPLES_8      0x08
#define ADXL345_FIFO_SAMPLES_9      0x09
#define ADXL345_FIFO_SAMPLES_10     0x0A
#define ADXL345_FIFO_SAMPLES_11     0x0B
#define ADXL345_FIFO_SAMPLES_12     0x0C
#define ADXL345_FIFO_SAMPLES_13     0x0D
#define ADXL345_FIFO_SAMPLES_14     0x0E
#define ADXL345_FIFO_SAMPLES_15     0x0F
#define ADXL345_FIFO_SAMPLES_16     0x10
#define ADXL345_FIFO_SAMPLES_17     0x11
#define ADXL345_FIFO_SAMPLES_18     0x12
#define ADXL345_FIFO_SAMPLES_19     0x13
#define ADXL345_FIFO_SAMPLES_20     0x14
#define ADXL345_FIFO_SAMPLES_21     0x15
#define ADXL345_FIFO_SAMPLES_22     0x16
#define ADXL345_FIFO_SAMPLES_23     0x17
#define ADXL345_FIFO_SAMPLES_24     0x18
#define ADXL345_FIFO_SAMPLES_25     0x19
#define ADXL345_FIFO_SAMPLES_26     0x1A
#define ADXL345_FIFO_SAMPLES_27     0x1B
#define ADXL345_FIFO_SAMPLES_28     0x1C
#define ADXL345_FIFO_SAMPLES_29     0x1D
#define ADXL345_FIFO_SAMPLES_30     0x1E
#define ADXL345_FIFO_SAMPLES_31     0x1F

/*
 * Mask used to read the number of entries in the FIFO
 * (AND with the FIFO_STATUS register)
 */
#define ADXL345_FIFO_ENTRIES_MASK   0x1F


/**
 * This function will initialize the three digital inputs/outputs required for
 * the full functionality of the ADXL345. It will initialize the following:
 * INT1
 * INT2
 * ALT_ADDRESS
 *
 * Make sure to set these pins in the defines at the top of the ADXL345.h file.
 */
void adxl345_initialize_pins();

/**
 * This function sets a configuration register on the ADXL345 accelerometer
 *
 * @param reg The register to set
 * @param value The value to put in the register
 * @return Returns 0 if successful, otherwise returns an I2C error code
 */
UINT8 adxl345_set_register(UINT8 reg, UINT8 value);

/**
 * This function retrieves data for the X, Y, and Z axis from the ADXL345 accelerometer
 *
 * @param data A pointer to the data structure containing the X, Y, and Z data
 * @return Returns 0 if successful, otherwise returns an I2C error code
 */
UINT8 adxl345_data_read(ADXL345_AXIS_DATA *data);

#endif	/* ADXL345_H */
