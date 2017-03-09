#include "test_memory.h"
#include "data.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#define LENGTH_8 8

// Memmove - Invalid Pointers - Should return fail if pointers are NULL
static void test_biglittle_nullPtr(void ** state){
	
	uint32_t * src_N = NULL;
	int8_t status;
	
	//null pointers, should fail
	status = big_to_little32(src_N, 1);
	assert_int_equal(status, -1);

}

// Memmove - No Overlap - Should return a pass for a move
static void test_biglittle_valid(void ** state){

	uint32_t data = 0xF055AA0F;
	uint32_t exp = 0x0FAA55F0;
	
	uint32_t * dataPtr = &data;
	
	int8_t status;
	
	//both valid pointers, no overlap, should pass
	status = big_to_little32(dataPtr, 1);
	assert_int_equal(status, 0);
	assert_memory_equal(&data, &exp, 4);
	
}

// Memset - Invalid Pointers - Should return fail if pointers are NULL
static void test_littlebig_nullPtr(void ** state){
	
	uint32_t * src_N = NULL;
	int8_t status;
	
	//null src pointer, should fail
	status = little_to_big32(src_N, 1);
	assert_int_equal(status, -1);
	
}

// Memset - Check Set - Should accurately set region for LENGTH_8 Value
static void test_littlebig_valid(void ** state){

	uint32_t data = 0xF055AA0F;
	uint32_t exp = 0x0FAA55F0;
	
	uint32_t * dataPtr = &data;
	
	int8_t status;
	
	//both valid pointers, no overlap, should pass
	status = little_to_big32(dataPtr, 1);
	assert_int_equal(status, 0);
	assert_memory_equal(&data, &exp, 4);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_biglittle_nullPtr),
        cmocka_unit_test(test_biglittle_valid),
		cmocka_unit_test(test_littlebig_nullPtr),
        cmocka_unit_test(test_littlebig_valid),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}