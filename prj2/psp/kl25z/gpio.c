#include "gpio.h"

/**************
* GPIO_nrf_init()
**************/
GPIO_status_t GPIO_nrf_init(void){

	//initialize the GPIO pins associated with the nrf and spi devices
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Initialize GPIO pin for CS output
	PORTD_PCR5 = PORT_PCR_MUX(0x01);
	GPIOD_PDDR |= (1 << 5);
	GPIOD_PSOR |= (1 << 5); //always enable

	//Initialize GPIO pin for IRQ input
	PORTA_PCR13 = PORT_PCR_MUX(0x01);
	GPIOA_PDDR &= ~(1 << 5);

	return GPIO_OK;
}

GPIO_status_t GPIO_poll_nrf(){
	//Don't do anything until we receive something, will be replaced w/ ISR
	while (!(GPIOA_PDIR & (1<<5)));

	return GPIO_OK;
}
