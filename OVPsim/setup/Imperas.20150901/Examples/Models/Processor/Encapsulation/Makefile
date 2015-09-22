IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif

XTHOME?=$(shell pwd)/externalISS

all: libXTrisc32.$(IMPERAS_SHRSUF) risc32Model.$(IMPERAS_SHRSUF) testcase.risc32 platform.exe

#
# Processor Section
#
LDFLAGS = $(OTHER_LDFLAGS)

ifeq ($(shell uname),Linux)
  LDFLAGS += -Wl,--version-script=version.script
else
  LDFLAGS += export.def
endif
LDFLAGS+=-L$(XTHOME) -lXTrisc32

CFLAGS = $(SIM_CFLAGS) $(OTHER_CFLAGS)

CFLAGS+=-I$(XTHOME)

SRCS.c = $(sort $(wildcard *.c))
SRCS.S = $(sort $(wildcard *.S))
OBJS.c = $(foreach obj, $(SRCS.c:.c=.o), $(obj))
OBJS.S = $(foreach obj, $(SRCS.S:.S=.o), $(obj))
OBJS = $(OBJS.c) $(OBJS.S)
SOLIB = risc32Model.$(IMPERAS_SHRSUF)

%.o: %.c
	$(V) echo "Compiling Processor $@"
	$(V) $(HOST_GCC) $(CFLAGS) $(SIM_CFLAGS) -c -o $@ $^

$(SOLIB): $(OBJS)
	$(V) echo "Linking Processor"
	$(V) $(HOST_GCC) $(CFLAGS) $(SIM_LDFLAGS) --shared -o $@ $^ $(IMPERAS_VMISTUBS) $(LDFLAGS)

#
# Imported externalISS Simulator Section
#
libXTrisc32.$(IMPERAS_SHRSUF): $(XTHOME)/libXTrisc32.$(IMPERAS_SHRSUF)
	cp $< $@

$(XTHOME)/asmXtrisc32.exe $(XTHOME)/libXTrisc32.$(IMPERAS_SHRSUF): $(XTHOME)/XTrisc32.c $(XTHOME)/XTrisc32.h $(XTHOME)/asmXtrisc32.c
	$(MAKE) -C $(XTHOME)

#
# platform Section
#
MORPHER_FILE   = "./risc32Model.$(IMPERAS_SHRSUF)"
TYPE_NAME      = "risc32"
APPLICATION    = "application.elf"

platform.exe: platform/platform.o
	$(V) echo "Linking platform $@"
	$(V) $(HOST_GCC) $(CFLAGS) -o $@  $^  $(CFLAGS) $(SIM_LDFLAGS) 

platform/platform.o: platform/platform.c
	$(V) echo "Compiling platform $@"
	$(V) $(HOST_GCC) $(CFLAGS) -c -o $@  $< $(CFLAGS) \
	  -DMORPHER_FILE="\"${MORPHER_FILE}\"" \
	  -DTYPE_NAME="\"${TYPE_NAME}\"" 

#
# Application section
#
testcase.risc32: application/testcase.S $(XTHOME)/asmXtrisc32.exe 
	$(V) echo "Assembling Application $@"
	$(XTHOME)/asmXtrisc32.exe $< $@

#
# Cleanup section
#
clean:
	$(V) - rm -f testcase.risc32
	$(V) - rm -f $(OBJS) $(SOLIB)
	$(V) - rm -f platform/platform.o platform.exe
	$(V) - rm -f $(XTHOME)/libXTrisc32.lib
	$(V) - rm -f libXTrisc32.$(IMPERAS_SHRSUF) $(XTHOME)/libXTrisc32.$(IMPERAS_SHRSUF) 
	$(V) - rm -f $(XTHOME)/asmXtrisc32.exe
