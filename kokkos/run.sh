#!/bin/bash

spack load cmake kokkos

BUILD_DIR=build
cmake -B $BUILD_DIR --verbose
make -C $BUILD_DIR VERBOSE=1
$BUILD_DIR/bitReversal > run.log
cat run.log