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
	LOG_ITEM_ASCII(PROFILE_MEMSET_START, "******START PART 1a: proof DMA memset function works", NO_PAYLOAD);
	//use regular memset to set data to something useful
	memset((void *)data1, 0xAA, 8);
	memset((void *)data2, 0xFF, 8);
	LOG_ITEM_ASCII(INFO, "data1 before:", NO_PAYLOAD);
	uint8_t string[10];
	sprintf(string, "0x%x", *((uint64_t*)&data1[0]));
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

	LOG_ITEM_ASCII(INFO, "data2 before:", NO_PAYLOAD);
	sprintf(string, "0x%x", *((uint64_t*)&data2[0]));
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

	int8_t stat = memset_dma((uint8_t *)&data2[0], 8, 0x00);
	LOG_ITEM_ASCII(INFO, "***data2 AFTER dma memset (0x00): stat= ", stat);
	sprintf(string, "0x%x", *((uint64_t*)&data2[0]));
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

	LOG_ITEM_ASCII(PROFILE_MEMSET_START, "******START PART 1b: proof DMA memmove function works", NO_PAYLOAD);
	memmove_dma((uint8_t *)&data1[0], (uint8_t *)&data2[0], 8, 8);
	LOG_ITEM_ASCII(INFO, "***data2 AFTER dma memmove (data1): ", NO_PAYLOAD);
	sprintf(string, "0x%x", *((uint64_t*)&data2[0]));
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

	/**
	 * PART 2 - PROFILER STUFF
	 */
	// initialize profiler variables
	uint16_t startTime = 0;
	uint16_t elapsedTime = 0;

	LOG_ITEM_ASCII(PROFILE_MEMSET_START, "******START PART 2a: profiling memset functions", NO_PAYLOAD);

	for(uint8_t i = 0; i < 4; i++){
		bytes = numBytesToTest[i];

		//LOG_ITEM(PROFILE_NUM_BYTES, &bytes, sizeof(bytes));
		LOG_ITEM_ASCII(PROFILE_NUM_BYTES, "***Number of bytes to profile: ", bytes);

		startTime = COUNTER_GET_COUNT();
		memset((void *)data1, 0xAA, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		//LOG_ITEM(PROFILE_MEM_STD, &elapsedTime, sizeof(elapsedTime));
		LOG_ITEM_ASCII(PROFILE_MEM_STD, "Std memset elapsed time: ", elapsedTime);

		startTime = COUNTER_GET_COUNT();
		my_memset((uint8_t *)data1, bytes, 0x55);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		//LOG_ITEM(PROFILE_MEM_CUSTOM, &elapsedTime, sizeof(elapsedTime));
		LOG_ITEM_ASCII(PROFILE_MEM_CUSTOM, "My memset elapsed time:  ", elapsedTime);

		startTime = COUNTER_GET_COUNT();
		//note- this will return -1 if not supported for given platform
		int8_t dmaStatus = memset_dma((uint8_t *)data1, bytes, 0xFF);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		if (dmaStatus < 0){
			//LOG_ITEM(DMA_NO_SUPPORT, NO_PAYLOAD, NO_PAYLOAD);
			LOG_ITEM_ASCII(DMA_NO_SUPPORT, "DMA not supported" , NO_PAYLOAD);
		} else {
			//LOG_ITEM(PROFILE_MEM_DMA, &elapsedTime, sizeof(elapsedTime));
			LOG_ITEM_ASCII(PROFILE_MEM_DMA, "DMA memset elapsed time: ", elapsedTime);
		}
	}

	//don't profile this, just set the memory to alternating values/clear
	memset((void *)data1, 0xAA, MAX_BYTES_TO_TEST); // all 0xAA
	memset((void *)data2, 0x00, MAX_BYTES_TO_TEST); // all 0x00

	LOG_ITEM_ASCII(PROFILE_MEMMOVE_START, "******START PART 2b: profiling memmove functions", NO_PAYLOAD);

	for(uint8_t i = 0; i < 4; i++){
		bytes = numBytesToTest[i];

		LOG_ITEM_ASCII(PROFILE_NUM_BYTES, "***Number of bytes to profile: ", bytes);

		startTime = COUNTER_GET_COUNT();
		memmove((uint8_t *)data1, (uint8_t *)data2, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM_ASCII(PROFILE_MEM_STD, "Std memmove elapsed time: ", elapsedTime);

		startTime = COUNTER_GET_COUNT();
		my_memmove((uint8_t *)data2, (uint8_t *)data1, bytes);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		LOG_ITEM_ASCII(PROFILE_MEM_CUSTOM, "My memmove elapsed time:  ", elapsedTime);

		startTime = COUNTER_GET_COUNT();
		//note- this will return -1 if not supported for given platform
		int8_t dmaStatus = memmove_dma((uint8_t *)data1, (uint8_t *)data2, bytes, 8);
		elapsedTime = COUNTER_GET_COUNT() - startTime;
		if (dmaStatus < 0){
					//LOG_ITEM(DMA_NO_SUPPORT, NO_PAYLOAD, NO_PAYLOAD);
					LOG_ITEM_ASCII(DMA_NO_SUPPORT, "DMA not supported" , NO_PAYLOAD);
				} else {
					//LOG_ITEM(PROFILE_MEM_DMA, &elapsedTime, sizeof(elapsedTime));
					LOG_ITEM_ASCII(PROFILE_MEM_DMA, "DMA memmove elapsed time: ", elapsedTime);
				}
	}

	LOG_ITEM_ASCII(PROFILE_MEMSET_START, "******START PART 4: proof SPI/ NRF interface works", NO_PAYLOAD);

#if (PLATFORM_CODE == PLATFORM_KL25Z)

	// Don't do this for any other platform

	SPI_init();
	GPIO_nrf_init();
	uint8_t writeReg = 0;
	uint8_t readReg = 0;

	readReg = nrf_read_config();
	LOG_ITEM_ASCII(INFO, "Config reg read:", NO_PAYLOAD);
	sprintf(string, "0x%x", readReg);
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

	writeReg = readReg | 0x10;
	nrf_write_config(writeReg);
	LOG_ITEM_ASCII(INFO, "Writing register val:", NO_PAYLOAD);
	sprintf(string, "0x%x", writeReg);
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

	readReg = nrf_read_config();
	LOG_ITEM_ASCII(INFO, "Reading back config reg:", NO_PAYLOAD);
	sprintf(string, "0x%x", readReg);
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

	readReg = nrf_read_register(NRF_STATUS);
	LOG_ITEM_ASCII(INFO, "Reading back status reg:", NO_PAYLOAD);
	sprintf(string, "0x%x", readReg);
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

#else
	LOG_ITEM_ASCII(PROFILE_MEMSET_START, "***Not supported", NO_PAYLOAD);


#endif




	while (1){
		//do nothing for now
	}
	
}
