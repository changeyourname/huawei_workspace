IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = peakSpeed1_m16c.M16C-O0-g.elf 

# PROG=peakSpeed1_m16c
# CROSS=M16C
# ELFROOT=M16C-O0-g
# ELF=peakSpeed1_m16c.M16C-O0-g.elf
# OPTIONS=-O0 -g 

M16C-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.M16C-O0-g.o,$(S)))

CROSS := M16C
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.M16C-O0-g.elf:  $(M16C-O0-g_OBJ)
	@    echo "# Linking M16C $@"
	$(V) $(M16C_LINK) -o $@ $^ $(M16C_LDFLAGS) -lm
	
%.M16C-O0-g.o: %.c
	@    echo "# Compiling M16C $<"
	$(V) $(M16C_CC) -c -o $@ $< -DM16C $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
