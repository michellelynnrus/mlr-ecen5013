#include "test_memory.h"
#include "circBuf.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#define LENGTH_8 8


// Allocate-Free - Checks that a dynamic buffer can be created on the heap
static void test_allocateFree(void ** state){
	CB_t * bufPtr = NULL;
	CB_Status_t status;
	CB_Status_t expStat = OK;
	
	//allocate buffer, should pass
	status = CB_Allocate(&bufPtr, LENGTH_8);
	assert_int_equal(status, expStat);
	
	//free buffer, should pass
	status = CB_Destroy(bufPtr);
	assert_int_equal(status, expStat);
}

// Invalid Pointer - Check that buffer pointer is valid
static void test_nullPtr(void ** state){

	CB_t * bufPtr_N = NULL;
	CB_Status_t status;
	CB_Status_t expStat = NULL_PTR;
	uint8_t item = 0xAA;
	
	//null pointers, should fail
	status = CB_AddItem(bufPtr_N, item);
	assert_int_equal(status, expStat);
	
}

// Non-initialized Buffer - Check that buffer is initialized
static void test_nonInit(void ** state){
	
	CB_t * bufPtr_N = NULL;
	CB_Status_t status;
	CB_Status_t expStat = NULL_PTR;
	uint8_t item = 0xAA;
	
	//buffer is not initialized, should fail
	status = CB_AddItem(bufPtr_N, item);
	assert_int_equal(status, expStat);
	
}

// Add-Remove - Check that add and then a remove returns the same item for full length of buffer
static void test_addRemove(void ** state){
	CB_t * bufPtr = NULL;
	
	uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t exp[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t item;
	uint8_t * dataPtr = &item;
	
	CB_Status_t status;
	CB_Status_t expStat = OK;
	
	status = CB_Allocate(&bufPtr, LENGTH_8);
	
	//add data until full
	for (uint8_t i = 0; i < LENGTH_8 ; i++){
		status = CB_AddItem(bufPtr, data[i]);
		assert_int_equal(status, expStat);
	}
	
	//make sure full buffer is what we expect
	assert_memory_equal(bufPtr->buffer, &exp, 8);
		
	//remove data until empty, compare to expected
	for (uint8_t i = 0; i < LENGTH_8; i++){
		status = CB_RemoveItem(bufPtr, dataPtr);
		assert_int_equal(status, expStat);
		assert_int_equal(*dataPtr, exp[i]);
	}
}

// Buffer Full - Check buffer reports true for full
static void test_bufFull(void ** state){

	CB_t * bufPtr = NULL;
	
	uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8};

	CB_Status_t status;
	CB_Status_t expStat = FULL;
	
	status = CB_Allocate(&bufPtr, LENGTH_8);
	
	//add data until full
	for (uint8_t i = 0; i < LENGTH_8 ; i++){
		status = CB_AddItem(bufPtr, data[i]);

	}

	assert_memory_equal(bufPtr->buffer, &data, 8);
	
	status = CB_Full(bufPtr);
	assert_int_equal(status, expStat);
}


// Buffer Empty - Check buffer reports true for full
static void test_bufEmpty(void ** state){

	CB_t * bufPtr = NULL;

	CB_Status_t status;
	CB_Status_t expStat = EMPTY;
	
	status = CB_Allocate(&bufPtr, LENGTH_8);
	
	status = CB_Empty(bufPtr);
	assert_int_equal(status, expStat);
}

