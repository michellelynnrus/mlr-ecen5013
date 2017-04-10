#include <stdio.h>
#include "project_2.h"

/**************
* project_2_report()
**************/
void project_2_report(void){

#if PLATFORM_CODE == PLATFORM_KL25Z
	uint8_t byte;
	uint8_t i;
	UART_Status_t status;
	uint8_t numAlpha = 0;
	uint8_t numNumeric = 0;
	uint8_t numPunct = 0;
	uint8_t numMisc = 0;
#endif
	//Initialize system
	SYS_INIT();

    while (1){

#if PLATFORM_CODE == PLATFORM_KL25Z
    	//don't do this for any other platform (they don't have equivalent RX functions)

    	//Wait for rx
    	status = uart_receive_byte(&byte);

    	if (byte == 0x6E){
    		GPIOD_PDOR = 0x02;
    	} else if (byte == 0x66){
    		GPIOD_PDOR = 0x00;
    	}

    	if (status == UART_OK){
    		if ((byte >= 65 && byte <= 90) || (byte >= 97 && byte <= 122)){
    			//A-Z or a-z
    			numAlpha++;
    		} else if (byte >= 48 && byte <= 57){
    			//0-9
    			numNumeric++;
    		} else if ((byte >= 33 && byte <= 47) || (byte >= 58 && byte <= 64)|| (byte >= 91 && byte <= 96)) {
    			//punctuation (I think these are all considered punctuation)
    			// does not include a space because idk if that is considered punctuation
    			numPunct++;
    		} else {
    			//everything else
    			numMisc++;
    		}

    		i++;
    	}

    	if (i >= 16){
    		LOG_ITEM(DATA_ALPHA_COUNT, &numAlpha, sizeof(uint8_t));
    		LOG_ITEM(DATA_NUMERIC_COUNT, &numAlpha, sizeof(uint8_t));
    		LOG_ITEM(DATA_PUNCTUATION_COUNT, &numAlpha, sizeof(uint8_t));
    		LOG_ITEM(DATA_MISC_COUNT, &numAlpha, sizeof(uint8_t));

			numAlpha = 0;
			numNumeric = 0;
			numPunct = 0;
			numMisc = 0;

			i = 0;
    	}


#endif

    }
	
}
