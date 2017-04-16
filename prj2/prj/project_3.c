#include <stdio.h>
#include "project_3.h"
#include "memory.h"
/**************
* project_3_report()
**************/
void project_3_report(void){

#if PLATFORM_CODE == PLATFORM_KL25Z
	uint32_t srcData [2] = {0x01234567, 0x76543210};
	uint32_t dstData [2] = {0xFFFFFFFF, 0xFFFFFFFF};

	uint16_t startTime = 0;
	uint16_t endTime = 0;



#endif
	//Initialize system
	SYS_INIT();
	COUNTER_INIT();



#if PLATFORM_CODE == PLATFORM_KL25Z
	//setup stuff to test interrupt latency
	__enable_irq();
	NVIC_EnableIRQ(PORTA_IRQn);


    //while (1){


    //don't do this for any other platform (they don't have equivalent RX functions)
	//GPIOB_PTOR = (1 << 18);
	LOG_ITEM(DATA_ANALYSIS_COMPLETED, (uint8_t *)&dstData, sizeof(uint32_t)*2);

	startTime = COUNTER_GET_COUNT();
	GPIOD_PSOR = (1 << 1);
	//SysTick_Config(0);
	//startTime = SysTick->VAL;
	//memset_dma((uint8_t *)&dstData, 6, 0xAA);
	//NVIC_SetPendingIRQ(PORTA_IRQn);
	//endTime = COUNTER_GET_COUNT();

	LOG_ITEM(DATA_ALPHA_COUNT, (uint8_t *)&startTime, sizeof(uint16_t));
	//LOG_ITEM(DATA_NUMERIC_COUNT, (uint8_t *)&endTime, sizeof(uint16_t));

	//LOG_ITEM(DATA_ANALYSIS_COMPLETED, (uint8_t *)&dstData, sizeof(uint32_t)*2);

#endif

   // }
	
}

#if PLATFORM_CODE == PLATFORM_KL25Z
extern void PORTA_IRQHandler(){
	uint32_t intEndTime = COUNTER_GET_COUNT();
	LOG_ITEM(DATA_NUMERIC_COUNT, (uint8_t *)&intEndTime, sizeof(uint32_t));
	PORTA_PCR13 |= PORT_PCR_ISF_MASK;
}
#endif
