#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdint.h>
#include <stdlib.h>

#if (std==c99)
#define INLINE_FUNC static inline __attribute__((always_inline))
#else
#define INLINE_FUNC __STATIC_INLINE
#endif

/**************
* typedef struct CB_t
*	description: 
*		Circular buffer type - made of byte elements. Can be any given size at allocation. 
*	fields:
*		uint8_t buffer - Pointer to original memory location for the buffer
*		uint8_t head - Pointer to Head, tracks newest item added
*		uint8_t tail - Pointer to Tail, tracks oldest item added
*		uint16_t length - Allocated size of the buffer
*		uint16_t count - Current count, must be updated with even add/remove
**************/
typedef struct CircBuf {
	uint8_t * buffer;
	volatile uint8_t * head;
	volatile uint8_t * tail;
	uint16_t length;
	volatile uint16_t count;
} CB_t;

/**************
* typedef struct CB_Status_t
*	description: 
*		Enum of status codes used as return values from CB functions.
*	fields:
*		OK - Nothing is inherently wrong with operation performed
*		FULL - Circular buffer is full
*		EMPTY - Circular buffer is empty
*		NULLPTR - Circular buffer pointer is null
*		UNKNOWN_ERROR - You broke something (may not be used)
**************/
typedef enum CircBuf_Status {
	CB_OK,
	CB_FULL,
	CB_EMPTY,
	CB_NULL_PTR,
	CB_MALLOC_ERR,
	CB_UNKNOWN_ERROR
} CB_Status_t;

/**************
* CB_AddItem()
*	description: 
*		Adds an item to the buffer. Increments head, then adds item
*	params:
*		CB_t * circBuf - circular buffer pointer
*		uint8_t item - Item to add
*	returns:
*		CB_Status_t status - corresponding enum to action
**************/
CB_Status_t CB_AddItem(CB_t * circBuf, uint8_t item);

/**************
* CB_RemoveItem()
*	description: 
*		Removes an item from the buffer. Remove item, then increment tail
*	params:
*		CB_t * circBuf - circular buffer pointer
*		uint8_t * item - Pointer to return removed item
*	returns:
*		CB_Status_t status - corresponding enum to action
**************/
CB_Status_t CB_RemoveItem(CB_t * circBuf, uint8_t * item);

/**************
* CB_Full()
*	description: 
*		Querys the state of the buffer
*	params:
*		CB_t * circBuf - circular buffer pointer
*	returns:
*		CB_Status_t status - enumeration with the state of the buffer
**************/
INLINE_FUNC CB_Status_t CB_Full(CB_t * circBuf){
	//Check for a null pointer
	if (!circBuf) {
		return CB_NULL_PTR;
	}

	//Can I just do this with the count?
	if (circBuf->count == circBuf->length){
		return CB_FULL;
	}

	return CB_OK;
}

/**************
* CB_Empty()
*	description: 
*		Querys the state of the buffer
*	params:
*		CB_t * circBuf - circular buffer pointer
*	returns:
*		CB_Status_t status - enumeration with the state of the buffer
**************/
INLINE_FUNC CB_Status_t CB_Empty(CB_t * circBuf){
	//Check for a null pointer
	if (!circBuf) {
		return CB_NULL_PTR;
	}

	//Would it also work to use the count?
	if (circBuf->count == 0){
		return CB_EMPTY;
	}


	return CB_OK;
}

/**************
* CB_Peek()
*	description: 
*		Allows you to look at the nth item (must be less then count 
*		and greater or equal to zero)
*	params:
*		CB_t * circBuf - circular buffer pointer
*		uint16_t index - item index to peek at, offset from last added item (tail)
*		uint8_t * value - pointer to value to return
*	returns:
*		CB_Status_t status - enumeration with the state of the buffer
**************/
CB_Status_t CB_Peek(CB_t * circBuf, uint16_t index, uint8_t * value);

/**************
* CB_Allocate()
*	description: 
*		Allocates a circular buffer structure and the buffer 
*		portion in memory (on the heap) given a number of bytes
*	params:
*		CB_t ** circBuf - pointer to circular buffer pointer
*		uint16_t length - length of bytes to allocate to buffer
*	returns:
*		CB_Status_t status - enumeration with the state of the buffer
**************/
CB_Status_t CB_Allocate(CB_t ** circBuf, uint16_t length);

/**************
* CB_Destroy()
*	description: 
*		Frees the circular buffer from dynamic memory
*	params:
*		CB_t * circBuf - circular buffer pointer
*	returns:
*		CB_Status_t status - enumeration with the state of the buffer
**************/
CB_Status_t CB_Destroy(CB_t * circBuf);






#endif /* __circBuf_h__ */
