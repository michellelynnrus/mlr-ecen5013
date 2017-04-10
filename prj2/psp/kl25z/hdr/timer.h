#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include "MKL25Z4.h"

/**************
* upCounter_init()
*	description:
*		initialize the timer/PWM module's up counter
*	params:
*		none
*	returns:
*		int8_t status - returns 0 if init was successful, -1 if unsuccessful
**************/
int32_t upCounter_init(void);

uint16_t upCounter_getCount(void);

#endif /*__TIMER_H__*/
