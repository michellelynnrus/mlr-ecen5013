### build
BLD_PATH = build

### main
MAIN_SRC_FILES=\
	main.c

### lib
LIB_PATH = lib
LIB_HDR_PATH = lib/hdr
LIB_SRC_FILES=\
	data.c \
	memory.c \
	circBuf.c \
	binLog.c

### prj
PRJ_PATH = prj
PRJ_HDR_PATH = prj/hdr
PRJ_SRC_FILES=\
	project_1.c\
	project_2.c#\
	#project_3.c

### psp
PSP_PATH = psp
PSP_HDR_PATH = psp
#PSP_HDR_FILES=\
#	psp_config.h\
#	psp_macros_log.h\
#	psp_macros_sys.h

### psp - kl25z
PSP_PATH_KL25Z = psp/kl25z
PSP_HDR_PATH_KL25Z = psp/kl25z/hdr
PSP_SRC_FILES_KL25Z=\
	logger.c\
	psp_kl25z.c\
	uart.c


	


