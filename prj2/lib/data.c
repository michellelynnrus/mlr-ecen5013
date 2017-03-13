#include "data.h"
#include "memory.h"

#include <stdio.h>

/**************
* my_itoa()
**************/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base){

	int8_t i = 0;

	uint32_t rem = 0;
	uint8_t negFlg = 0;
	
	//check for NULL ptr
	if (str == NULL){
		//return pointer to an error code -1
		return (int8_t *) -1;
	}
	
	uint32_t uData = data;
	
	if (data == 0) {
		*str = '0';
		i++;
	} else if (data < 0 && base == 10){
		//handle the negative value - make the value a positive, unsigned integer
		uData = (uint32_t)(data * (-1));
		negFlg = 1; //set a negative indicator flag
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
	
	//add a negative sign if the value was determined to be negative earlier
	if (base == 10 && negFlg){
		*(str+i) = '-';
		i++;
	}
	
	//string end character
	*(str+i) = '\0';
	
	//reverse the string so it's in the correct order
	my_reverse((uint8_t *)str, i);

	return str;
}

/**************
* my_atoi()
**************/
int32_t my_atoi(int8_t * str){
	uint8_t i = 0;
	uint8_t len = 0;
	int32_t data = 0;
	uint8_t negFlg = 0;
	
	//check for NULL ptr
	if (str == NULL){
		//return an error code -1
		return -1;
	}
	
	//determine length by searching for string end character
	while (*(str + len) != '\0'){
		len++;	
	}
	
	//if the first character is '-', set a flag to indicate this is a negative value
	//  and increment our index to skip calculations on the negative sign
	if (*str == '-'){
		negFlg = 1;
		i++;
	}
	
	// do math, determine the value of the string as an integer
	while (i < len){
		data = data * 10 + *(str+i) - 48 ;
		i++;
	}
	
	//negate the value if the negative flg was set earlier
	if (negFlg){
		data = data * (-1);
	}
	
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
#if (PLATFORM_CODE != 2)
	//only run printf commands if not the FRDM board
	printf("0x ");
	for (int i = 0; i < length; i++){
		printf("%02x ", *(start + i));
	}
	printf("\n");
#endif
	return;
}