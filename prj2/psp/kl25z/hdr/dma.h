#ifndef __DMA_H__
#define __DMA_H__

#include <stdint.h>
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "psp_macros_log.h"

/**************
* dma0_move()
*	description:
*		Channel initialization
* 		Transfer control descriptor (in channel registers) needs to be loaded with
* 			-address pointers
* 			-byte-transfer count
* 			-control information
* 		using accesses from the slave peripheral bus
*	params:
*		uint8_t * src - pointer to the source data
*		uint8_t * dst - pointer to the destination the data should be moved to
*		uint32_t length - length of the data to move (in bytes)
*		uint8_t size - size of source/dest bus cycle for the DMA controller
*			(driver currently only supports ssize=dsize)
*	returns:
*		int8_t status - returns 0 if init was successful, -1 if unsuccessful
**************/
int32_t dma0_move(uint8_t * src, uint8_t * dst, uint32_t length, uint8_t size);


#endif /*__DMA_H__*/
