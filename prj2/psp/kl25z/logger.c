#include "logger.h"
#include "data.h"
#include "psp_macros_log.h"

#define BAUD (9600)
#define BASE_10 (10)

void log_init(void){

	//Allocate circular buffers
	CB_Status_t txBufStatus = CB_Allocate(&p_log_TXbuf, LOG_BUF_SIZE);
	CB_Status_t rxBufStatus = CB_Allocate(&p_log_RXbuf, LOG_BUF_SIZE);

	if (txBufStatus != CB_OK || rxBufStatus != CB_OK){
		//there has been an error
		//you should probably handle this, Michelle from the future
	}

	//initialize/configure uart
	uart_configure(BAUD);

	LOG_ITEM(LOGGER_INITIALIZED, NO_PAYLOAD, NO_PAYLOAD);

}

void log_data(uint8_t * data, uint8_t length){
	for (uint8_t i = 0; i < length; i++){
		CB_AddItem(p_log_TXbuf, *(data+i));
	}
}

void log_string(uint8_t * string){
	uint8_t i = 0;
	//loop until end string end character
	while(*(string+i) != '\0'){
		CB_AddItem(p_log_TXbuf, *(string+i));
		i++;
	}
}

void log_integer(uint8_t integer){
	int8_t ascii;
	my_itoa(&ascii, (int32_t)integer, BASE_10);
	log_string((uint8_t *)&ascii);
}

void log_flush(void){

//#ifndef UART_INT
	while (CB_Empty(p_log_TXbuf) != CB_EMPTY){
		// if we are using polling implementation, need to send the data out now
		// otherwise the interrupt should be doing that for us?
		uint8_t item;
		CB_RemoveItem(p_log_TXbuf, &item);
		uart_send_byte(item);
	}
//#endif
		// otherwise the interrupt should be doing that for us so just wait


}
