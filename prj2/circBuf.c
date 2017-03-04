#include "circBuf.h"


CB_Status_t CB_AddItem(CB_t * circBuf, uint8_t item){
	//Check for a null pointer
	if (!circBuf) {
		return NULL_PTR;
	} 
	
	//If full, return full
	if (CB_Full(circBuf) == FULL){
		return FULL;
	}
	
	//If not full, check cases
	
	if (CB_Empty(circBuf) != EMPTY){
		
		//If not empty, check boundary condition
		if ((circBuf->head - circBuf->buffer) >= (length - 1)) {
		
			//If boundary condition (head at end of allocated memory space)
			circBuf->head = circBuf->buffer;
		
		} else {
			
			//If no boundary condition, increment head pointer
			(circBuf->head)++;
		
		}
	} //If empty, don't modify head pointer
	
	//Set value at updated head pointer to item
	*(circBuf->head) = item;
	
	//Increment count
	circBuf->count++;
	
	return OK;	
}


CB_Status_t CB_RemoveItem(CB_t * circBuf, uint8_t * item){
	//Check for a null pointer
	if (!circBuf) {
		return NULL_PTR;
	} 
	
	//If empty, return empty
	if (CB_Empty(circBuf) == EMPTY){
		return CB_Empty;
	}
	
	//If not empty, store data at tail pointer to item pointer
	*item = *(circBuf->tail);
	
	//Decrement count
	circBuf->count--;
	
	//Check if empty again; don't increment tail if empty
	if (CB_Empty(circBuf) != EMPTY){
		//If not empty, check boundary condition
		if ((circBuf->tail - circBuf->buffer) >= (length - 1)) {
		
			//If boundary condition (tail at end of allocated memory space)
			circBuf->tail = circBuf->buffer;
		
		} else {
			
			//If no boundary condition, increment tail pointer
			(circBuf->tail)++;
		
		}
	}
	
	return UNKNOWN_ERROR;
}


CB_Status_t CB_Full(CB_t * circBuf){
	//Check for a null pointer
	if (!circBuf) {
		return NULL_PTR;
	} 
	
	//Can I just do this with the count?
	if (count == length){
		return FULL;
	}
	
	/*//check if tail is at boundary condition
	if ((circBuf->tail - circBuf->buffer) >= (length - 1)) {
		//check if tail would catch up to head
		if (circBuf->head == circBuf->buffer) {
			return FULL;
		}
	} else {
		//not at boundary condition, check if tail is one element behind head
		if (
	*/
	return OK;
}


CB_Status_t CB_Empty(CB_t * circBuf){
	//Check for a null pointer
	if (!circBuf) {
		return NULL_PTR;
	} 
	
	/*//Check if head and tail are at the same location
	if (circBuf->head == circBuf->tail){
		return EMPTY;
	}*/
	
	//Would it also work to use the count?

	if (count == 0){
		return EMPTY;
	}
	
	
	return UNKNOWN_ERROR;
}


CB_Status_t CB_Peek(CB_t * circBuf, uint16_t index, uint8_t * data){
	//Check for a null pointer
	if (!circBuf) {
		return NULL_PTR;
	} 
	
	//Set data to data at index of buffer, offset from last added item (tail)
	*data = *(circBuf->tail + index);
	
	return OK;
}


CB_Status_t CB_Allocate(CB_t * circBuf, uint16_t length){
	//Check for a null pointer
	if (!circBuf) {
		return NULL_PTR;
	} 
	
	//allocate length bytes in memory
	circBuf = (CB_t *) malloc(length);
	
	//initialize CB_t fields
	circBuf->head = circBuf->buffer;
	circBuf->tail = circBuf->buffer;
	circBuf->length = length;
	circBuf->count = 0;
	
	return OK;
}


CB_Status_t CB_Destroy(CB_t * circBuf){
	//Check for a null pointer
	if (!circBuf) {
		return NULL_PTR;
	} 
	
	//free memory in buffer pointer
	free(circBuf->buffer);
	
	//clear CB_t fields
	circBuf->head = circBuf->buffer;
	circBuf->tail = circBuf->buffer;
	circBuf->length = 0;
	circBuf->count = 0;
	
	return OK;
}


