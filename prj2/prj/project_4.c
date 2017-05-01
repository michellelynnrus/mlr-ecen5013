#include <stdio.h>
#include "project_4.h"

#include "cmdif.h"

#include "uart.h"
#include <string.h>

/**************
* project_4_report()
**************/
void project_4_report(void){

	//Initialize system
	SYS_INIT();
	COUNTER_INIT();
	pwm_init();
	PSP_CMDIF_INIT();

	LOG_ITEM_ASCII(INFO, "******stuff is happening", NO_PAYLOAD);
	
	uint8_t byteVal = 0xaa;
	uint8_t * byteIn;
	byteIn = &byteVal;
	
	uint8_t string[64];

	//sprintf(string, "Byte rcv, cmdID = 0x%x", *byteIn);
	//LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

    while (1){
	
		//wait for commands (blocking for now) 
    	cmdIf_Receive();


    }
	
}
