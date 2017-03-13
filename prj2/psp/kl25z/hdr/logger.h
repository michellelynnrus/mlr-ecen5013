#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "circBuf.h"
#include "uart.h"

#define LOG_BUF_SIZE (128)

//Pointers to TX/RX circular buffers
CB_t * p_log_TXbuf;
CB_t * p_log_RXbuf;

/*
 * log_init()
 * description: initializes logging (allocates buffers)
 * inputs:
 * returns:
 * 		status probably
 */
void log_init(void);

/*
 * log_data()
 * description: logs a sequence of bytes to the terminal
 * inputs:
 * 		uint8_t * data - pointer to sequence of bytes
 * 		uint8_t length - length of bytes to log
 * returns:
 * 		status probably
 */
void log_data(uint8_t * data, uint8_t length);

/*
 * log_string()
 * description: logs a c-string to the terminal
 * inputs:
 * 		uint8_t * string - pointer to c-string
 * returns:
 * 		status probably
 */
void log_string(uint8_t * string);

/*
 * log_integer()
 * description: logs an integer to the terminal (uses itoa)
 * inputs:
 * 		uint8_t integer - integer to log
 * returns:
 * 		status probably
 */
void log_integer(uint8_t integer);

/*
 * log_flush()
 * description: blocks until the current logger buffer is empty
 * inputs:
 * returns:
 * 		status probably
 */
void log_flush(void);

#endif /* __LOGGER_H__ */
