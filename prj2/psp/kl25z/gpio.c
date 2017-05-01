#include "gpio.h"
#include "psp_macros_log.h"
#include <string.h>

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

GPIO_status_t GPIO_poll_nrf(void){
	//Don't do anything until we receive something, will be replaced w/ ISR
	while (!(GPIOA_PDIR & (1<<5)));

	return GPIO_OK;
}

void GPIO_SetLEDEnState(uint8_t ledID, uint8_t enState){
	uint8_t string[64];
	switch (ledID){
		case LED_RED:
			if (enState == 1){
				GPIOB_PCOR |= (1 << 18);
			} else {
				GPIOB_PSOR |= (1 << 18);
			}
			break;
		case LED_GREEN:
			if (enState == 1){
				GPIOB_PCOR |= (1 << 19);
			} else {
				GPIOB_PSOR |= (1 << 19);
			}
			break;
		case LED_BLUE:
			/*if (enState){
				GPIOD_PCOR |= (1 << 1);
			} else {
				GPIOD_PSOR |= (1 << 1);
			}*/
			LOG_ITEM_ASCII(ERROR, "LED SET EN STATE - BLUE LED not supported", NO_PAYLOAD);
			break;
		default:

			sprintf(string, "Invalid LED SET EN STATE, LED ID = %d", ledID);
			LOG_ITEM_ASCII(ERROR, string, NO_PAYLOAD);

			break;
	}
}
