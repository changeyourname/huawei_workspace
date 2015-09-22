IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.platform

IGEN         := $(IMPERAS_HOME)/bin/$(IMPERAS_ARCH)/igen.exe

platformsource: testByteSwap.xml

testByteSwap.xml: platform.tcl
	$(V) $(IGEN) --batch platform.tcl -writexml testByteSwap.xml
