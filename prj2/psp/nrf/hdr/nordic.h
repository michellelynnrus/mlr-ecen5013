#ifndef __NORDIC_H__
#define __NORDIC_H__

#include <stdint.h>
#include <nrf24L01p.h>

/**************
* nrf_read_register()
*	description:
*		Read the register and return the value 
*	params:
*		uint8_t register - register to read
*	returns:
*		uint8_t regValue - value of the register that was read
**************/
uint8_t nrf_read_register(uint8_t register); 

/**************
* nrf_write_register()
*	description:
*		Write to the given register with the data.
*	params:
*		uint8_t register - register to write
*		uint8_t value - data to write to the given register
*	returns:
*		
**************/
void nrf_write_register(uint8_t register, uint8_t value); 

/**************
* nrf_read_status()
*	description:
*		Reads the STATUS register 
*	params:
*		
*	returns:
*		uint8_t regValue - value of the STATUS register 
**************/
uint8_t nrf_read_status(void); 

/**************
* nrf_write_config()
*	description:
*		Write to CONFIG register
*	params:
*		uint8_t config - data to write to the CONFIG register
*	returns:
*		
**************/
void nrf_write_config(uint8_t config); 

/**************
* nrf_read_config()
*	description:
*		Read the CONFIG register 
*	params:
*		
*	returns:
*		uint8_t regValue - value of the CONFIG register 
**************/
uint8_t nrf_read_config(void); 


/**************
* nrf_read_rf_setup()
*	description:
*		Reads RF_SETUP register
*	params:
*		
*	returns:
*		uint8_t regValue - value of the RF_SETUP register 
**************/
uint8_t nrf_read_rf_setup(void); 


/**************
* nrf_write_rf_setup()
*	description:
*		Writes to the RF_SETUP register
*	params:
*		uint8_t config - data to write to the RF_SETUP register
*	returns:
*		
**************/
void nrf_write_rf_setup(uint8_t config);


/**************
* nrf_write_rf_ch()
*	description:
*		Writes to the RF_CH register
*	params:
*		uint8_t config - data to write to the RF_CH register
*	returns:
*		
**************/
void nrf_write_rf_ch(uint8_t channel);


/**************
* nrf_read_TX_ADDR()
*	description:
*		Reads the 8 bytes of the TX_ADDR register
*	params:
*		
*	returns:
*		uint8_t * txAddrPtr - pointer to the start of the TX_ADDR value read 
**************/
uint8_t * nrf_read_TX_ADDR(void);


/**************
* nrf_write_TX_ADDR()
*	description:
*		Writes the 8 byte TX_ADDR register
*	params:
*		uint8_t * txAddrPtr - pointer to the start of the TX_ADDR to write
*	returns:
*		
**************/
void nrf_write_TX_ADDR(uint8_t * tx_addr); 


/**************
* nrf_read_fifo_status()
*	description:
*		Reads FIFO_STATUS register
*	params:
*		
*	returns:
*		uint8_t regValue - value of the FIFO_STATUS register 
**************/
uint8_t nrf_read_fifo_status(void);


/**************
* nrf_flush_tx_fifo()
*	description:
*		Sends the command FLUSH_TX
*	params:
*		
*	returns:
*		
**************/
void nrf_flush_tx_fifo(void);


/**************
* nrf_flush_rx_fifo()
*	description:
*		Sends the command FLUSH_RX
*	params:
*		
*	returns:
*		 
**************/
void nrf_flush_rx_fifo();



#endif /*__NORDIC_H__*/
