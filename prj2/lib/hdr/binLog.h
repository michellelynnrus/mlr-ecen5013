#ifndef __BINLOG_H__
#define __BINLOG_H__

#include <stdint.h>
#define PAYLOAD_LENGTH_MAX (64)
#define NO_PAYLOAD (0)

/*
 * typedef enum LOG_ID_t
 * Log ID codes for the 14 existing types of binary log items
 */
typedef enum {
	LOGGER_INITIALIZED = 0,		 //no payload
	GPIO_INITIALIZED = 1,		 //no payload
	SYSTEM_INITIALIZED = 2,		 //no payload
	SYSTEM_HALTED = 3,			 //no payload
	INFO = 4,					 //important information with regards to an info string
	WARNING = 5,				 //important information with regards to a warning string
	ERROR = 6,					 //important information with regards to an error string
	DATA_RECEIVED = 7,			 //logs that an item was received on UART, transmits back
	DATA_ANALYSIS_STARTED = 8,	 //no payload
	DATA_ALPHA_COUNT = 9,		 //logs number of alphabetic characters
	DATA_NUMERIC_COUNT = 10,	 //logs number of numeric characters
	DATA_PUNCTUATION_COUNT = 11, //logs number of punctuation characters
	DATA_MISC_COUNT = 12,		 //logs number of misc characters
	DATA_ANALYSIS_COMPLETED = 13, //no payload
	PROFILE_MEMMOVE_START = 14,	//no payload
	PROFILE_MEMSET_START = 15,	//no payload
	PROFILE_NUM_BYTES = 16,		//number of bytes to start profiling
	PROFILE_MEM_STD = 17,		//profile time
	PROFILE_MEM_CUSTOM = 18,	//profile time
	PROFILE_MEM_DMA = 19,		//profile time
	DMA_NO_SUPPORT = 20			//no payload
} LOG_ID_t;

/*
 * typedef struct LOG_t
 * Definition of a binary log type
 * Fields:
 * 		LOG_ID_t logID - ID for the log type
 * 		uint8_t * payload - pointer to the payload
 * 		uint32_t payloadSize - size of the payload
 */
typedef struct {
	LOG_ID_t logID;
	uint8_t logIDAscii[16];
	uint8_t * payload;
	uint32_t payloadSize;
	uint16_t data;
	uint8_t dataAscii[16];
} LOG_t;

/*
 * typedef enum binLog_Status_t
 * enum to indicate success or failure of binary log functions
 */
typedef enum {
	BINLOG_OK,
	BINLOG_NULLPTR,
	BINLOG_MALLOC_ERR,
	BINLOG_ERROR
} binLog_Status_t;

/**************
* binLog_CreateItem()
*	description:
*		creates a LOG_t type log item in dynamic memory
*	params:
*		LOG_t ** log - pointer to log pointer
*	returns:
*		binLog_Status_t status - returns OK or NULLPTR
**************/
binLog_Status_t binLog_CreateItem(LOG_t ** log, uint32_t payloadLength);

/**************
* binLog_LogItem()
*	description:
*		Create and send a log item with a given sized payload.
*		NOTE: to send a log item with no payload, the macro NO_PAYLOAD may be used
*		in place of payload and length parameters.
*	params:
*		LOG_ID_t logID - ID of the log item to send
*		uint8_t * payload - pointer to payload. use NO_PAYLOAD if no payload requested
*		uint32_t length - length of payload. use NO_PAYLOAD if no payload requested
*	returns:
*		binLog_Status_t status - returns OK or NULLPTR
**************/
binLog_Status_t binLog_LogItem(LOG_ID_t logID, uint8_t * payload, uint32_t length);

/**************
* binLog_Send()
*	description:
*		Sends the log item using LOG_RAW_DATA macro
*	params:
*		LOG_t * log - pointer to log item to send
*	returns:
*		binLog_Status_t status - returns OK or NULLPTR
**************/
binLog_Status_t binLog_Send(LOG_t * log);

/**************
* binLog_DestroyItem()
*	description:
*		Frees the log item from dynamic memory
*	params:
*		LOG_t * log - circular buffer pointer
*	returns:
*		binLog_Status_t status - returns OK or NULLPTR
**************/
binLog_Status_t binLog_DestroyItem(LOG_t *log);

binLog_Status_t binLog_LogItem_Ascii(LOG_ID_t logID, uint8_t * payload, uint16_t data);

binLog_Status_t binLog_Send_Ascii(LOG_t * log);

#endif /* __BINLOG_H__*/
