IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = fibonacci.ARC600-O3-g.elf fibonacci.ARC700-O2-g.elf 

# PROG=fibonacci
# CROSS=ARC600
# ELFROOT=ARC600-O3-g
# ELF=fibonacci.ARC600-O3-g.elf
# OPTIONS=-O3 -g 

ARC600-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC600-O3-g.o,$(S)))

CROSS := ARC600
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=fibonacci
# CROSS=ARC700
# ELFROOT=ARC700-O2-g
# ELF=fibonacci.ARC700-O2-g.elf
# OPTIONS=-O2 -g 

ARC700-O2-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC700-O2-g.o,$(S)))

CROSS := ARC700
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.ARC600-O3-g.elf:  $(ARC600-O3-g_OBJ)
	@    echo "# Linking ARC600 $@"
	$(V) $(ARC600_LINK) -o $@ $^ $(ARC600_LDFLAGS) -lm
	
%.ARC600-O3-g.o: %.c
	@    echo "# Compiling ARC600 $<"
	$(V) $(ARC600_CC) -c -o $@ $< -DARC600 $(DEF) -O3 -g 

%.ARC700-O2-g.elf:  $(ARC700-O2-g_OBJ)
	@    echo "# Linking ARC700 $@"
	$(V) $(ARC700_LINK) -o $@ $^ $(ARC700_LDFLAGS) -lm
	
%.ARC700-O2-g.o: %.c
	@    echo "# Compiling ARC700 $<"
	$(V) $(ARC700_CC) -c -o $@ $< -DARC700 $(DEF) -O2 -g 

clean::
	- rm -f $(ELF)
