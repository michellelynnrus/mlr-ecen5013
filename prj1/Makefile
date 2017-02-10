#begin makefile
#write comments up here

include sources.mk

CPU = native
ARCH = $(shell arch)
#SPECS = #nosys.specs
CC=gcc
CSTD=c99
TARGET=main
PLATFORM_FLAGS:=-march=$(CPU) #\
#				-mcpu=$(CPU) #\
#				--specs=$(SPECS)
				
CFLAGS= $(PLATFORM_FLAGS)#-g -std=$(CSTD) -mthumb -Wall -Werror -O0
LDFLAGS= -Wl,-Map=$(TARGET).map
OBJS:=$(SRCS:.c=.o)

#ifeq ($(PLATFORM),FRDM)
#	CPU=cortex-m0plus
#endif
#
#ifeq ($(PLATFORM),BBB)
#	CPU=cortex-a8
#endif
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
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $@.out
	

#main.out: $(OBJS)
#	$(CC) $(CFLAGS) -o $@ $^
	
.PHONY: clean
clean:
	rm $(TARGET).map $(OBJS) $(TARGET).out