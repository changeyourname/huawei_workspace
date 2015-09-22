IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = fibonacci_microblaze.MICROBLAZE-O3-g.elf 

# PROG=fibonacci_microblaze
# CROSS=MICROBLAZE
# ELFROOT=MICROBLAZE-O3-g
# ELF=fibonacci_microblaze.MICROBLAZE-O3-g.elf
# OPTIONS=-O3 -g 

MICROBLAZE-O3-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MICROBLAZE-O3-g.o,$(S)))

CROSS := MICROBLAZE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.MICROBLAZE-O3-g.elf:  $(MICROBLAZE-O3-g_OBJ)
	@    echo "# Linking MICROBLAZE $@"
	$(V) $(MICROBLAZE_LINK) -o $@ $^ $(MICROBLAZE_LDFLAGS) -lm
	
%.MICROBLAZE-O3-g.o: %.c
	@    echo "# Compiling MICROBLAZE $<"
	$(V) $(MICROBLAZE_CC) -c -o $@ $< -DMICROBLAZE $(DEF) -O3 -g 

clean::
	- rm -f $(ELF)
