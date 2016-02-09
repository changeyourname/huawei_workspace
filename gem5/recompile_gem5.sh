scons build/ARM/gem5.opt -j16
scons build/ARM/gem5.fast -j16
scons --with-cxx-config --without-python build/ARM/libgem5_opt.so -j16
scons --with-cxx-config --without-python build/ARM/libgem5_fast.so -j16

