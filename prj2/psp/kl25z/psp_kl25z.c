#include "psp_kl25z.h"
#include "psp_macros_log.h"

void sys_init_kl25z(void){
	//buffer declaration
	extern uint32_t __BUFFER_START;
	uint8_t * bufferPtr = (uint8_t *)&__BUFFER_START;

	//Disable watchdog - clear COP COPT bits
	SIM_COPC &= ~SIM_COPC_COPT_MASK;

	//Enable port clock(s)
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	//SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//For hw5
	//PORTA_PCR13 = PORT_PCR_MUX(0x01) | PORT_PCR_IRQC(0b1001);

	//enable pin for GPIO output direction
	//RED LED
	PORTB_PCR18 = PORT_PCR_MUX(0x01);
	GPIOB_PDDR = (1 << 18);

	GPIOB_PSOR = (1 << 18);

	//BLUE LED
	//PORTD_PCR1 = PORT_PCR_MUX(0x01);
	//GPIOD_PDDR = (1 << 1);

	//GPIOD_PSOR = (1 << 1);

	LOG_INIT();

	//insert GPIO initialization here (i.e. input, outputs, etc)

	LOG_ITEM(GPIO_INITIALIZED, NO_PAYLOAD, NO_PAYLOAD);

	LOG_ITEM(SYSTEM_INITIALIZED, NO_PAYLOAD, NO_PAYLOAD);

}
