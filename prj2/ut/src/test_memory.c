#include "test_memory.h"
#include "memory.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#define LENGTH_8 8

// Memmove - Invalid Pointers - Should return fail if pointers are NULL
static void test_memmove_nullPtr(void ** state){
	
	uint8_t * src_N = NULL;
	uint8_t * dst_N = NULL;
	int8_t status;
	
	//null pointers, should fail
	status = my_memmove(src_N, dst_N, LENGTH_8/2);
	assert_int_equal(status, -1);

}

// Memmove - No Overlap - Should return a pass for a move
static void test_memmove_noOverlap(void ** state){

	uint8_t vals[] 	= {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] 	= {1, 2, 3, 4, 1, 2, 3, 4};
	uint8_t * src = &vals[0]; //vals[0:3]
	uint8_t * dst = &vals[LENGTH_8/2]; //vals[4:7]
	
	int8_t status;
	
	//both valid pointers, no overlap, should pass
	status = my_memmove(src, dst, LENGTH_8/2);
	assert_int_equal(status, 0);
	assert_memory_equal(&vals, &exp, LENGTH_8);
	
}

// Memmove - SRC in DST region Overlap - Should succeed at this
static void test_memmove_SRCinDST(void ** state){

	uint8_t vals[] 	= {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] 	= {1, 2, 1, 2, 3, 4, 7, 8};
	uint8_t * src = &vals[0]; //vals[0:3]
	uint8_t * dst = &vals[2]; //vals[2:5]
	
	int8_t status;
	
	//both valid pointers, SRC in DST overlap, should pass
	status = my_memmove(src, dst, LENGTH_8/2);
	assert_int_equal(status, 0);
	assert_memory_equal(&vals, &exp, LENGTH_8);

}

// Memmove - DST in SRC region Overlap - Should succeed at this
static void test_memmove_DSTinSRC(void ** state){

	uint8_t vals[] 	= {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] 	= {3, 4, 5, 6, 5, 6, 7, 8};
	uint8_t * src = &vals[2]; //vals[2:5]
	uint8_t * dst = &vals[0]; //vals[0:3]
	int8_t status;
	
	//both valid pointers, DST in SRC overlap, should pass
	status = my_memmove(src, dst, LENGTH_8/2);
	assert_int_equal(status, 0);
	assert_memory_equal(&vals, &exp, LENGTH_8);

}

// Memset - Invalid Pointers - Should return fail if pointers are NULL
static void test_memset_nullPtr(void ** state){
	
	uint8_t * src_N = NULL;
	int8_t status;
	
	//null src pointer, should fail
	status = my_memset(src_N, LENGTH_8/2, 0xF);
	assert_int_equal(status, -1);
	
}

// Memset - Check Set - Should accurately set region for LENGTH_8 Value
static void test_memset_checkSet(void ** state){

	uint8_t vals[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] = {1, 2, 0xF, 0xF, 0xF, 0xF, 7, 8};
	uint8_t * src = &vals[2]; //vals[2:5]
	int8_t status;
	
	//set region to 0xF, should pass
	status = my_memset(src, LENGTH_8/2, 0xF);
	assert_int_equal(status, 0);
	assert_memory_equal(&vals, &exp, LENGTH_8);
}

// Memzero - Invalid Pointers - Should return fail if pointers are NULL
static void test_memzero_nullPtr(void ** state){
		
	uint8_t * src_N = NULL;
	int8_t status;
	
	//null src pointer, should fail
	status = my_memzero(src_N, LENGTH_8/2);
	assert_int_equal(status, -1);
}

// Memzero - Check Set - Should accurately set region to zeroes
static void test_memzero_checkSet(void ** state){
	
	uint8_t vals[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] = {1, 2, 0x0, 0x0, 0x0, 0x0, 7, 8};
	uint8_t * src = &vals[2]; //vals[2:5]
	int8_t status;
	
	//set region to 0xF, should pass
	status = my_memzero(src, LENGTH_8/2);
	assert_int_equal(status, 0);
	assert_memory_equal(&vals, &exp, LENGTH_8);
}

// Reverse - Invalid Pointers - Should return fail if pointers are NULL
static void test_reverse_nullPtr(void ** state){
	uint8_t * src_N = NULL;
	int8_t status;
	
	//null src pointer, should fail
	status = my_reverse(src_N, LENGTH_8/2);
	assert_int_equal(status, -1);
}

// Reverse - Check Odd reverse - Should check that reverse succeeded for even length
static void test_reverse_checkOdd(void ** state){
	uint8_t vals[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] = {1, 2, 5, 4, 3, 6, 7, 8};
	uint8_t * src = &vals[2]; //vals[2:5]
	int8_t status;
	
	//reverse (odd), should pass
	status = my_reverse(src, LENGTH_8/2-1);
	assert_int_equal(status, 0);
	assert_memory_equal(&vals, &exp, LENGTH_8);
}

// Reverse - Check Even reverse - Should check that reverse succeeded for even length
static void test_reverse_checkEven(void ** state){
	uint8_t vals[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] = {1, 2, 6, 5, 4, 3, 7, 8};
	uint8_t * src = &vals[2]; //vals[2:5]
	int8_t status;
	
	//reverse (even), should pass
	status = my_reverse(src, LENGTH_8/2);
	assert_int_equal(status, 0);
	assert_memory_equal(&vals, &exp, LENGTH_8);
}

// Reverse - Check characters - Should be able to reverse any character set (256 byte array of 0-255)
static void test_reverse_checkChars(void ** state){
	uint8_t chars [256];
	uint8_t exp_chars [256];
	uint8_t * src = chars;
	for (uint32_t i = 0; i < 256; i++){
		chars[i] = i;
		exp_chars[i] = 255-i;
	}
	
	int8_t status;
	
	//reverse 0-255, should pass
	status = my_reverse(src, 256);
	assert_int_equal(status, 0);
	assert_memory_equal(&chars, &exp_chars, 256);
	
	
}

int main(void)
{

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_memmove_nullPtr),
        cmocka_unit_test(test_memmove_noOverlap),
		cmocka_unit_test(test_memmove_SRCinDST),
        cmocka_unit_test(test_memmove_DSTinSRC),
		cmocka_unit_test(test_memset_nullPtr),
        cmocka_unit_test(test_memset_checkSet),
		cmocka_unit_test(test_memzero_nullPtr),
        cmocka_unit_test(test_memzero_checkSet),
		cmocka_unit_test(test_reverse_nullPtr),
		cmocka_unit_test(test_reverse_checkOdd),
        cmocka_unit_test(test_reverse_checkEven),
        cmocka_unit_test(test_reverse_checkChars),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}