IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

include $(IMPERAS_HOME)/bin/Makefile.include

ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif

simulate:
	$(V) platform/platform.$(IMPERAS_ARCH).exe
