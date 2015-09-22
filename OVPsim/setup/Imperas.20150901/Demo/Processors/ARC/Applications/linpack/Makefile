IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = linpack.ARC600-O1-g.elf linpack.ARC700-O0-g.elf 

# PROG=linpack
# CROSS=ARC600
# ELFROOT=ARC600-O1-g
# ELF=linpack.ARC600-O1-g.elf
# OPTIONS=-O1 -g 

ARC600-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC600-O1-g.o,$(S)))

CROSS := ARC600
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=linpack
# CROSS=ARC700
# ELFROOT=ARC700-O0-g
# ELF=linpack.ARC700-O0-g.elf
# OPTIONS=-O0 -g 

ARC700-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARC700-O0-g.o,$(S)))

CROSS := ARC700
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.ARC600-O1-g.elf:  $(ARC600-O1-g_OBJ)
	@    echo "# Linking ARC600 $@"
	$(V) $(ARC600_LINK) -o $@ $^ $(ARC600_LDFLAGS) -lm
	
%.ARC600-O1-g.o: %.c
	@    echo "# Compiling ARC600 $<"
	$(V) $(ARC600_CC) -c -o $@ $< -DARC600 $(DEF) -O1 -g 

%.ARC700-O0-g.elf:  $(ARC700-O0-g_OBJ)
	@    echo "# Linking ARC700 $@"
	$(V) $(ARC700_LINK) -o $@ $^ $(ARC700_LDFLAGS) -lm
	
%.ARC700-O0-g.o: %.c
	@    echo "# Compiling ARC700 $<"
	$(V) $(ARC700_CC) -c -o $@ $< -DARC700 $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
