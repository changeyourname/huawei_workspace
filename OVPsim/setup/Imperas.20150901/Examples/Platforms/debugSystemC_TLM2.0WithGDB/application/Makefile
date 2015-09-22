IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif

CROSS?=OR1K

all: application.$(CROSS).elf

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS)_CC toolchain")
endif

%.$(CROSS).elf: %.o
	$(V) echo "Linking Application $@"
	$(V) $(IMPERAS_LINK) -g  -gdwarf-2 -o $@  $^  $(IMPERAS_LDFLAGS)

%.o: %.c
	$(V) echo "Compiling Application $@"
	$(V) $(IMPERAS_CC) -g -gdwarf-2 -c  $(IMPERAS_CFLAGS) -D$(CROSS)  -o $@  $<

clean:
	- rm -f application.elf application.o
