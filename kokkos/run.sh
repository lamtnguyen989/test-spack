#!/bin/bash

# Loading libraries with Spack
spack load cmake kokkos

# Cmake config
BUILD_DIR=build
cmake   -B $BUILD_DIR \
        -DCMAKE_BUILD_TYPE=Release \
        -DKokkos_ENABLE_CUDA_RELOCATABLE_DEVICE_CODE=ON \

# Compile and run executable
make -C $BUILD_DIR VERBOSE=1 -j$(nproc)
$BUILD_DIR/bitReversal > run.log

# Result 
cat run.log