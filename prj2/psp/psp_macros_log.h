#ifndef __PSP_MACROS_LOG_H__
#define __PSP_MACROS_LOG_H__

#include "psp_config.h"

#ifdef DEBUG_MODE

#include "binLog.h"

#if (PLATFORM_CODE==PLATFORM_KL25Z)

#include "logger.h"
#include "uart.h"

// LOGGING FUNCTIONS FOR KL25Z IN DEBUG MODE
#define LOG_INIT()							log_init()
#define LOG_RAW_DATA(data, length) 			log_data(data, length)
#define LOG_RAW_STRING(string) 				log_string(string)
#define LOG_RAW_INT(integer)				log_integer(integer)
#define LOG_FLUSH()							log_flush()
#define LOG_ITEM(logID, payload, length)	binLog_LogItem(logID, payload, length)
#define LOG_ITEM_ASCII(logID, payload, data)	binLog_LogItem_Ascii(logID, payload, data)
//#define LOG_ITEM_ASCII(logID, payload)	binLog_LogItem_Ascii(logID, payload)

#else

#include <stdio.h>

// LOGGING FUNCTIONS FOR LINUX AND BBB IN DEBUG MODE
#define LOG_INIT()
#define LOG_RAW_DATA(data, length) 	printf("%s", (char*)data)
#define LOG_RAW_STRING(string) 		printf(string)
#define LOG_RAW_INT(integer)		printf("%d", i)
#define LOG_FLUSH()
#define LOG_ITEM(logID, payload, length)	binLog_LogItem(logID, payload, length)
#define LOG_ITEM_ASCII(logID, payload, data) binLog_LogItem_Ascii(logID, payload, data)

#endif

#else

// LOGGING FUNCTIONS SHOULDN'T DO ANYTHING IN NON-DEBUG MODE
#define LOG_INIT()
#define LOG_RAW_DATA(data, length)
#define LOG_RAW_STRING(string)
#define LOG_RAW_INT(integer)
#define LOG_FLUSH()
#define LOG_ITEM()
#define LOG_ITEM_ASCII(logID, payload, data)

#endif


#endif /* __PSP_MACROS_LOG_H__ */
