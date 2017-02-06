#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdint.h>
#include "memory.h"

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
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);

/**************
* my_atoi()
*	description: 
*		i. AsciI-to-Integer needs to convert data back from an ASCII represented string into an integer type. Need to handle signed data.
*	params:
*		int8_t * str - pointer to ASCII string to convert
*	returns:
*		int32_t retInt - integer value converted from ASCII
**************/
int32_t my_atoi(int8_t * str);

/**************
* big_to_little32()
*	description: 
*		i. Needs to be able to convert data types in memory from a big endian representation to little endian.
*		ii. Should return an error if the conversion fails for any reason.
*	params:
*		uint32_t * data - pointer to the source data
*		uint32_t length - length of the data to convert (in bytes)
*	returns:
*		int8_t status - returns 0 if convert was successful, -1 if unsuccessful
**************/
int8_t big_to_little32(uint32_t * data, uint32_t length);

/**************
* little_to_big32()
*	description: 
*		i. Needs to be able to convert data types in memory from a little endian representation to big endian.
*		ii. Should return an error if the conversion fails for any reason.
*	params:
*		uint32_t * data - pointer to the source data
*		uint32_t length - length of the data to convert (in bytes)
*	returns:
*		int8_t status - returns 0 if convert was successful, -1 if unsuccessful
**************/
int8_t little_to_big32(uint32_t * data, uint32_t length);


/**************
* print_memory()
*	description: 
*		i. This takes a pointer to memory and prints the hex output of bytes given a pointer to a memory location and a length of bytes to print.
*		NOTE: This function uses printf.
*	params:
*		uint32_t * data - pointer to memory
*		uint32_t length - length of the data to print (in bytes)
*	returns:
*		none
**************/
void print_memory(uint8_t * start, uint32_t length);



#endif /* __DATA_H__ */