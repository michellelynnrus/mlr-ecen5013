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
*		int32_t base - base of the ascii string to return (i.e. 10, 16, 2, etc)
*	returns:
*		int8_t * - retStr - pointer to return data 
**************/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base){
	//int8_t rem = data;
	int8_t i = 0;

	uint32_t rem = 0;
	uint8_t negFlg = 0;
	
	//little_to_big32(&data, 1);
	
	uint32_t uData = data;
	
	if (data == 0) {
		*str = '0';
		i++;
	} else if (data < 0 && base == 10){
		//handle the negative value
		printf("neg\n");
		uData = (uint32_t)(data * (-1));
		negFlg = 1;
	}
	
	while (uData != 0){
		rem = uData % base; 

		// add ascii offset
		if (rem >= 10 ){
			*(str+i)= rem + 55;
		} else {
			*(str+i) = rem + 48;
		}
		uData = uData/base; 
		i++;
	}
	
	if (base == 10 && negFlg){
		*(str+i) = '-';
		i++;
	}
	
	*(str+i) = '\0';
	
	my_reverse(str, i);

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
	uint8_t i = 0;
	uint8_t len = 0;
	int32_t data = 0;
	
	while (*(str + len) != '\0'){
		len++;	
	}

	for (i = 0; i < len; i++){
		data = data * 10 + *(str+i) - 48 ;
	}
	
	//little_to_big32(&data, 1);
	
	return data;
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