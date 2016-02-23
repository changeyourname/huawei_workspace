#!/bin/bash

NUM_CPUS=1              # 1/2/4

ARM_SYSTEM="armv8"      # "armv7"; "armv8"

CACHES_MODE=0        # 0->no cache; 1->gem5 L1caches; 2->gem5 L1+L2caches; 
                        # 3->SystemC L1caches; 4->SystemC L1+L2caches
                    
GEM5_BINARY=gem5.fast    # gem5.opt; gem5.fast

CPU_TYPE=atomic         # timing; atomic

DISK_IMAGE_TYPE=0       # 0->minimal; 1->ubuntu







SYSC_MAKE_CMD="make NUM_CPUS=${NUM_CPUS} "

if [ "$ARM_SYSTEM" = "armv7" ]; 
then
    MACHINE_TYPE=VExpress_EMM
    ISA=arm
    DTB=vexpress.aarch32.ll_20131205.0-gem5.${NUM_CPUS}cpu.dtb
    KERNEL=vmlinux.aarch32.ll_20131205.0-gem5
    if [ $DISK_IMAGE_TYPE -eq 0 ]; 
    then
        DISK_IMAGE=linux-aarch32-ael.img
    else
        DISK_IMAGE=aarch32-ubuntu-natty-headless.img
    fi
    
    if [ $CACHES_MODE -gt 2 ]; then
        make clean
        CACHES="--systemc-cache --cacheline_size=4"
    fi
    
    SYSC_MAKE_CMD+="WORD_SIZE=4 "
else
    MACHINE_TYPE=VExpress_EMM64
    ISA=aarch64
    DTB=vexpress.aarch64.20140821.dtb
    KERNEL=vmlinux.aarch64.20140821
    if [ $DISK_IMAGE_TYPE -eq 0 ];
    then
        DISK_IMAGE=linaro-minimal-aarch64.img
    else
        DISK_IMAGE=aarch64-ubuntu-trusty-headless.img
    fi
    
    if [ $CACHES_MODE -gt 2 ]; then
        make clean
        CACHES="--systemc-cache --cacheline_size=8"
    fi
    
    SYSC_MAKE_CMD+="WORD_SIZE=8 "  
fi 


if [ $CACHES_MODE -eq 1 ]; then
    CACHES="--caches"
elif [ $CACHES_MODE -eq 2 ]; then
    CACHES="--caches --l2cache" 
fi
    


../../build/ARM/$GEM5_BINARY ../../configs/example/fs.py --cpu-type=$CPU_TYPE \
--num-cpu=$NUM_CPUS --mem-type=SimpleMemory --mem-size=512MB --mem-channels=1 \
--machine-type=$MACHINE_TYPE --dtb-filename=$DTB --kernel=$KERNEL --disk-image=$DISK_IMAGE \
--arm-iset=$ISA $CACHES

if [ $CACHES_MODE -gt 2 ]; then
    if [ $CACHES_MODE -eq 4 ]; then
        SYSC_MAKE_CMD+="L2_CACHE=1 "
    fi
    ${SYSC_MAKE_CMD}
    ./gem5.opt.sc m5out/config.ini -o 2147483648
fi












