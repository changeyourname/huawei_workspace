IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif

all: platform.$(IMPERAS_ARCH).exe 

icmCpuManager.o:
	$(V) $(HOST_GXX) $(SIM_CFLAGS) \
		-c -o icmCpuManager.o \
	    ${IMPERAS_HOME}/ImpPublic/source/host/icm/icmCpuManager.cpp 

platform.$(IMPERAS_ARCH).exe: platform.$(IMPERAS_ARCH).o icmCpuManager.o
	$(V) echo "Linking Simulation platform $@"
	$(V) $(HOST_GXX) -g -o $@ $^ $(SIM_CFLAGS) $(SIM_LDFLAGS)

platform.$(IMPERAS_ARCH).o: platform.cpp
	$(V) echo "Compiling Simulation platform $<"
	$(V) $(HOST_GXX) -g -c -o $@ $< $(SIM_CFLAGS)


