#!/bin/bash

spack load cmake kokkos

BUILD_DIR=build
cmake -B $BUILD_DIR
make -s -C $BUILD_DIR
$BUILD_DIR/bitReversal > run.log
cat run.log