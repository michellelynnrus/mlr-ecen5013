#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include "MKL25Z4.h"

#define LED_RED (0)
#define LED_GREEN (1)
#define LED_BLUE (2)

typedef enum {
	GPIO_OK = 1,
	GPIO_ERROR = 2,
} GPIO_status_t;


/**************
* GPIO_nrf_init()
*	description:
*		Initializes the GPIO pins associated with the nrf and SPI devices
*	params:
*
*	returns:
*		GPIO_status_t status - returns OK if init was successful, ERROR if unsuccessful
**************/
GPIO_status_t GPIO_nrf_init(void);

GPIO_status_t GPIO_poll_nrf(void);

void GPIO_SetLEDEnState(uint8_t ledID, uint8_t enState);

#endif /*__GPIO_H__*/
