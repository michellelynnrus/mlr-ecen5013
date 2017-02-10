#begin makefile
#write comments up here

include sources.mk

PLATFORM = host
CPU = native
ARCH = $(shell arch)
SPECS = nosys.specs
CC=gcc
CSTD=c99
TARGET=main
PLATFORM_FLAGS= -march=$(CPU)

#default platform is host, change CPU and CC if specified otherwise
ifeq ($(PLATFORM),frdm)
	CPU=cortex-m0plus
	CC=arm-none-eabi-gcc
	PLATFORM_FLAGS=-mcpu=$(CPU) --specs=$(SPECS) -mthumb
endif

ifeq ($(PLATFORM),bbb)
	CPU=cortex-a8
	CC=arm-linux-gnueabihf-gcc
	PLATFORM_FLAGS=-mcpu=$(CPU) -mthumb
endif
				
				
CFLAGS= $(PLATFORM_FLAGS) -std=$(CSTD)# -g -Wall -Werror -O0
LDFLAGS= -Wl,-Map=$(TARGET).map
OBJS:=$(SRCS:.c=.o)


#
#OS:=$(shell uname -s)
#ifeq ($(OS),Linux)
#	CC=gcc
#	CPU=native
#	ARCH=$(shell arch)
#else 
#	CC=arm_none_eabi_gcc
#endif


%.o: %.c
	$(CC) -c $^ -o $@ $(CFLAGS)
		 
		 
.PHONY: all
all: main

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $@
	

#main.out: $(OBJS)
#	$(CC) $(CFLAGS) -o $@ $^
	
.PHONY: clean
clean:
	rm $(TARGET).map $(OBJS) $(TARGET)