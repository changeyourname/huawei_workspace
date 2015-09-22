IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = peakSpeed2_microblaze.MICROBLAZE-O0-g.elf 

# PROG=peakSpeed2_microblaze
# CROSS=MICROBLAZE
# ELFROOT=MICROBLAZE-O0-g
# ELF=peakSpeed2_microblaze.MICROBLAZE-O0-g.elf
# OPTIONS=-O0 -g 

MICROBLAZE-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MICROBLAZE-O0-g.o,$(S)))

CROSS := MICROBLAZE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.MICROBLAZE-O0-g.elf:  $(MICROBLAZE-O0-g_OBJ)
	@    echo "# Linking MICROBLAZE $@"
	$(V) $(MICROBLAZE_LINK) -o $@ $^ $(MICROBLAZE_LDFLAGS) -lm
	
%.MICROBLAZE-O0-g.o: %.c
	@    echo "# Compiling MICROBLAZE $<"
	$(V) $(MICROBLAZE_CC) -c -o $@ $< -DMICROBLAZE $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
