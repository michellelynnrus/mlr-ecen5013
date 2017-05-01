#ifndef __PSP_MACROS_CMD_H__
#define __PSP_MACROS_CMD_H__

#include "psp_config.h"

#ifdef CMD_NORDIC

#include "nordic.c"

//todo: add nordic functions here
#define PSP_CMDIF_INIT()
#define PSP_CMDIF_RECEIVE(byte)
#define PSP_CMDIF_SEND(cmdID, size, payload)
#define PSP_CMDIF_FLUSH()

#else /* undef CMD_NORDIC */

#if (PLATFORM_CODE==PLATFORM_KL25Z)

#include "psp_macros_log.h" //use logger for outputs since it's already written for uart
#include "uart.h"

#define PSP_CMDIF_INIT()			// sys_init() should include uart_configure()/LOG_INIT()
#define PSP_CMDIF_RECEIVE(byte) 				uart_receive_byte(byte) //
#define PSP_CMDIF_SEND(cmdID, size, payload)	LOG_RAW_DATA(cmdID, size, payload)
#define PSP_CMDIF_FLUSH()						LOG_FLUSH()

#else /* #if (PLATFORM_CODE!=PLATFORM_KL25Z) */

//definitions not valid for other platforms w/o nordic
#define PSP_CMDIF_INIT()
#define PSP_CMDIF_RECEIVE(byte)
#define PSP_CMDIF_SEND(cmdID, size, payload)
#define PSP_CMDIF_FLUSH()

#endif /* #if (PLATFORM_CODE==PLATFORM_KL25Z) */

#endif /* #ifdef NORDIC_CMDS */
	

#endif /* __PSP_MACROS_CMD_H__ */
