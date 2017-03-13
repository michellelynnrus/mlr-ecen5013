#include "psp_kl25z.h"
#include "psp_macros_log.h"

void sys_init_kl25z(void){
	//Disable watchdog - clear COP COPT bits
	SIM_COPC &= ~SIM_COPC_COPT_MASK;

	//Enable port clock(s)
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	//SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	//SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	LOG_INIT();

	//insert GPIO initialization here (i.e. input, outputs, etc)

	LOG_ITEM(GPIO_INITIALIZED, NO_PAYLOAD, NO_PAYLOAD);

	LOG_ITEM(SYSTEM_INITIALIZED, NO_PAYLOAD, NO_PAYLOAD);

}
