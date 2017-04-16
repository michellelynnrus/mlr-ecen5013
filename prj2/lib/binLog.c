#include "binLog.h"
#include <stdlib.h>
#include "psp_macros_log.h"
#include "memory.h"

binLog_Status_t binLog_CreateItem(LOG_t ** log, uint32_t payloadLength){
	binLog_Status_t status = BINLOG_OK;

	if (!log){
		status = BINLOG_NULLPTR;
	} else {
		//allocate space for log data type
		*log = (LOG_t *) malloc(sizeof(LOG_t));

		if (!log){
			status = BINLOG_MALLOC_ERR;
		} else {
		//allocate space for payload
			(*log)->payload = (uint8_t *) malloc(payloadLength);

			if (!((*log)->payload)){
				status = BINLOG_MALLOC_ERR;
			} else {
				//initialize logID to 0
				(*log)->logID = 0;

				//set payload length
				(*log)->payloadSize = payloadLength;

			}
		}
	}

	return status;
}

binLog_Status_t binLog_LogItem(LOG_ID_t logID, uint8_t * payload, uint32_t length){
	binLog_Status_t status = BINLOG_OK;

	if (length > 0 && !payload){
		status = BINLOG_NULLPTR;
	} else {
		// create log item
		LOG_t * log;
		binLog_CreateItem(&log, length);

		//set log item values, copy payload
		log->logID = logID;
		my_memmove(payload, log->payload, length);

		//send item
		binLog_Send(log);

		//destroy log item
		binLog_DestroyItem(log);
	}

	return status;
}

binLog_Status_t binLog_Send(LOG_t * log){
	binLog_Status_t status = BINLOG_OK;

	if (!log){
		status = BINLOG_NULLPTR;
	} else {
		//use existing LOG_RAW_DATA macro to send log ID + payload
		LOG_RAW_DATA(&(log->logID), sizeof(log->logID));
		LOG_RAW_DATA(log->payload, log->payloadSize);
		LOG_FLUSH();
	}

	return status;
}

binLog_Status_t binLog_DestroyItem(LOG_t *log){
	binLog_Status_t status = BINLOG_OK;

	if (!log){
		status = BINLOG_NULLPTR;
	} else {
		free(log->payload);
		free(log);
	}

	return status;
}
