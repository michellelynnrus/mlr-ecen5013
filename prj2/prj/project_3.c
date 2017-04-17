#include <stdio.h>
#include "project_3.h"
#include "memory.h"

#if (PLATFORM_CODE == PLATFORM_KL25Z)
#include "spi.h"
#include "gpio.h"
#include "nordic.h"
#endif

#define MAX_BYTES_TO_TEST (5000)

/**************
* project_3_report()
**************/
void project_3_report(void){

	//Initialize system
	SYS_INIT();
	COUNTER_INIT();

	// initialize data for memmove/memset tests
	uint8_t numBytesToTest[] = {10, 100, 1000, 5000};
	uint8_t patterns[] = {0xAA, 0x55, 0xFF, 0x00};
	uint8_t data1 [MAX_BYTES_TO_TEST]; //will be 0xAA for memmove
	uint8_t data2 [MAX_BYTES_TO_TEST]; //will be 0x55 for memmove
	uint8_t data3 [MAX_BYTES_TO_TEST]; //will be 0xFF for memmove
	uint8_t movDestData [MAX_BYTES_TO_TEST]; //will alternate between 0xAA and 0x55 for memmove
	uint8_t bytes = 0;
	uint8_t pattern = 0;

	// initialize profiler variables
	uint16_t startTime = 0;
	uint16_t elapsedTime = 0;

	LOG_ITEM(PROFILE_MEMSET_START, 0, 0);

	for(uint8_t i = 0; i < 4; i++){
		bytes = numBytesToTest[i];
		pattern = patterns[i];

		LOG_ITEM(PROFILE_NUM_BYTES, (uint8_t *)&bytes, sizeof(bytes));

		startTime = COUNTER_GET_COUNT();
		memset((uint8_t *)&data1, bytes, pattern);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_STD, (uint8_t *)&elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		my_memset((uint8_t *)&data2, bytes, pattern);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_CUSTOM, (uint8_t *)&elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		//note- this will return -1 if not supported for given platform
		int8_t dmaStatus = memset_dma((uint8_t *)&data3, bytes, pattern);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		if (dmaStatus < 0){
			LOG_ITEM(DMA_NO_SUPPORT, 0, 0);
		} else {
			LOG_ITEM(PROFILE_MEM_STD, (uint8_t *)&elapsedTime, sizeof(elapsedTime));
		}
	}

	//don't profile this, just set the memory to alternating values/clear
	memset((uint8_t *)&data1, MAX_BYTES_TO_TEST, patterns[0]); // all 0xAA
	memset((uint8_t *)&data2, MAX_BYTES_TO_TEST, patterns[1]); // all 0x55
	memset((uint8_t *)&data3, MAX_BYTES_TO_TEST, patterns[2]); // all 0xFF
	memset((uint8_t *)&movDestData, MAX_BYTES_TO_TEST, patterns[3]); // all 0x00

	LOG_ITEM(PROFILE_MEMMOVE_START, 0, 0);

	for(uint8_t i = 0; i < 4; i++){
		bytes = numBytesToTest[i];
		pattern = patterns[i];

		LOG_ITEM(PROFILE_NUM_BYTES, (uint8_t *)&bytes, sizeof(bytes));

		startTime = COUNTER_GET_COUNT();
		memmove((uint8_t *)&data1, (uint8_t *)&movDestData, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_STD, (uint8_t *)&elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		my_memset((uint8_t *)&data2, (uint8_t *)&movDestData, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_CUSTOM, (uint8_t *)&elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		//note- this will return -1 if not supported for given platform
		int8_t dmaStatus = memset_dma((uint8_t *)&data3, (uint8_t *)&movDestData, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		if (dmaStatus < 0){
			LOG_ITEM(DMA_NO_SUPPORT, 0, 0);
		} else {
			LOG_ITEM(PROFILE_MEM_STD, (uint8_t *)&elapsedTime, sizeof(elapsedTime));
		}
	}


#if (PLATFORM_CODE == PLATFORM_KL25Z)
	// Don't do this for any other platform

	SPI_init();
	GPIO_nrf_init();

	uint8_t readReg = 0;
	readReg = nrf_read_config();


#endif




	while (1){
		//do nothing for now
	}
	
}
