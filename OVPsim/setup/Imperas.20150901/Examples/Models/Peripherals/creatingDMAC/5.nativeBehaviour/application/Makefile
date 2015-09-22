IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif

all: dmaTest.elf 

# APP
CROSS?=OR1K
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS)_CC toolchain")
endif

dmaTest.elf: dmaTest.o
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -o $@  $^ $(IMPERAS_LDFLAGS)

dmaTest.o: dmaTest.c
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c -Iapplication -o $@  $<

clean:
	$(V) - rm -f dmaTest.elf dmaTest.o

