CC = cc
CFLAGS = -std=c99 -Wall -g -O0
#-Werror
#
# build third-party libraries
#
SUBDIRS = ../../3rd-party

TEST = circBuf


ifdef SUBDIRS
.PHONY : $(SUBDIRS)
$(SUBDIRS) : 
	$(MAKE) --no-print-directory --directory=$@ \
		CC=$(CC) CFLAGS="$(CFLAGS)" $(MAKECMDGOALS)
endif

THIRD_PARTY_DIR = ../../3rd-party
CMOCKA_INCLUDE_DIR = $(THIRD_PARTY_DIR)/build-Debug/include
CMOCKA_LIBRARY = $(THIRD_PARTY_DIR)/build-Debug/lib/libcmocka.a

cmocka : $(SUBDIRS)

CFLAGS += -I $(CMOCKA_INCLUDE_DIR)

#
# quick and dirty build rules to demonstrate testing, not good build
# system practices.
#

#
# library
#
LIB_SRCS = \
	../src/memory.c \
	../src/data.c \
	../src/circBuf.c

LIB_OBJS = $(LIB_SRCS:%.c=%.o)

LIB_HEADERS = $(LIB_SRCS:%.c=%.h)

LIB = libutils.a

#
# main executable
#
EXE_SRCS = main.c
EXE_OBJS = $(EXE_SRCS:%.c=%.o)

EXE = main.out

#
# tests
#
TEST_SRCS = \
	$(addsuffix .c, $(addprefix src/test_, $(TEST)))

TEST_DATA_OBJS = $(TEST_SRCS:%.c=%.o)

TEST_EXE = $(addsuffix .out, $(addprefix src/test_, $(TEST)))


#
# Generic rule to generate objects
#
%.o : %.c
	$(CC) $(CFLAGS) -I ../hdr -I hdr -c -o $@ $<

$(LIB) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

all : $(LIB) $(EXE)

$(EXE) : $(EXE_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test : $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE) : $(TEST_SRCS) $(LIB)
	$(CC) $(CFLAGS) -I ../hdr -I hdr -o $@ $^ $(CMOCKA_LIBRARY) -lm


.PHONY : clean
clean : FORCE
	-rm -rf *~ *.o $(LIB) $(EXE) $(TEST_EXE) *.dSYM/

.PHONY : clobber
clobber : $(SUBDIRS) clean


FORCE :