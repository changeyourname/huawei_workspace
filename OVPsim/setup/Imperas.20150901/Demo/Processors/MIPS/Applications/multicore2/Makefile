IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = multicore2.MIPS32LE-O1-g.elf multicore2.CS_UMIPS-O1-g.elf multicore2.CS_MIPS32LE-O1-g.elf multicore2.CS_MIPS32-O1-g.elf multicore2.CS_MIPS64-O1-g.elf 

# PROG=multicore2
# CROSS=MIPS32LE
# ELFROOT=MIPS32LE-O1-g
# ELF=multicore2.MIPS32LE-O1-g.elf
# OPTIONS=-O1 -g 

MIPS32LE-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.MIPS32LE-O1-g.o,$(S)))

CROSS := MIPS32LE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=multicore2
# CROSS=CS_UMIPS
# ELFROOT=CS_UMIPS-O1-g
# ELF=multicore2.CS_UMIPS-O1-g.elf
# OPTIONS=-O1 -g 

CS_UMIPS-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.CS_UMIPS-O1-g.o,$(S)))

CROSS := CS_UMIPS
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=multicore2
# CROSS=CS_MIPS32LE
# ELFROOT=CS_MIPS32LE-O1-g
# ELF=multicore2.CS_MIPS32LE-O1-g.elf
# OPTIONS=-O1 -g 

CS_MIPS32LE-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.CS_MIPS32LE-O1-g.o,$(S)))

CROSS := CS_MIPS32LE
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=multicore2
# CROSS=CS_MIPS32
# ELFROOT=CS_MIPS32-O1-g
# ELF=multicore2.CS_MIPS32-O1-g.elf
# OPTIONS=-O1 -g 

CS_MIPS32-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.CS_MIPS32-O1-g.o,$(S)))

CROSS := CS_MIPS32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=multicore2
# CROSS=CS_MIPS64
# ELFROOT=CS_MIPS64-O1-g
# ELF=multicore2.CS_MIPS64-O1-g.elf
# OPTIONS=-O1 -g 

CS_MIPS64-O1-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.CS_MIPS64-O1-g.o,$(S)))

CROSS := CS_MIPS64
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.MIPS32LE-O1-g.elf:  $(MIPS32LE-O1-g_OBJ)
	@    echo "# Linking MIPS32LE $@"
	$(V) $(MIPS32LE_LINK) -o $@ $^ $(MIPS32LE_LDFLAGS) -lm
	
%.MIPS32LE-O1-g.o: %.c
	@    echo "# Compiling MIPS32LE $<"
	$(V) $(MIPS32LE_CC) -c -o $@ $< -DMIPS32LE $(DEF) -O1 -g 

%.CS_UMIPS-O1-g.elf:  $(CS_UMIPS-O1-g_OBJ)
	@    echo "# Linking CS_UMIPS $@"
	$(V) $(CS_UMIPS_LINK) -o $@ $^ $(CS_UMIPS_LDFLAGS) -lm
	
%.CS_UMIPS-O1-g.o: %.c
	@    echo "# Compiling CS_UMIPS $<"
	$(V) $(CS_UMIPS_CC) -c -o $@ $< -DCS_UMIPS $(DEF) -O1 -g 

%.CS_MIPS32LE-O1-g.elf:  $(CS_MIPS32LE-O1-g_OBJ)
	@    echo "# Linking CS_MIPS32LE $@"
	$(V) $(CS_MIPS32LE_LINK) -o $@ $^ $(CS_MIPS32LE_LDFLAGS) -lm
	
%.CS_MIPS32LE-O1-g.o: %.c
	@    echo "# Compiling CS_MIPS32LE $<"
	$(V) $(CS_MIPS32LE_CC) -c -o $@ $< -DCS_MIPS32LE $(DEF) -O1 -g 

%.CS_MIPS32-O1-g.elf:  $(CS_MIPS32-O1-g_OBJ)
	@    echo "# Linking CS_MIPS32 $@"
	$(V) $(CS_MIPS32_LINK) -o $@ $^ $(CS_MIPS32_LDFLAGS) -lm
	
%.CS_MIPS32-O1-g.o: %.c
	@    echo "# Compiling CS_MIPS32 $<"
	$(V) $(CS_MIPS32_CC) -c -o $@ $< -DCS_MIPS32 $(DEF) -O1 -g 

%.CS_MIPS64-O1-g.elf:  $(CS_MIPS64-O1-g_OBJ)
	@    echo "# Linking CS_MIPS64 $@"
	$(V) $(CS_MIPS64_LINK) -o $@ $^ $(CS_MIPS64_LDFLAGS) -lm
	
%.CS_MIPS64-O1-g.o: %.c
	@    echo "# Compiling CS_MIPS64 $<"
	$(V) $(CS_MIPS64_CC) -c -o $@ $< -DCS_MIPS64 $(DEF) -O1 -g 

clean::
	- rm -f $(ELF)
