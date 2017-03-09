#include "memory.h"

#include <stdio.h>

/**************
* my_memmove()
**************/
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length){
	
	
	if (src == NULL || dst == NULL || length <= 0) {
		//return non-zero code indicating failure
		//NULL pointer or invalid length
     	return -1; 
	}
	
	if((src < dst) && (src+length >= dst)){
		
		//create a temporary array to hold the data (only if overlapping)
		//am I allowed to do this with the array...?
		uint8_t tmpData[length];
		uint8_t * tmpDataPtr = tmpData;
		//Loop through the data copy to new dst address
		for(int i = 0; i < length; i++){
			*(tmpDataPtr + i) = *(src + i);
		}
	
		//Loop through the data copy to new dst address
		for(uint8_t i = 0; i < length; i++){
			*(dst+i) = *(tmpDataPtr+i);
		}
	} else {

		//Loop through the data copy to new dst address
		for(uint8_t i = 0; i < length; i++){
			*(dst+i) = *(src+i);
		}
	}
	return 0;
}

/**************
* my_memset()
**************/
int8_t my_memset(uint8_t * src, uint32_t length, uint8_t value){

	if (src == NULL || length <= 0) {
		//return non-zero code indicating failure
		//NULL pointer or invalid length
     	return -1; 
	}

	//Loop through the data and set values
	for(uint8_t i = 0; i < length; i++){
		*src = value;
		src++;

	}

	return 0;
}

/**************
* my_memzero()
**************/
int8_t my_memzero(uint8_t * src, uint32_t length){
	//call memset and pass in 0 as the value to set 
	return my_memset(src, length, 0);
}

/**************
* my_reverse()
**************/
int8_t my_reverse(uint8_t * src, uint32_t length){

	
	if (src == NULL || length <= 0) {
		//return non-zero code indicating failure
		//NULL pointer or invalid length
     	return -1; 
	}
	
	uint8_t * newPtr = src + length - 1;
	uint8_t tempVal;	

	//Loop through the data and swap first/last values
	//Repeat until we meet in the middle
	for(uint8_t i = 0; i < length/2; i++){
		tempVal = *src;
		*src = *newPtr;
		*newPtr = tempVal;

		src++;
		newPtr--;

	}
	
	return 0;
}


