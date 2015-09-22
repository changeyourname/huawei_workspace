IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

# needed to find mips32CacheExtBIU.h
CFLAGS = -I$(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/ImperasLib/mips.com/processor/mips32/1.0

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.platform
