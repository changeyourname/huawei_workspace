IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

# Various Cross compiler setups, Set default
CROSS?=MIPS32LE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the toolchain to support $(CROSS) ")
endif

ifeq ($(CROSS),MIPS32LE)
   ENDIAN=L
else
   ENDIAN=B
endif

OPTIMISATION=-O0 -g -gdwarf-2

SRC=genexception.s main.s

# Define the base address to link the separate code
CODEBASE.genexception.$(CROSS).elf=0x1fc00380
CODEBASE.main.$(CROSS).elf=0x80000000

EXE = $(patsubst %.s,%.$(CROSS).elf,$(SRC))

all: $(EXE)

%.$(CROSS).elf: %.o
	$(V)  echo "Linking $@ at base $(CODEBASE.$@)"
	$(V)  $(IMPERAS_LD) -E$(ENDIAN) -Ttext $(CODEBASE.$@) -o $@ $< 

# Compilation of standard benchmarch code
%.o: %.s
	$(V)  echo "Assembling $<"
	$(V)  $(IMPERAS_AS) -mips32r2 -E$(ENDIAN) -o $@ $< $(OPTIMISATION)

clean:
	-rm -f *.elf *.o 
