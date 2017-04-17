#include "nordic.h"

/**************
* nrf_read_register()
**************/
uint8_t nrf_read_register(uint8_t reg){
	uint8_t nrfStat = 0; //may be unused
	uint8_t regData = 0;

	// Drop CSn
	SPI_set_CSn(0);

	// Read command via SPI
	SPI_write_byte(reg | NRF_CMD_R_REG);

	// Read nrf status via SPI
	SPI_read_byte((uint8_t *)&nrfStat);

	// Write NOOP to receive read data
	SPI_write_byte(NRF_CMD_NOP);

	// Read receive data
	SPI_read_byte((uint8_t *)&regData);

	// Bring CSn back up
	SPI_set_CSn(1);

	return regData;
}

/**************
* nrf_write_register()
**************/
void nrf_write_register(uint8_t reg, uint8_t value){
	uint8_t nrfStat = 0; //may be unused
	uint8_t regData = 0;

	// Drop CSn
	SPI_set_CSn(0);

	// Write command via SPI
	SPI_write_byte(reg | NRF_CMD_W_REG);

	// Read nrf status via SPI
	SPI_read_byte((uint8_t *)&nrfStat);

	// Write data for register
	SPI_write_byte(value);

	// Bring CSn back up
	SPI_set_CSn(1);

}

/**************
* nrf_read_status()
**************/
uint8_t nrf_read_status(void){
	uint8_t regData = 0;

	// Drop CSn
	SPI_set_CSn(0);

	// Write NOOP to receive read data
	SPI_write_byte(NRF_CMD_NOP);

	// Read receive data
	SPI_read_byte((uint8_t *)&regData);

	// Bring CSn back up
	SPI_set_CSn(1);

	return regData;
}

/**************
* nrf_write_config()
**************/
void nrf_write_config(uint8_t config){
	//write to CONFIG register
	nrf_write_register(NRF_CONFIG, config);
}

/**************
* nrf_read_config()
**************/
uint8_t nrf_read_config(void){
	//read from CONFIG register
	return nrf_read_register(NRF_CONFIG);
}


/**************
* nrf_read_rf_setup()
**************/
uint8_t nrf_read_rf_setup(void){
	//read from NRF_RF_SETUP register
	return nrf_read_register(NRF_RF_SETUP);
}


/**************
* nrf_write_rf_setup()
*	returns:
*
**************/
void nrf_write_rf_setup(uint8_t config){
	//write to NRF_RF_SETUP register
	nrf_write_register(NRF_RF_SETUP, config);
}


/**************
* nrf_read_rf_ch()
**************/
uint8_t nrf_read_rf_ch(void){
	//read from NRF_RF_CH register
	return nrf_read_register(NRF_RF_CH);
}

/**************
* nrf_write_rf_ch()
**************/
void nrf_write_rf_ch(uint8_t channel){
	//write to NRF_RF_CH register
	nrf_write_register(NRF_RF_CH, channel);
}


/**************
* nrf_read_TX_ADDR()
**************/
uint8_t * nrf_read_TX_ADDR(void){
	//read from NRF_RF_CH register
	uint8_t txVal = nrf_read_register(NRF_TX_ADDR);
	return (uint8_t *) &txVal;
}


/**************
* nrf_write_TX_ADDR()
**************/
void nrf_write_TX_ADDR(uint8_t * tx_addr){
	nrf_write_register(NRF_TX_ADDR, *tx_addr);
}


/**************
* nrf_read_fifo_status()
**************/
uint8_t nrf_read_fifo_status(void){
	//read from NRF_FIFO_STATUS register
	return nrf_read_register(NRF_FIFO_STATUS);
}


/**************
* nrf_flush_tx_fifo()
**************/
void nrf_flush_tx_fifo(void){
	uint8_t nrfStat = 0;

	// Drop CSn
	SPI_set_CSn(0);

	// Write NOOP to receive read data
	SPI_write_byte(NRF_CMD_FLUSH_TX);

	// Read receive data
	SPI_read_byte((uint8_t *)&nrfStat);

	// Bring CSn back up
	SPI_set_CSn(1);

}


/**************
* nrf_flush_rx_fifo()
**************/
void nrf_flush_rx_fifo(){
	uint8_t nrfStat = 0;

	// Drop CSn
	SPI_set_CSn(0);

	// Write NOOP to receive read data
	SPI_write_byte(NRF_CMD_FLUSH_RX);

	// Read receive data
	SPI_read_byte((uint8_t *)&nrfStat);

	// Bring CSn back up
	SPI_set_CSn(1);
}
