#include "spi.h"

/**************
* SPI_init()
**************/
SPI_status_t SPI_init(void){
	//Configure clocks - PORTB & SPI0 clock gate enable
	//SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	//switch to these for use with logic analyzer
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	//Configure port pins PTD 0-13 for ALT2
	PORTD_PCR0 = PORT_PCR_MUX(0x01); //SPI0_PCS0, J2 06
	PORTD_PCR1 = PORT_PCR_MUX(0x02); //SPI0_SCK, J2 12
	PORTD_PCR2 = PORT_PCR_MUX(0x02); //SPI0_MOSI/bidir MOMI, J2 08
	PORTD_PCR3 = PORT_PCR_MUX(0x02); //SPI0_MISO/bidir unused, J2 10


	//Configure SPI peripheral

	//Enable SPI, master, SS output enable, no interrupts
	//SPI0_C1 |= (SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK);
	SPI0_C1 = (SPI_C1_MSTR_MASK);

	//Changed back to MISO/MOSI mode, manual SS control
	//Bidirectional mode, Mode-fault disabled, no interrupts
	//SPI0_C2 |= (SPI_C2_SPC0_MASK | SPI_C2_MODFEN_MASK);
	//SPI0_C2 |= (SPI_C2_MODFEN_MASK);

	//Set baud rate control - total divisor should be 8? exp 2.6Mhz? math is hard
	SPI0_BR = (SPI_BR_SPPR(0) | SPI_BR_SPR(0));

	SPI0_C2 |= SPI_C2_BIDIROE_MASK;
	//Enable SPI
	SPI0_C1 |= SPI_C1_SPE_MASK;

	// enable manual control of CSn
	GPIOD_PDDR |= (1 << 0);
	GPIOD_PSOR |= (1 << 0);

	return SPI_OK;
}


/**************
* SPI_read_byte()
**************/
SPI_status_t SPI_read_byte(uint8_t * byte){
	//clear MOSI/MOMI pin, set as input
	//SPI0_C2 &= ~(SPI_C2_BIDIROE_MASK);

	//while(!(SPI0_S & SPI_S_SPRF_MASK));

	*byte = SPI0_D;

	return SPI_OK;
}

/**************
* SPI_write_byte()
**************/
SPI_status_t SPI_write_byte(uint8_t byte){

	// Poll until SPI tx buf empty flag is not set
	SPI_flush();

	//set MOSI/MOMI pin to output
	//SPI0_C2 |= SPI_C2_BIDIROE_MASK;

	// Write byte to SPI data register
	SPI0_D = byte;



	//SPI_flush();

	//clear MOSI/MOMI pin, set as input
	//SPI0_C2 &= ~(SPI_C2_BIDIROE_MASK);
	return SPI_OK;
}

/**************
* SPI_send_packet()
**************/
SPI_status_t SPI_send_packet(uint8_t * pData, size_t length){
	// Loop through each byte of data and send over SPI
	for (size_t i = 0; i < length; i++){
		SPI_write_byte(*(pData + i));
	}
	return SPI_OK;
}

/**************
* SPI_flush()
**************/
SPI_status_t SPI_flush(void){
	// Poll until SPI tx buf empty flag is not set
	while(!(SPI0_S & SPI_S_SPTEF_MASK));

	return SPI_OK;
}

SPI_status_t SPI_set_CSn(uint8_t val){
	//PORTD_PCR0 = CSn
	if (val == 0){
		GPIOD_PCOR |= (1 << 0);
	} if (val == 1){
		GPIOD_PSOR |= (1 << 0);
	} else {
		return SPI_ERROR;
	}
	return SPI_OK;
}
