#include "data.h"
#include "memory.h"

#include <stdio.h>

/**************
* my_itoa()
*	description: 
*		i. Integer-to-asciI needs to convert data from a standard integer type into an ascii string. Need to handle signed data.
*	params:
*		int8_t * str - pointer to return data
*		int8_t data - integer data to convert
*		int32_t base - base of the integer (i.e. 10, 16, 2, etc)
*	returns:
*		int8_t * - retStr - pointer to return data
**************/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base){
	
	return 0;
}

/**************
* my_atoi()
*	description: 
*		i. AsciI-to-Integer needs to convert data back from an ASCII represented string into an integer type. Need to handle signed data.
*	params:
*		int8_t * str - pointer to ASCII string to convert
*	returns:
*		int32_t retInt - integer value converted from ASCII
**************/
int32_t my_atoi(int8_t * str){

	return 0;
}

/**************
* big_to_little32()
**************/
int8_t big_to_little32(uint32_t * data, uint32_t length){
	//literally just swapping bytes, they both require the same code
	return little_to_big32(data, length);
}

/**************
* little_to_big32()
**************/
int8_t little_to_big32(uint32_t * data, uint32_t length){
	
	if (data == NULL || length <= 0) {
		//return non-zero code indicating failure
		//NULL pointer or invalid length
     	return -1; 
	}
	
	uint8_t * byte;
	//reverse the order of bytes in each 32 bit element
	for (int i = 0; i < length; i++){
		byte = (uint8_t *)(data + i);
		my_reverse(byte, 4);
	}

	return 0;
}


/**************
* print_memory()
**************/
void print_memory(uint8_t * start, uint32_t length){
	if (start == NULL) {
		//NULL pointer, no status return val so printf (yay)
		printf("print_memory error: NULL pointer\n");
		return;
	}
	printf("0x ");
	for (int i = 0; i < length; i++){
		printf("%02x ", *(start + i));
	}
	printf("\n");
	return;
}