ifeq ($(TOOLDIR),)
  IMPERAS_ERROR := $(error "You must define the TOOLDIR variable")
endif
  
ROOT=$(TOOLDIR)/bin/arm-none-linux-gnueabi

CC=$(ROOT)-gcc

CFLAGS=-g
LDFLAGS=-lm

SRC = $(wildcard *.c)
EXE = $(SRC:.c=.exe)

all: $(EXE)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean::
	rm -f $(EXE)
