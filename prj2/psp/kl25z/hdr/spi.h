#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include <stdlib.h>
#include "MKL25Z4.h"

/*
 *
One final note is that you will need to be careful on your SPI configuration.
	1. The SPI clock frequencies you select needs to be no larger than 8MHz.
	2. The KL25z SPI will need to be set into Master mode and the NRF will act
		as a slave device.
	3. Your SPI module should be configured for 3-wire mode (+2 gpio wires)
	4. The device should be configured for MSB first.
	5. Clock Should Idle Low and be active on the rising edge.
	6. Your clock Chip selects should wrap around the full length of the
		nordic commands.
	7. The SPI NOP command for this device is 0xFF
 *
 */



typedef enum {
	SPI_OK = 1,
	SPI_ERROR = 2
} SPI_status_t;


/**************
* SPI_init()
*	description:
*		Initializes the SPI controller
*	params:
*
*	returns:
*		SPI_status_t status - returns OK if init was successful, ERROR if unsuccessful
**************/
SPI_status_t SPI_init(void);


/**************
* SPI_read_byte()
*	description:
*		Reads a single byte from the SPI bus
*	params:
*		uint8_t * byte - pointer to returned byte
*	returns:
*		SPI_status_t status - returns OK if read was successful, ERROR if unsuccessful
**************/
SPI_status_t SPI_read_byte(uint8_t * byte);

/**************
* SPI_write_byte()
*	description:
*		Sends a single byte on the SPI bus
*	params:
*		uint8_t byte - byte of data to send
*	returns:
*		SPI_status_t status - returns OK if write was successful, ERROR if unsuccessful
**************/
SPI_status_t SPI_write_byte(uint8_t byte);

/**************
* SPI_send_packet()
*	description:
*		Sends numerous SPI bytes given a pointer to a byte array and a
*		length of how many bytes to send
*	params:
*		uint8_t * pData - pointer to byte array to send
*		size_t length - number of bytes to send
*	returns:
*		SPI_status_t status - returns OK if write was successful, ERROR if unsuccessful
**************/
SPI_status_t SPI_send_packet(uint8_t * pData, size_t length);

/**************
* SPI_flush()
*	description:
*		Blocks until SPI transmit buffer has completed transmitting
*	params:
*
*	returns:
*		SPI_status_t status - returns OK if successful, ERROR if unsuccessful
**************/
SPI_status_t SPI_flush(void);

SPI_status_t SPI_set_CSn(uint8_t val);

#endif /*__SPI_H__*/
