#include "project_1.h"


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
	//uint32_t * set_1[32] = 0x0123456789ABCDEF0123456789ABCDEF;
	uint8_t set_2[32];
	uint8_t * setPtr_2 = set_2;
	for (uint8_t i = 0; i < 32; i++){
		*setPtr_2 = i;
		setPtr_2++;
	}
	//uint32_t *set_3[32] = abcdefghijklmnopqrstuvwxyzABCDEF;
	
	test_memory(set_2);
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
	
	return;
}

/**************
* test_data2()
*		i. Show your data functions work by calling the following functions in this order with the second array,  set_2 :  my_itoa() & then  print_memory()
*	params:
*		none
*	returns:
*		none
**************/
void test_data2(void){
	
	return;
}

/**************
* test_data3()
*		i. Show your data functions work by calling the following functions in this order with the second array,  set_3 :  my_atoi() & then  print_memory()
*	params:
*		none
*	returns:
*		none
**************/
void test_data3(void){
	
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
void test_memory(uint8_t * ptr){
	
	printf("index:\t   ");
	for (int i = 0; i < 32; i++){
		printf("%02d ", *(ptr + i));
	}
	printf("\n");
	uint32_t len = 32;
	printf("1. \t");
	print_memory(ptr, len); 

	my_reverse(ptr, 12);
	//printf("2. \t");
	//print_memory(ptr, len);
	
	my_memset(ptr+16, 4, 0xEE);
	//printf("3. \t");
	//print_memory(ptr, len);
	
	my_memmove(ptr+25, ptr+19, 6);
	//printf("4. \t");
	//print_memory(ptr, len);
	
	my_memzero(ptr+11, 5);
	//printf("5. \t");
	//print_memory(ptr, len);
	
	my_memmove(ptr, ptr+8, 8);
	//printf("6. \t");
	//print_memory(ptr, len);
	
	printf("7. \t");
	print_memory(ptr, len);
	
	return;
}
