IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = multicore2_microblaze.MICROBLAZE-O1-g.elf 

# PROG=multicore2_microblaze
# CROSS=MICROBLAZE
# ELFROOT=MICROBLAZE-O1-g
# ELF=multicore2_microblaze.MICROBLAZE-O1-g.elf
# OPTIONS=-O1 -g 

MICROBLAZE-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MICROBLAZE-O1-g.o,$(S)))

CROSS := MICROBLAZE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.MICROBLAZE-O1-g.elf:  $(MICROBLAZE-O1-g_OBJ)
	@    echo "# Linking MICROBLAZE $@"
	$(V) $(MICROBLAZE_LINK) -o $@ $^ $(MICROBLAZE_LDFLAGS) -lm
	
%.MICROBLAZE-O1-g.o: %.c
	@    echo "# Compiling MICROBLAZE $<"
	$(V) $(MICROBLAZE_CC) -c -o $@ $< -DMICROBLAZE $(DEF) -O1 -g 

clean::
	- rm -f $(ELF)
