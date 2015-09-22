IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = fibonacci.CS_NIOS2-O3-g.elf 

# PROG=fibonacci
# CROSS=CS_NIOS2
# ELFROOT=CS_NIOS2-O3-g
# ELF=fibonacci.CS_NIOS2-O3-g.elf
# OPTIONS=-O3 -g 

CS_NIOS2-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.CS_NIOS2-O3-g.o,$(S)))

CROSS := CS_NIOS2
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.CS_NIOS2-O3-g.elf:  $(CS_NIOS2-O3-g_OBJ)
	@    echo "# Linking CS_NIOS2 $@"
	$(V) $(CS_NIOS2_LINK) -o $@ $^ $(CS_NIOS2_LDFLAGS) -lm
	
%.CS_NIOS2-O3-g.o: %.c
	@    echo "# Compiling CS_NIOS2 $<"
	$(V) $(CS_NIOS2_CC) -c -o $@ $< -DCS_NIOS2 $(DEF) -O3 -g 

clean::
	- rm -f $(ELF)
