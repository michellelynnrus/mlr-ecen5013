#include "memory.h"

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
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length){
	
	if (length <= 0) {
		//return non-zero code indicating failure, in this case length must be nonzero and positive
     	return -1; 
	}

	//Loop through the data copy to new dst address
	for(int i = 0; i < length; i++){
		*dst = *src;
		src++;
		dst++;

	}
	return 0;
}

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
int8_t my_memset(uint8_t * src, uint32_t length, uint8_t value){

	if (length <= 0) {
		//return non-zero code indicating failure, in this case length must be nonzero and positive
     	return -1; 
	}

	//Loop through the data and set values
	for(int i = 0; i < length; i++){
		*src = value;
		src++;

	}

	return 0;
}

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
int8_t my_memzero(uint8_t * src, uint32_t length){
	
	return my_memset(src, length, 0);
}

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
int8_t my_reverse(uint8_t * src, uint32_t length){
	int8_t * newPtr = src + length - 1;
	int8_t tempVal;	
	
	if (length <= 0) {
		//return non-zero code indicating failure, in this case length must be nonzero and positive
     	return -1; 
	}

	//Loop through the data and swap first/last values
	//Repeat until we meet in the middle
	for(int i = 0; i < length/2; i++){
		tempVal = *src;
		*src = *newPtr;
		*newPtr = tempVal;

		src++;
		newPtr--;

	}
	
	return 0;
}


