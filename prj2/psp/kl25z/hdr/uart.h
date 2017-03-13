#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "circBuf.h"

typedef enum {
	UART_OK,
	UART_NULLPTR,
	UART_BUF_ERR,
	UART_NODATA,
	UART_OTHER_ERR
} UART_Status_t;

/************
 * uart_configure()
 * description:
 * 		Configures uart to settings. Dynamic based on intended BAUD rate (calculated based on clock frequencies)
 * inputs:
 * 		Intended BAUD rate
 * outputs:
 * 		UART_Status_t status - returns with OK for successful or error code indicating type of error
 */
UART_Status_t uart_configure(uint64_t baudRate);

/************
 * uart_send_byte()
 * description:
 * 		Sends one byte. Blocks until transmission complete
 * inputs:
 * 		uint8_t byte - byte of data to send
 * outputs:
 * 		UART_Status_t status - returns with OK for successful or error code indicating type of error
 */
UART_Status_t uart_send_byte(uint8_t byte);

/************
 * uart_send_byte_n()
 * description:
 * 		Sends a sequence of bytes. Blocks until sequence complete. Takes a
 *		pointer to a byte sequence and length of n bytes to send
 * inputs:
 * 		uint8_t * bytes - pointer to byte sequence to send
 * 		uint8_t n - number of bytes to send
 * outputs:
 * 		UART_Status_t status - returns with OK for successful or error code indicating type of error
 */
UART_Status_t uart_send_byte_n(uint8_t * bytes, uint8_t n);

/************
 * uart_receive_byte()
 * description:
 * 		Receives one byte. Blocks until transmission complete
 * inputs:
 * 		uint8_t * byte - pointer to hold received data
 * outputs:
 * 		UART_Status_t status - returns with OK for successful or error code indicating type of error
 */
UART_Status_t uart_receive_byte(uint8_t * byte);

#endif /* __UART_H__ */