// Wrap Add - Test that your buffer can wrap around the edge boundary and add to the front
static void test_wrapAdd(void ** state){
	CB_t * bufPtr = NULL;
	
	uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t data2[] = {9, 10, 11, 12};
	uint8_t exp[] = {9, 10, 11, 12, 5, 6, 7, 8};
	uint8_t item;
	uint8_t * dataPtr = &item;
	
	CB_Status_t status;
	CB_Status_t expStat = OK;
	
	status = CB_Allocate(&bufPtr, LENGTH_8);
	
	//add data until full
	for (uint8_t i = 0; i < LENGTH_8; i++){
		status = CB_AddItem(bufPtr, data[i]);
		assert_int_equal(status, expStat);
	}
	
	//remove data 
	for (uint8_t i = 0; i < LENGTH_8/2; i++){
		status = CB_RemoveItem(bufPtr, dataPtr);
		assert_int_equal(status, expStat);
	}

	//add data
	for (uint8_t i = 0; i < LENGTH_8/2; i++){
		status = CB_AddItem(bufPtr, data2[i]);
		assert_int_equal(status, expStat);
	}
	
	assert_memory_equal(bufPtr->buffer, &exp, 8);
}


// Wrap Remove - Test that your buffer can wrap around the edge boundary and add to the front
static void test_wrapRemove(void ** state){
	CB_t * bufPtr = NULL;
	
	uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	uint8_t data2[] = {9, 10, 11, 12};
	uint8_t exp[] = {9, 10, 11, 12, 5, 6, 7, 8};
	uint8_t item;
	uint8_t * dataPtr = &item;
	
	CB_Status_t status;
	CB_Status_t expStat = OK;
	
	status = CB_Allocate(&bufPtr, LENGTH_8);
	
	//add data until full
	for (uint8_t i = 0; i < LENGTH_8; i++){
		status = CB_AddItem(bufPtr, data[i]);
		assert_int_equal(status, expStat);
	}
	
	//remove data 
	for (uint8_t i = 0; i < LENGTH_8/2; i++){
		status = CB_RemoveItem(bufPtr, dataPtr);
		assert_int_equal(status, expStat);
	}

	//add data
	for (uint8_t i = 0; i < LENGTH_8/2; i++){
		status = CB_AddItem(bufPtr, data2[i]);
		assert_int_equal(status, expStat);
	}
	
	//remove data until empty 
	for (uint8_t i = 0; i < LENGTH_8; i++){
		status = CB_RemoveItem(bufPtr, dataPtr);
		assert_int_equal(status, expStat);
	}
	
	//make sure full buffer is what we expect
	assert_memory_equal(bufPtr->buffer, &exp, 8);
	assert_int_equal(bufPtr->count, 0);
}



// Over Fill - Test that your buffer fails when too many items are added
static void test_overFill(void ** state){
	CB_t * bufPtr = NULL;
	
	uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

	CB_Status_t status;
	CB_Status_t expStat = OK;
	CB_Status_t expStat_err = FULL;
	
	status = CB_Allocate(&bufPtr, LENGTH_8);
	
	//add data until overfull
	for (uint8_t i = 0; i < LENGTH_8 + 4 ; i++){
		status = CB_AddItem(bufPtr, data[i]);
		if (i < LENGTH_8) {
			assert_int_equal(status, expStat);
		} else {
			assert_int_equal(status, expStat_err);
		}
	}

	assert_memory_equal(bufPtr->buffer, &data, 8);
	
}


// Over Empty - Test that your buffer fails to remove an item when empty
static void test_overEmpty(void ** state){

	CB_t * bufPtr = NULL;
	
	CB_Status_t status;
	CB_Status_t expStat_err = EMPTY;
	uint8_t item;
	uint8_t * dataPtr = &item;
	
	status = CB_Allocate(&bufPtr, LENGTH_8);
	
	//try to remove from empty buffer
	status = CB_RemoveItem(bufPtr, dataPtr);
	assert_int_equal(status, expStat_err);

}



int main(void)
{
	
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_allocateFree),
        cmocka_unit_test(test_nullPtr),
		cmocka_unit_test(test_nonInit),
        cmocka_unit_test(test_addRemove),
		cmocka_unit_test(test_bufFull),
        cmocka_unit_test(test_bufEmpty),
		cmocka_unit_test(test_wrapAdd),
        cmocka_unit_test(test_wrapRemove),
		cmocka_unit_test(test_overFill),
        cmocka_unit_test(test_overEmpty),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}