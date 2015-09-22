IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = fibonacci.POWERPC32-O3-g.elf fibonacci.POWERPC32-O3-g.elf 

# PROG=fibonacci
# CROSS=POWERPC32
# ELFROOT=POWERPC32-O3-g
# ELF=fibonacci.POWERPC32-O3-g.elf
# OPTIONS=-O3 -g 

POWERPC32-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O3-g.o,$(S)))

CROSS := POWERPC32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=fibonacci
# CROSS=POWERPC32
# ELFROOT=POWERPC32-O3-g
# ELF=fibonacci.POWERPC32-O3-g.elf
# OPTIONS=-O3 -g 

POWERPC32-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.POWERPC32-O3-g.o,$(S)))

CROSS := POWERPC32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.POWERPC32-O3-g.elf:  $(POWERPC32-O3-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O3-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O3 -g 

%.POWERPC32-O3-g.elf:  $(POWERPC32-O3-g_OBJ)
	@    echo "# Linking POWERPC32 $@"
	$(V) $(POWERPC32_LINK) -o $@ $^ $(POWERPC32_LDFLAGS) -lm
	
%.POWERPC32-O3-g.o: %.c
	@    echo "# Compiling POWERPC32 $<"
	$(V) $(POWERPC32_CC) -c -o $@ $< -DPOWERPC32 $(DEF) -O3 -g 

clean::
	- rm -f $(ELF)
