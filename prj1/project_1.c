#include "project_1.h"

//global pointers so functions can all access data sets
uint8_t * setPtr_1 = NULL;
uint8_t * setPtr_2 = NULL;
uint8_t * setPtr_3 = NULL;

//global pointer for the array of arrays that itoa/atoi/test_data2 needs
uint8_t * charArrPtr_2 = NULL;

/**************
* project_1_report()
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
	uint8_t charArr_2[264];
	charArrPtr_2 = charArr_2;
	
	// running test functions
#if (PLATFORM_CODE!=2)
	printf("TEST_DATA1: \n");
#endif
	test_data1();
#if (PLATFORM_CODE!=2)
	printf("\n\nTEST_DATA2: \n");
#endif
	test_data2();
#if (PLATFORM_CODE!=2)
	printf("\n\nTEST_MEMORY: \n");
#endif
	test_memory();
	return;
}


/**************
* test_data1()
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
**************/
void test_data2(void){
	int32_t conv = 0;
	
	// loop through the 8 32-bit integers
	// store the string in each 33 bytes of charArrPtr_2 
	//   (it is sized this way to hold max 32 chars + string end char because binary)
	for (int i = 0; i < 8; i++){
		my_itoa((int8_t *)(charArrPtr_2 + i*33), *((int32_t *)setPtr_2+i), 10);
		//printf("i=%d itoa: %s, ",i,(char *) (charArrPtr_2 + i*33));
		//print_memory(charArrPtr_2 + i*33, 33);
	}

	//printf("\nset_2: ");
	print_memory(setPtr_2, 32);
	//printf("charArr: ");
	print_memory(charArrPtr_2, 264);
	
	for (int i = 0; i < 8; i++){

		conv = my_atoi((int8_t *)charArrPtr_2 + i*33);
		//printf("i=%d atoi: %d, ",i, conv);
		*(setPtr_2 + i*4) = conv;
		//print_memory(&conv, 4);
		
	}
	//printf("\nset_2: ");
	print_memory(setPtr_2, 32);

	return;
}


/**************
* test_memory()
**************/
void test_memory(void){
	
	uint32_t len = 32;
	/*printf("index:\t   ");
	for (int i = 0; i < len; i++){
		printf("%02d ", *(setPtr_2 + i));
	}
	printf("\n");
	*/
	
	//printf("1. \t");
	print_memory(setPtr_2, len); 

	my_reverse(setPtr_2, 12);
	my_memset(setPtr_2+16, 4, 0xEE);
	my_memmove(setPtr_2+25, setPtr_2+19, 6);
	my_memzero(setPtr_2+11, 5);
	my_memmove(setPtr_2, setPtr_2+8, 8);

	//printf("7. \t");
	print_memory(setPtr_2, len);
	
	return;
}
