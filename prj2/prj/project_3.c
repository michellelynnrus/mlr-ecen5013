#include <stdio.h>
#include "project_3.h"
#include "memory.h"
#include <string.h>

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
	uint32_t numBytesToTest[] = {10, 100, 1000, 5000};
	uint8_t data1 [MAX_BYTES_TO_TEST];
	uint8_t data2 [MAX_BYTES_TO_TEST];

	uint16_t bytes = 0;
	/**
	 * PART 1 - PROOF THAT DMA MEMMOVE/MEMSET FUNCTIONS WORK
	 */

	/**
	 * PART 2 - PROFILER STUFF
	 */
	// initialize profiler variables
	uint16_t startTime = 0;
	uint16_t elapsedTime = 0;

	LOG_ITEM(PROFILE_MEMSET_START, NO_PAYLOAD, NO_PAYLOAD);

	for(uint8_t i = 1; i < 4; i++){
		bytes = numBytesToTest[i];

		LOG_ITEM(PROFILE_NUM_BYTES, &bytes, sizeof(bytes));

		startTime = COUNTER_GET_COUNT();
		memset((void *)&data1, 0xAA, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_STD, &elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		my_memset((uint8_t *)&data2, bytes, 0x55);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_CUSTOM, &elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		//note- this will return -1 if not supported for given platform
		int8_t dmaStatus = memset_dma((uint8_t *)&data1, bytes, 0xFF);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		if (dmaStatus < 0){
			LOG_ITEM(DMA_NO_SUPPORT, NO_PAYLOAD, NO_PAYLOAD);
		} else {
			LOG_ITEM(PROFILE_MEM_DMA, &elapsedTime, sizeof(elapsedTime));
		}
	}

	//don't profile this, just set the memory to alternating values/clear
	memset((void *)&data1, 0xAA, MAX_BYTES_TO_TEST); // all 0xAA
	memset((void *)&data2, 0x00, MAX_BYTES_TO_TEST); // all 0x00

	LOG_ITEM(PROFILE_MEMMOVE_START, NO_PAYLOAD, NO_PAYLOAD);

	for(uint8_t i = 0; i < 4; i++){
		bytes = numBytesToTest[i];

		LOG_ITEM(PROFILE_NUM_BYTES, &bytes, sizeof(bytes));

		startTime = COUNTER_GET_COUNT();
		memmove((uint8_t *)&data1, (uint8_t *)&data2, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_STD, &elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		my_memmove((uint8_t *)&data2, (uint8_t *)&data1, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM(PROFILE_MEM_CUSTOM, &elapsedTime, sizeof(elapsedTime));

		startTime = COUNTER_GET_COUNT();
		//note- this will return -1 if not supported for given platform
		int8_t dmaStatus = memmove_dma((uint8_t *)&data1, (uint8_t *)&data2, bytes, sizeof(uint8_t));
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		if (dmaStatus < 0){
			LOG_ITEM(DMA_NO_SUPPORT, NO_PAYLOAD, NO_PAYLOAD);
		} else {
			LOG_ITEM(PROFILE_MEM_DMA, &elapsedTime, sizeof(elapsedTime));
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
