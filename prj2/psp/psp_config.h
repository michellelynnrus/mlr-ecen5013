#ifndef __PSP_CONFIG_H__
#define __PSP_CONFIG_H__

#define PLATFORM_LINUX (0)
#define PLATFORM_BBB (1)
#define PLATFORM_KL25Z (2)

#ifndef PLATFORM_CODE
//#define PLATFORM_CODE PLATFORM_LINUX
//#define PLATFORM_CODE PLATFORM_BBB
#define PLATFORM_CODE PLATFORM_KL25Z
#endif

#ifndef DEBUG_MODE
#define DEBUG_MODE
//#undef DEBUG_MODE
#endif

#ifndef UART_INT
//#define UART_INT
#undef UART_INT
#endif

#ifndef CMD_NORDIC
//#define CMD_NORDIC
#undef CMD_NORDIC
#endif

#if PLATFORM_CODE == PLATFORM_KL25Z
#include "psp_kl25z.h"
#endif

#endif /* __PSP_CONFIG_H__ */
