IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

NOVLNV?=1
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.platform

ifeq ($(EXCEPTIONS),1)
  CFLAGS += -DSIMEXCEPTIONS
endif
