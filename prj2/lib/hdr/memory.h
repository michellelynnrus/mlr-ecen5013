#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "psp_config.h"


#include "psp_macros_sys.h"

/**************
* memmove_dma()
*	description:
*		This function is equivalent to my_memmove but uses DMA (if enabled in given platform's PSP layer)
*		i. This should take two pointers (one source and one destination) and a length of bytes to move from one location to the other.
*		ii. Must work correctly for overlapped regions between the two memory blocks.
*		iii. Should return an error if move fail for any reason.
*	params:
*		uint8_t * src - pointer to the source data
*		uint8_t * dst - pointer to the destination the data should be moved to
*		uint32_t length - length of the data to move (in bytes)
*	returns:
*		int8_t status - returns 0 if memmove was successful, -1 if unsuccessful
**************/
int8_t memmove_dma(uint8_t * src, uint8_t * dst, uint32_t length, uint8_t size);

/**************
* memset_dma()
*	description:
*		This function is equivalent to my_memset but uses DMA (if enabled in given platform's PSP layer)
*		i. This should take a pointer to a memory location, a length in bytes and set all locations of that memory to a given value.
*		ii. Should return an error if the function fails for any reason.
*	params:
*		uint8_t * src - pointer to the source data
*		uint32_t length - length of the data to set (in bytes)
*		uint8_t value - value to set memory range to
*	returns:
*		int8_t status - returns 0 if memset was successful, -1 if unsuccessful
**************/
int8_t memset_dma(uint8_t * src, uint32_t length, uint8_t value);


/**************
* my_memmove()
*	description: 
*		i. This should take two pointers (one source and one destination) and a length of bytes to move from one location to the other.
*		ii. Must work correctly for overlapped regions between the two memory blocks.
*		iii. Should return an error if move fail for any reason.
*	params:
*		uint8_t * src - pointer to the source data
*		uint8_t * dst - pointer to the destination the data should be moved to
*		uint32_t length - length of the data to move (in bytes)
*	returns:
*		int8_t status - returns 0 if memmove was successful, -1 if unsuccessful
**************/
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);

/**************
* my_memset()
*	description: 
*		i. This should take a pointer to a memory location, a length in bytes and set all locations of that memory to a given value.
*		ii. Should return an error if the function fails for any reason.
*	params:
*		uint8_t * src - pointer to the source data
*		uint32_t length - length of the data to set (in bytes)
*		uint8_t value - value to set memory range to
*	returns:
*		int8_t status - returns 0 if memset was successful, -1 if unsuccessful
**************/
int8_t my_memset(uint8_t * src, uint32_t length, uint8_t value);

/**************
* my_memzero()
*	description: 
*		i. This should take a pointer to a memory location and a length in bytes and zero out all of the memory.
*		ii. Should return an error if the function fails for any reason.
*	params:
*		uint8_t * src - pointer to the source data
*		uint32_t length - length of the data to set (in bytes)
*	returns:
*		int8_t status - returns 0 if memset was successful, -1 if unsuccessful
**************/
int8_t my_memzero(uint8_t * src, uint32_t length);

/**************
* my_reverse()
*	description: 
*		i. This should take a pointer to a memory location and a length in bytes and reverse the order of all of the bytes
*		ii. Should return an error if move fail for any reason.
*	params:
*		uint8_t * src - pointer to the source data
*		uint32_t length - length of the data to reverse (in bytes)
*	returns:
*		int8_t status - returns 0 if reverse was successful, -1 if unsuccessful
**************/
int8_t my_reverse(uint8_t * src, uint32_t length);



#endif /* __MEMORY_H__ */
