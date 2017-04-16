#include "nordic.h"

/**************
* nrf_read_register()
**************/
uint8_t nrf_read_register(uint8_t register){

	return 1;
}

/**************
* nrf_write_register()
**************/
void nrf_write_register(uint8_t register, uint8_t value){

}

/**************
* nrf_read_status()
**************/
uint8_t nrf_read_status(void){

	return 1;
}

/**************
* nrf_write_config()
**************/
void nrf_write_config(uint8_t config){

}

/**************
* nrf_read_config()
**************/
uint8_t nrf_read_config(void){

	return 1;
}


/**************
* nrf_read_rf_setup()
**************/
uint8_t nrf_read_rf_setup(void){

	return 1;
}


/**************
* nrf_write_rf_setup()
*	returns:
*
**************/
void nrf_write_rf_setup(uint8_t config){

}


/**************
* nrf_write_rf_ch()
**************/
void nrf_write_rf_ch(uint8_t channel){

}


/**************
* nrf_read_TX_ADDR()
**************/
uint8_t * nrf_read_TX_ADDR(void){

	return 1;
}


/**************
* nrf_write_TX_ADDR()
**************/
void nrf_write_TX_ADDR(uint8_t * tx_addr){

}


/**************
* nrf_read_fifo_status()
**************/
uint8_t nrf_read_fifo_status(void){

	return 1;
}


/**************
* nrf_flush_tx_fifo()
**************/
void nrf_flush_tx_fifo(void){

}


/**************
* nrf_flush_rx_fifo()
**************/
void nrf_flush_rx_fifo(){

}
