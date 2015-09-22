#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci_microblaze/fibonacci_microblaze.MICROBLAZE-O3-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_10 \
     --numprocessors 1     --parameter endian=big     $@     -argv 39

