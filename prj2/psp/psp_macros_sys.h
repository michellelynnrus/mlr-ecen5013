#ifndef __PSP_MACROS_SYS_H__
#define __PSP_MACROS_SYS_H__

#include "psp_config.h"


#if (PLATFORM_CODE==PLATFORM_KL25Z)

//#include "psp_kl25z.h"

#define SYS_INIT() 							sys_init_kl25z()

#define DMA_MOVE(src, dst, length, size) 	dma0_move(src, dst, length, size)

#define COUNTER_INIT()						upCounter_init()
#define COUNTER_GET_COUNT()					upCounter_getCount()

#else

#define SYS_INIT()
#define DMA_MOVE(src, dst, length, size)

#define COUNTER_INIT()
#define COUNTER_GET_COUNT()
#endif

#endif /* __PSP_MACROS_SYS_H__ */
