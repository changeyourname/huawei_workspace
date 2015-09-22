#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci_m16c/fibonacci_m16c.M16C-O2-g.elf \
    --processorvendor posedgesoft.ovpworld.org --processorname m16c --variant m16c \
     --numprocessors 1          $@     -argv 30

