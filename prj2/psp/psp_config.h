#ifndef __PSP_CONFIG_H__
#define __PSP_CONFIG_H__

#define PLATFORM_LINUX (0)
#define PLATFORM_BBB (1)
#define PLATFORM_KL25Z (2)

//#define PLATFORM_CODE PLATFORM_LINUX
//#define PLATFORM_CODE PLATFORM_BBB
#define PLATFORM_CODE PLATFORM_KL25Z

#define DEBUG_MODE
//#undef DEBUG_MODE

#define UART_INT
//#undef UART_INT

#endif /* __PSP_CONFIG_H__ */
