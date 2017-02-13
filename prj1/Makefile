# Filename: Makefile
# Includes: sources.mk
# Description: makefile to compile and build ECEN5013 project 1
# Targets: 
#	- build: builds and links whole project. generates individual .o files, project1 output file, and .map file
#	- compile-all: builds all files but does not link. generates individual .o files
#	- clean: removes all .o, .i, .asm, .map files and project1 output file
#	- *.o: generates individual object file
#	- *.i: generates individual preprocessed output file
#	- *.asm: generates individual assembly file
#	- *.dep: generates individual dependency file
# Platforms: 
#	- Linux VM host machine native compile (default unless bbb architecture detected)
#	- Linux VM host machine cross compile for Beaglebone Black
#	- Linux VM host machine cross compile for FRDM-KL25Z
#	- Beaglebone Black native compile (default IF bbb architecture is detected)
# Parameters: all parameters are optional, defaults are noted below
#	- PROJECT: specifies what project is running and defines compile time switch in main.c and output filename
#		- default = 1
#	- PLATFORM: specifies what platform to compile for. defines compile time switch for whether to disable printf
#		- default = host, automatically changed to bbb if shell arch command returns bbb architecture
#	- DEBUG: enables -g flag if set to true
#		- default = false
#	- WALL: enables -Wall flag if set to true
#		- default = false
#	- WERROR: enables -Werror flag if set to true
#		- default = false
#	- OPT0: enables -O0 flag if set to true
#		- default = false
#	- CSTD: defines the c standard
#		- default = c99

include sources.mk

#variables can be changed when calling make
PROJECT = 1
PLATFORM = host
DEBUG = false
WALL = false
WERROR = false
OPT0 = false

#default for all platforms
CSTD=c99

#variables to use as #defines for compile time switching
TARGET=project$(PROJECT)
PLATFORM_CODE=0

#default values for Linux VM host platform
CPU = native
PLATFORM_FLAGS= -march=$(CPU)
CC=gcc
SIZE=size

#default for other platforms
SPECS = nosys.specs

#determine if native compiling on bbb (if so, default platform to BBB rather than VM host)
ARCH = $(shell arch)
ifeq ($(ARCH),armv7l)
	PLATFORM=bbb
endif

#default platform is host, change CPU and CC if specified otherwise
ifeq ($(PLATFORM),frdm)
	CPU=cortex-m0plus
	CC=arm-none-eabi-gcc
	PLATFORM_FLAGS=-mcpu=$(CPU) --specs=$(SPECS) -mthumb
	PLATFORM_CODE=2
	SIZE=arm-none-eabi-size
endif

ifeq ($(PLATFORM),bbb)
	CPU=cortex-a8
	CC=arm-linux-gnueabihf-gcc
	PLATFORM_FLAGS=-mcpu=$(CPU) -mthumb
	PLATFORM_CODE=1
	SIZE=arm-linux-gnueabihf-size
endif
				
#define flags
CFLAGS= $(PLATFORM_FLAGS) -std=$(CSTD) -D PROJECT=$(PROJECT) -D PLATFORM_CODE=$(PLATFORM_CODE)

#add additional flags if requested
ifeq ($(DEBUG),true)
	CFLAGS += -g
endif

ifeq ($(WALL),true)
	CFLAGS += -Wall
endif

ifeq ($(WERROR),true)
	CFLAGS += -Werror
endif

ifeq ($(OPT0),true)
	CFLAGS += -O0
endif

LDFLAGS= -Wl,-Map=$(TARGET).map

#generate object, preprocessed output, assembly, and dependency file lists from sources
OBJS:=$(SRCS:.c=.o)
PRES:=$(SRCS:.c=.i)
ASMS:=$(SRCS:.c=.asm)
DEPS:=$(SRCS:.c=.dep)

#targets
%.o: %.c
	$(CC) -c $^ -o $@ $(CFLAGS)
	
%.i: %.c
	$(CC) -E $^ -o $@ $(CFLAGS)
	
%.asm: %.c
	$(CC) -S $^ -o $@ $(CFLAGS)

%.dep: %.c
	 $(CC) -M $(CFLAGS) -o $@ $<
		 
.PHONY: build
build: $(TARGET)

.PHONY: compile-all
compile-all: $(OBJS)
	$(CC) $^ $(INCLUDES) -c -o $@

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $@
	$(SIZE) $(TARGET)
	
.PHONY: clean
clean:
	rm $(TARGET).map $(PRES) $(ASMS) $(DEPS) $(OBJS) $(TARGET)