IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = fibonacci.OR1K-O3-g.elf 

# PROG=fibonacci
# CROSS=OR1K
# ELFROOT=OR1K-O3-g
# ELF=fibonacci.OR1K-O3-g.elf
# OPTIONS=-O3 -g 

OR1K-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.OR1K-O3-g.o,$(S)))

CROSS := OR1K
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.OR1K-O3-g.elf:  $(OR1K-O3-g_OBJ)
	@    echo "# Linking OR1K $@"
	$(V) $(OR1K_LINK) -o $@ $^ $(OR1K_LDFLAGS) -lm
	
%.OR1K-O3-g.o: %.c
	@    echo "# Compiling OR1K $<"
	$(V) $(OR1K_CC) -c -o $@ $< -DOR1K $(DEF) -O3 -g 

clean::
	- rm -f $(ELF)
