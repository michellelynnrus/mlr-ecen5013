#include <stdio.h>
#include "project_3.h"
#include "memory.h"
/**************
* project_3_report()
**************/
void project_3_report(void){

	uint32_t srcData [2] = {0x01234567, 0x76543210};
	uint32_t dstData [2] = {0xFFFFFFFF, 0xFFFFFFFF};

	uint16_t startTime = 0;
	uint16_t endTime = 0;

	//Initialize system
	SYS_INIT();
	COUNTER_INIT();




	/*
    //leftover LED code for kl25z (hw5)
	GPIOB_PTOR = (1 << 18);
	GPIOD_PSOR = (1 << 1);
	*/

	LOG_ITEM(DATA_ANALYSIS_COMPLETED, (uint8_t *)&dstData, sizeof(uint32_t)*2);

	startTime = COUNTER_GET_COUNT();
	//note- this will return -1 if not supported for given platform
	int8_t dmaStatus = memset_dma((uint8_t *)&dstData, 6, 0xAA);
	endTime = COUNTER_GET_COUNT();

	LOG_ITEM(DATA_ALPHA_COUNT, (uint8_t *)&startTime, sizeof(uint16_t));

	while (1){
		//do nothing for now
	}
	
}
