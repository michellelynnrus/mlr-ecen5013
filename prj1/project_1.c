#include "project_1.h"

//global pointers so functions can all access data sets
uint8_t * setPtr_1 = NULL;
int8_t * setPtr_2 = NULL;
uint8_t * setPtr_3 = NULL;

//global pointer for the array of arrays that itoa/atoi/test_data2 needs
uint8_t * charArrPtr_2 = NULL;

/**************
* project_1_report()
*		i. set_1 : Create an array of 32 bytes (unsigned). Initialize this array to increasing hex numbers like: 0x0123456789ABCDEF0123456789ABCDEF
*		ii. set_2 : Create another array of 32 bytes (unsigned). Initialize this array to an increasing integer count of 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...., 31.
*		iii. set_3 : Create another array of 32 bytes (unsigned). Initialize this array to an increasing integer count of “abcdefghijklmnopqrstuvwxyzABCDEF”
*		iv. This should call the functions below in order.
*	params:
*		none
*	returns:
*		none
**************/
void project_1_report(void){
	
	//initializing data sets
	
	uint8_t set_1[32]; //0x0123456789ABCDEF0123456789ABCDEF;
	setPtr_1 = set_1;
	for (uint8_t i = 0; i < 32; i++){
		if (i < 16){
			*(setPtr_1 + i)= i;
		} else {
			*(setPtr_1 + i)= i-16;
		}
	}
	
	uint8_t set_2[32];
	setPtr_2 = set_2;
	for (uint8_t i = 0; i < 32; i++){
		*(setPtr_2 + i)= i;
	}
	
	//set_2 is 32 8-bit integers, equivalent to 8 32-bit integers
	// the max chars needed to represent a 32 bit integer is sizeof(char)*32
	//   because each bit needs a char if converted to binary
	//   + 1 extra char for the string end character
	// This means to represent each integer as a string we need a max of:
	//   8 chars * (32 bits + 1 end char) = 264
	int8_t charArr_2[264];
	charArrPtr_2 = charArr_2;
	
	// running test functions
	printf("TEST_DATA1: \n");
	test_data1();
	printf("\n\nTEST_DATA2: \n");
	test_data2();
	printf("\n\nTEST_MEMORY: \n");
	test_memory();
	return;
}


/**************
* test_data1()
*		i. Show your data functions work by calling the following functions in this order with the first array,  set_1 :
*			1. print_memory() 
*			2. big_to_little32()
*			3. print_memory() 
*			4. little_to_big32() 
*			5. print_memory()
*	params:
*		none
*	returns:
*		none
**************/
void test_data1(void){
	uint32_t * setPtr32_1 = (uint32_t *)setPtr_1;
	
	print_memory(setPtr_1, 32); 
	big_to_little32(setPtr32_1, 32/4);
	print_memory(setPtr_1, 32);
	little_to_big32(setPtr32_1, 32/4); 
	print_memory(setPtr_1, 32);
	return;
}

/**************
* test_data2()
*		i. Show your data functions work by calling the following functions in this order with the second array,  set_2 :  
*			1. my_itoa()
*			2. print_memory() 
*			3. my_atoi()
*			4. print_memory()
*	params:
*		none
*	returns:
*		none
**************/
void test_data2(void){
	int32_t conv = 0;
	
	// loop through the 8 32-bit integers
	// store the string in each 33 bytes of charArrPtr_2 
	//   (it is sized this way to hold max 32 chars + string end char because binary)
	for (int i = 0; i < 8; i++){
		my_itoa(charArrPtr_2 + i*33, *((int32_t *)setPtr_2+i), 10);
		printf("i=%d itoa: %s, ",i,(char *) (charArrPtr_2 + i*33));
		//print_memory(charArrPtr_2 + i*33, 33);
	}
	printf("\nset_2: ");
	print_memory(setPtr_2, 32);
	printf("charArr: ");
	print_memory(charArrPtr_2, 264);
	
	for (int i = 0; i < 8; i++){

		conv = my_atoi(charArrPtr_2 + i*33);
		printf("i=%d atoi: %d, ",i, conv);
		*(setPtr_2 + i*4) = conv;
		//print_memory(&conv, 4);
		
	}
	printf("\nset_2: ");
	print_memory(setPtr_2, 32);

	return;
}


/**************
* test_memory()
*		i. Perform the following operations on a point to the set_2 data block.
*			1. print_memory(); all 32 bytes
*			2. my_reverse(); On the first 12 bytes
*			3. my_memset();  Set 0xEE on the 17th to the 20th bytes ([16]-[19])
*			4. my_memmove(); Move the 6 bytes starting at the 26th byte ([25]), to the 20th position ([19])
*			5. memzero();  Bytes 12 - 16 ([11] - [15])
*			6. my_memmove(); Move the 8 bytes starting at the 1st byte ([0]), to the 9th position ([8])
*			7. print_memory(); all 32 bytes
*	params:
*		uint32_t * ptr - pointer to data set to use, it is assumed for this test that the data is 32 bytes long
*	returns:
*		none
**************/
void test_memory(void){
	
	uint32_t len = 32;

	printf("1. \t");
	print_memory(setPtr_2, len); 

	my_reverse(setPtr_2, 12);
	my_memset(setPtr_2+16, 4, 0xEE);
	my_memmove(setPtr_2+25, setPtr_2+19, 6);
	my_memzero(setPtr_2+11, 5);
	my_memmove(setPtr_2, setPtr_2+8, 8);

	printf("7. \t");
	print_memory(setPtr_2, len);
	
	return;
}
