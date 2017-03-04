#ifndef __circBuf_h__
#define __circBuf_h__

/**************
* typedef struct CB_t
*	description: 
*		Circular buffer type - made of byte elements. Can be any given size at allocation. 
*	fields:
*		uint8_t buffer - Pointer to original memory location for the buffer
*		uint8_t head - Pointer to Head
*		uint8_t tail - Pointer to Tail
*		uint16_t length - Allocated size of the buffer
*		uint16_t count - Current count, must be updated with even add/remove
**************/
typedef struct CB_t {
	uint8_t * buffer;
	uint8_t head;
	uint8_t tail;
	uint16_t length;
	uint16_t count;
} CircBuf;

/**************
* typedef struct CB_Status_t
*	description: 
*		Circular buffer enum type
*	fields:
*		
**************/
typedef enum CB_Status_t {
	OK;
	FULL;
	EMPTY;
	NULLPTR;
	UNKNOWN_ERROR;
}

/**************
* CB_AddItem()
*	description: 
*		Adds an item to the buffer
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
*		Removes an item from the buffer
*	params:
*		CB_t * circBuf - circular buffer pointer
*		uint8_t item - Item to remove
*	returns:
*		CB_Status_t status - corresponding enum to action
**************/
CB_Status_t CB_RemoveItem(CB_t * circBuf, uint8_t item);

/**************
* CB_Full()
*	description: 
*		Querys the state of the buffer
*	params:
*		CB_t * circBuf - circular buffer pointer
*	returns:
*		CB_Status_t status - enumeration with the state of the buffer
**************/
CB_Status_t CB_Full(CB_t * circBuf);

/**************
* CB_Status_tmpty()
*	description: 
*		Querys the state of the buffer
*	params:
*		CB_t * circBuf - circular buffer pointer
*	returns:
*		CB_Status_t status - enumeration with the state of the buffer
**************/
CB_Status_t CB_Status_tmpty(CB_t * circBuf);

/**************
* CB_Peek()
*	description: 
*		Allows you to look at the nth item (must be less then count 
*		and greater or equal to zero)
*	params:
*		CB_t * circBuf - circular buffer pointer
*		uint16_t index - item index to peek at
*	returns:
*		CB_Status_t status - 
**************/
CB_Status_t CB_Peek(CB_t * circBuf, uint16_t index);

/**************
* CB_Allocate()
*	description: 
*		Allocates a circular buffer structure and the buffer 
*		portion in memory (on the heap) given a number of bytes
*	params:
*		CB_t * circBuf - circular buffer pointer
*		uint16_t length - length of bytes to allocate to buffer
*	returns:
*		CB_Status_t status - 
**************/
CB_Status_t CB_Allocate(CB_t * circBuf, uint16_t length);

/**************
* bufDestroy()
*	description: 
*		Frees the circular buffer from dynamic memory
*	params:
*		CB_t * circBuf - circular buffer pointer
*	returns:
*		CB_Status_t status - 
**************/
CB_Status_t CB_Destroy(CB_t * circBuf);






#endif /* __circBuf_h__ */