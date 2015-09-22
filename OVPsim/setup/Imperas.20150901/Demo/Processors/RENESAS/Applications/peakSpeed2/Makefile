IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = peakSpeed2.V850-O0-g.elf 

# PROG=peakSpeed2
# CROSS=V850
# ELFROOT=V850-O0-g
# ELF=peakSpeed2.V850-O0-g.elf
# OPTIONS=-O0 -g 

V850-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.V850-O0-g.o,$(S)))

CROSS := V850
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.V850-O0-g.elf:  $(V850-O0-g_OBJ)
	@    echo "# Linking V850 $@"
	$(V) $(V850_LINK) -o $@ $^ $(V850_LDFLAGS) -lm
	
%.V850-O0-g.o: %.c
	@    echo "# Compiling V850 $<"
	$(V) $(V850_CC) -c -o $@ $< -DV850 $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
