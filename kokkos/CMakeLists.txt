# Bits and bobs of any basic Cmake
cmake_minimum_required(VERSION 3.22)
project(bitReversal)

# finding Kokkos
find_package(Kokkos REQUIRED)

# Sources
set(SRC_DIR ".")
set(SRC_FILE ${SRC_DIR}/bit-reversal-kokkos.cpp)

# Executables
add_executable(bitReversal ${SRC_FILE})
target_link_libraries(bitReversal Kokkos::kokkos)