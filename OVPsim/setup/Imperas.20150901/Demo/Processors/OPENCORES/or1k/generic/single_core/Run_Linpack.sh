#!/bin/sh
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --program ../../../Applications/linpack/linpack.OR1K-O0-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
     --numprocessors 1          $@     -argv 8

