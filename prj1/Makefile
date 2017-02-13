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

# TRY THIS
ifeq ($(ARCH),armv7l)
	PLATFORM=bbb
endif

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
				
				
CFLAGS= $(PLATFORM_FLAGS) -std=$(CSTD) -g -Wall -Werror -O0
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
		 
.PHONY: all
all: $(TARGET)

.PHONY: compile-all
compile-all: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(INCLUDES) -c -o $@

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $@
	

#main.out: $(OBJS)
#	$(CC) $(CFLAGS) -o $@ $^
	
.PHONY: clean
clean:
	rm $(TARGET).map $(PRES) $(ASMS) $(OBJS) $(TARGET)