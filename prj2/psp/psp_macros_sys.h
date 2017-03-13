#ifndef __PSP_MACROS_SYS_H__
#define __PSP_MACROS_SYS_H__

#include "psp_config.h"


#if (PLATFORM_CODE==PLATFORM_KL25Z)

#include "psp_kl25z.h"

#define SYS_INIT() sys_init_kl25z()

#else

#define SYS_INIT()

#endif

#endif /* __PSP_MACROS_SYS_H__ */
