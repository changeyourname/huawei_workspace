#!/bin/sh
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/fibonacci/fibonacci.OR1K-O3-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
     --numprocessors 1          $@     -argv 36

