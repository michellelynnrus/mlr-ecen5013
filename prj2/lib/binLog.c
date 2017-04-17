#include "binLog.h"
#include <stdlib.h>
#include <string.h>
#include "psp_macros_log.h"
#include "memory.h"
#include "data.h"

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

binLog_Status_t binLog_LogItem_Ascii(LOG_ID_t logID, uint8_t * payload){//, uint16_t data){
	binLog_Status_t status = BINLOG_OK;
	//uint8_t string[128];
	//sprintf(string, "%s %d", payload, data);
	uint32_t length = strlen(payload);
	if (length > 0 && !payload){
		status = BINLOG_NULLPTR;
	} else {
		// create log item
		LOG_t * log;
		binLog_CreateItem(&log, length);

		//set log item values, copy payload
		my_itoa(&log->logID, (int32_t)logID, 10);
		my_memmove(payload, log->payload, length);
		//log->data = data;

		//send item
		binLog_Send_Ascii(log);

		//destroy log item
		binLog_DestroyItem(log);
	}

	return status;
}

binLog_Status_t binLog_Send_Ascii(LOG_t * log){
	binLog_Status_t status = BINLOG_OK;
	uint8_t strArr[64];
	uint8_t * str = strArr;
	if (!log){
		status = BINLOG_NULLPTR;
	} else {
		//use existing LOG_RAW_DATA macro to send log ID + payload
		str = "LOGID: ";
		LOG_RAW_DATA(str, 7);
		LOG_RAW_DATA(&(log->logID), sizeof(log->logID));
		if (log->payloadSize > 0){
			//str = " - ";
			//LOG_RAW_DATA(str, strlen(str));
			//LOG_RAW_DATA(log->payload, log->payloadSize);
		}

		//if (log->data != NO_PAYLOAD){
		//	LOG_RAW_DATA(&(log->data), sizeof(log->data));
		//}
		//str = "\n";
		//LOG_RAW_DATA(str, strlen(str));
		//LOG_RAW_DATA(0xA, sizeof(uint8_t));
		LOG_FLUSH();
	}

	return status;
}
