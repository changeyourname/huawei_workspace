IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = linpack.CS_NIOS2-O0-g.elf 

# PROG=linpack
# CROSS=CS_NIOS2
# ELFROOT=CS_NIOS2-O0-g
# ELF=linpack.CS_NIOS2-O0-g.elf
# OPTIONS=-O0 -g 

CS_NIOS2-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.CS_NIOS2-O0-g.o,$(S)))

CROSS := CS_NIOS2
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.CS_NIOS2-O0-g.elf:  $(CS_NIOS2-O0-g_OBJ)
	@    echo "# Linking CS_NIOS2 $@"
	$(V) $(CS_NIOS2_LINK) -o $@ $^ $(CS_NIOS2_LDFLAGS) -lm
	
%.CS_NIOS2-O0-g.o: %.c
	@    echo "# Compiling CS_NIOS2 $<"
	$(V) $(CS_NIOS2_CC) -c -o $@ $< -DCS_NIOS2 $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
