IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include


CROSS?=OR1K

standalone:
	IMPERAS_RUNTIME=CpuManager platform/platform.$(IMPERAS_ARCH).exe application/hello.$(CROSS).s19

imperas:
	imperas.exe --objectloader loader/loader.$(IMPERAS_SHRSUF) -objfile application/hello.$(CROSS).s19 -v

