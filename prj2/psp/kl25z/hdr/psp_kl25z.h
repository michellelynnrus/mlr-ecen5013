#ifndef __PSP_KL25Z_H__
#define __PSP_KL25Z_H__

#include "fsl_device_registers.h"
#include "dma.h"
#include "timer.h"

//DMA is supported on this board
#define DMA_SUPPORTED

void sys_init_kl25z(void);


#endif /* __PSP_KL25Z_H__ */
