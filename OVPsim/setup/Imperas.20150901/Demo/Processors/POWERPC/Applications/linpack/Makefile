IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = linpack.POWERPC32-O0-g.elf linpack.POWERPC32-O0-g.elf 

# PROG=linpack
# CROSS=POWERPC32
# ELFROOT=POWERPC32-O0-g
# ELF=linpack.POWERPC32-O0-g.elf
# OPTIONS=-O0 -g 

POWERPC32-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O0-g.o,$(S)))

CROSS := POWERPC32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=linpack
# CROSS=POWERPC32
# ELFROOT=POWERPC32-O0-g
# ELF=linpack.POWERPC32-O0-g.elf
# OPTIONS=-O0 -g 

POWERPC32-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O0-g.o,$(S)))

CROSS := POWERPC32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.POWERPC32-O0-g.elf:  $(POWERPC32-O0-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O0-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O0 -g 

%.POWERPC32-O0-g.elf:  $(POWERPC32-O0-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O0-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
