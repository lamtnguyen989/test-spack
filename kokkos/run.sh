#!/bin/bash

spack load cmake kokkos

BUILD_DIR=build
cmake -B $BUILD_DIR
make -C $BUILD_DIR
$BUILD_DIR/bitReversal > run.log