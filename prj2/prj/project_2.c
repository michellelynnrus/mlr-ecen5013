#include <stdio.h>
#include "project_2.h"

/**************
* project_2_report()
**************/
void project_2_report(void){
	uint8_t byte;

	//Initialize system
	SYS_INIT();

    while (1){
    	//Wait for rx
    	uart_receive_byte(&byte);

    }
	
}
