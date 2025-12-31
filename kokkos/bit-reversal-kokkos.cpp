#include <Kokkos_Core.hpp>

int main(int argc, char* argv[])
{
    Kokkos::initialize(argc, argv);
    {
        // Checking execution space
        Kokkos::printf("Backend: %s\n", Kokkos::DefaultExecutionSpace::name());

        // Bit reversal stuff
        size_t length = 16;
        Kokkos::View<unsigned int *> array("array", length);
        Kokkos::parallel_for("fill", length, KOKKOS_LAMBDA(int k) { array(k) = k; });
    }
    Kokkos::finalize();
    return 0;
}