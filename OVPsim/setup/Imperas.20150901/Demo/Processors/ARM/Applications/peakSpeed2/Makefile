IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

SRC = $(wildcard *.c)

ELF = peakSpeed2.ARM7-O0-g.elf peakSpeed2.ARM_CORTEX_A-O0-g.elf peakSpeed2.ARM9-O0-g.elf peakSpeed2.AARCH32-O0-g.elf peakSpeed2.AARCH64-O0-g.elf peakSpeed2.ARM_CORTEX_M0-O0-g.elf peakSpeed2.ARM_CORTEX_M3-O0-g.elf 

# PROG=peakSpeed2
# CROSS=ARM7
# ELFROOT=ARM7-O0-g
# ELF=peakSpeed2.ARM7-O0-g.elf
# OPTIONS=-O0 -g 

ARM7-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM7-O0-g.o,$(S)))

CROSS := ARM7
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=peakSpeed2
# CROSS=ARM_CORTEX_A
# ELFROOT=ARM_CORTEX_A-O0-g
# ELF=peakSpeed2.ARM_CORTEX_A-O0-g.elf
# OPTIONS=-O0 -g 

ARM_CORTEX_A-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_A-O0-g.o,$(S)))

CROSS := ARM_CORTEX_A
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=peakSpeed2
# CROSS=ARM9
# ELFROOT=ARM9-O0-g
# ELF=peakSpeed2.ARM9-O0-g.elf
# OPTIONS=-O0 -g 

ARM9-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM9-O0-g.o,$(S)))

CROSS := ARM9
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=peakSpeed2
# CROSS=AARCH32
# ELFROOT=AARCH32-O0-g
# ELF=peakSpeed2.AARCH32-O0-g.elf
# OPTIONS=-O0 -g 

AARCH32-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.AARCH32-O0-g.o,$(S)))

CROSS := AARCH32
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=peakSpeed2
# CROSS=AARCH64
# ELFROOT=AARCH64-O0-g
# ELF=peakSpeed2.AARCH64-O0-g.elf
# OPTIONS=-O0 -g 

AARCH64-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.AARCH64-O0-g.o,$(S)))

CROSS := AARCH64
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=peakSpeed2
# CROSS=ARM_CORTEX_M0
# ELFROOT=ARM_CORTEX_M0-O0-g
# ELF=peakSpeed2.ARM_CORTEX_M0-O0-g.elf
# OPTIONS=-O0 -g 

ARM_CORTEX_M0-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M0-O0-g.o,$(S)))

CROSS := ARM_CORTEX_M0
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

# PROG=peakSpeed2
# CROSS=ARM_CORTEX_M3
# ELFROOT=ARM_CORTEX_M3-O0-g
# ELF=peakSpeed2.ARM_CORTEX_M3-O0-g.elf
# OPTIONS=-O0 -g 

ARM_CORTEX_M3-O0-g_OBJ = $(foreach S,$(SRC),$(patsubst %.c,%.ARM_CORTEX_M3-O0-g.o,$(S)))

CROSS := ARM_CORTEX_M3
-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
	IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(ELF)

%.ARM7-O0-g.elf:  $(ARM7-O0-g_OBJ)
	@    echo "# Linking ARM7 $@"
	$(V) $(ARM7_LINK) -o $@ $^ $(ARM7_LDFLAGS) -lm
	
%.ARM7-O0-g.o: %.c
	@    echo "# Compiling ARM7 $<"
	$(V) $(ARM7_CC) -c -o $@ $< -DARM7 $(DEF) -O0 -g 

%.ARM_CORTEX_A-O0-g.elf:  $(ARM_CORTEX_A-O0-g_OBJ)
	@    echo "# Linking ARM_CORTEX_A $@"
	$(V) $(ARM_CORTEX_A_LINK) -o $@ $^ $(ARM_CORTEX_A_LDFLAGS) -lm
	
%.ARM_CORTEX_A-O0-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_A $<"
	$(V) $(ARM_CORTEX_A_CC) -c -o $@ $< -DARM_CORTEX_A $(DEF) -O0 -g 

%.ARM9-O0-g.elf:  $(ARM9-O0-g_OBJ)
	@    echo "# Linking ARM9 $@"
	$(V) $(ARM9_LINK) -o $@ $^ $(ARM9_LDFLAGS) -lm
	
%.ARM9-O0-g.o: %.c
	@    echo "# Compiling ARM9 $<"
	$(V) $(ARM9_CC) -c -o $@ $< -DARM9 $(DEF) -O0 -g 

%.AARCH32-O0-g.elf:  $(AARCH32-O0-g_OBJ)
	@    echo "# Linking AARCH32 $@"
	$(V) $(AARCH32_LINK) -o $@ $^ $(AARCH32_LDFLAGS) -lm
	
%.AARCH32-O0-g.o: %.c
	@    echo "# Compiling AARCH32 $<"
	$(V) $(AARCH32_CC) -c -o $@ $< -DAARCH32 $(DEF) -O0 -g 

%.AARCH64-O0-g.elf:  $(AARCH64-O0-g_OBJ)
	@    echo "# Linking AARCH64 $@"
	$(V) $(AARCH64_LINK) -o $@ $^ $(AARCH64_LDFLAGS) -lm
	
%.AARCH64-O0-g.o: %.c
	@    echo "# Compiling AARCH64 $<"
	$(V) $(AARCH64_CC) -c -o $@ $< -DAARCH64 $(DEF) -O0 -g 

%.ARM_CORTEX_M0-O0-g.elf:  $(ARM_CORTEX_M0-O0-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M0 $@"
	$(V) $(ARM_CORTEX_M0_LINK) -o $@ $^ $(ARM_CORTEX_M0_LDFLAGS) -lm
	
%.ARM_CORTEX_M0-O0-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M0 $<"
	$(V) $(ARM_CORTEX_M0_CC) -c -o $@ $< -DARM_CORTEX_M0 $(DEF) -O0 -g 

%.ARM_CORTEX_M3-O0-g.elf:  $(ARM_CORTEX_M3-O0-g_OBJ)
	@    echo "# Linking ARM_CORTEX_M3 $@"
	$(V) $(ARM_CORTEX_M3_LINK) -o $@ $^ $(ARM_CORTEX_M3_LDFLAGS) -lm
	
%.ARM_CORTEX_M3-O0-g.o: %.c
	@    echo "# Compiling ARM_CORTEX_M3 $<"
	$(V) $(ARM_CORTEX_M3_CC) -c -o $@ $< -DARM_CORTEX_M3 $(DEF) -O0 -g 

clean::
	- rm -f $(ELF)
