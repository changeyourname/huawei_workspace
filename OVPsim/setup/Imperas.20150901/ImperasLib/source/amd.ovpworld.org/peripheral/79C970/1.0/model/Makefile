IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
ifeq ($(IMPERAS_UNAME),Windows)
    LDFLAGS=-lwsock32 -liphlpapi
endif
include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
