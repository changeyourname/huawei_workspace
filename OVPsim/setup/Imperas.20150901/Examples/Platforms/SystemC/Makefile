IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif
ifndef SYSTEMC_HOME
  SYSTEMC_HOME := $(error "SYSTEMC_HOME must be defined for SystemC install directory")
endif

# SystemC environment variables
#SYSTEMC_HOME must be setup to the root of the SystemC installation
SYSTEMC_INC        = ${SYSTEMC_HOME}/include

ifeq ($(IMPERAS_ARCH),Linux32)
    LIBRTL = $(IMPERAS_HOME)/bin/$(IMPERAS_ARCH)/libRuntimeLoader.so
    SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-linux
endif
ifeq ($(IMPERAS_ARCH),Linux64)
    LIBRTL = $(IMPERAS_HOME)/bin/$(IMPERAS_ARCH)/libRuntimeLoader.so
    SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-linux64
endif
ifeq ($(IMPERAS_ARCH),Windows32)
    LIBRTL = $(IMPERAS_HOME)/bin/$(IMPERAS_ARCH)/libRuntimeLoader.lib
    SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-mingw
endif
ifeq ($(IMPERAS_ARCH),Windows64)
    LIBRTL = $(IMPERAS_HOME)/bin/$(IMPERAS_ARCH)/libRuntimeLoader.lib
    SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-mingw64
endif

SYSTEMC_LIB = $(SYSTEMC_LIB_DIR)/libsystemc.a

# Makefile Options
ifeq (1,${EXTMEMORY})
   # !! Change membase and memsize if you are building with EXTMEMORY=1
   ifndef membase
     membase := $(error "membase not defined")
   endif
   ifndef memsize
     memsize := $(error "memsize not defined")
   endif

   MEM_CFLAGS = -D"EXTMEM_BASEADDR=${membase}" -D"EXTMEM_SIZE=${memsize}"
endif

all: impSimulation.exe

libicmCpuManagerCxx.a:
	$(V) $(HOST_GXX) $(SIM_CFLAGS) \
		-c -o icmCpuManager.o \
        ${IMPERAS_HOME}/ImpPublic/source/host/icm/icmCpuManager.cpp
	$(V) $(HOST_AR) -r $@ icmCpuManager.o

impSimulation.exe: impSimulation.o libicmCpuManagerCxx.a
	$(V) echo "Linking $@"
	$(V) $(HOST_GXX) -g -o $@ $^ $(SIM_CFLAGS) $(SIM_LDFLAGS) ${SYSTEMC_LIB}

impSimulation.$(IMPERAS_SHRSUF): impSimulation.o
	$(V) echo "Making $@"
	$(V) $(HOST_GCC) -shared -g -o $@ $^ $(SIM_CFLAGS) ${SYSTEMC_LIB} $(IMPERAS_ICMSTUBS)

impSimulation.o: platform/impSimulation.cpp
	$(V) echo "Compiling $@"
	$(V) $(HOST_GCC) -c -o $@  $< $(MEM_CFLAGS) $(SIM_CFLAGS) -I${SYSTEMC_INC}

-include $(IMPERAS_LIB)/CrossCompiler/OR1K.makefile.include
ifeq ($(OR1K_CC),)
    IMPERAS_ERROR := $(error "Please install the OR1K_CC toolchain")
endif

clean:
	- rm -f impSimulation.exe impSimulation.o
