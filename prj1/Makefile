#begin makefile
#write comments up here

include sources.mk

PLATFORM = host
CPU = native
ARCH = $(shell arch)
SPECS = nosys.specs
CC=gcc
CSTD=c99
TARGET=project1
PLATFORM_FLAGS= -march=$(CPU)
PROJECT=1
PLATFORM_CODE=0
SIZE=size

# TRY THIS
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
				
				
CFLAGS= $(PLATFORM_FLAGS) -std=$(CSTD) -g -Wall -Werror -O0 -D PROJECT=$(PROJECT) -D PLATFORM_CODE=$(PLATFORM_CODE)
LDFLAGS= -Wl,-Map=$(TARGET).map
OBJS:=$(SRCS:.c=.o)
PRES:=$(SRCS:.c=.i)
ASMS:=$(SRCS:.c=.asm)


%.o: %.c
	$(CC) -c $^ -o $@ $(CFLAGS)
	
%.i: %.c
	$(CC) -E $^ -o $@ $(CFLAGS)
	
%.asm: %.c
	$(CC) -S $^ -o $@ $(CFLAGS)
		 
.PHONY: build
build: $(TARGET)

.PHONY: compile-all
compile-all: $(OBJS)
	$(CC) $^ $(INCLUDES) -c -o $@

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $@
	$(SIZE) $(TARGET)
	

#main.out: $(OBJS)
#	$(CC) $(CFLAGS) -o $@ $^
	
.PHONY: clean
clean:
	rm $(TARGET).map $(PRES) $(ASMS) $(OBJS) $(TARGET)