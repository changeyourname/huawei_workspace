IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif

CROSS?=OR1K
all: application.$(CROSS).elf asmtest.$(CROSS).elf

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/OR1K.makefile.include
ifeq ($(OR1K_CC),)
    IMPERAS_ERROR := $(error "Please install the OR1K_CC toolchain")
endif

application.$(CROSS).od: application.$(CROSS).elf
	$(V) $($(CROSS)_OBJDUMP) -d $^ > $@

application.$(CROSS).elf: application.$(CROSS).o
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -o $@ $^ $($(CROSS)_LDFLAGS)

application.$(CROSS).o: application.c
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC) -c -g -gdwarf-2 -o $@ $<

asmtest.$(CROSS).elf: asmtest.$(CROSS).o
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LD) -o $@ --section-start .text=0 $^

asmtest.$(CROSS).o: asmtest.S
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  -o $@  $<

clean:
	$(V) - rm -f application.$(CROSS).elf application/application.$(CROSS).o
	$(V) - rm -f asmtest.$(CROSS).elf application/asmtest.$(CROSS).o
	
