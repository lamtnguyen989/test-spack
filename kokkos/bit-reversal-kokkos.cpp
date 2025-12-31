#include <Kokkos_Core.hpp>
#include <iostream>
#include <type_traits>

int main(int argc, char* argv[])
{
    Kokkos::initialize(argc, argv);

    // Checking execution space
    std::cout   << "Backend: " 
                << Kokkos::DefaultExecutionSpace::name() 
                << std::endl;

    // Bit reversal stuff (TODO)
    //Kokkos::View<int *> array("default", 16);

    Kokkos::finalize();
}