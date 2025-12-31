#include <Kokkos_Core.hpp>

int main(int argc, char* argv[])
{
    // Shutting up OpenMP backend messages
    setenv("OMP_PROC_BIND", "spread", 1);

    Kokkos::initialize(argc, argv);
    {
        // Checking execution space
        Kokkos::printf("Backend: %s\n", Kokkos::DefaultExecutionSpace::name());

        // Check number of devices available
        Kokkos::printf("Devices: %d\n", Kokkos::num_devices());


        // Initialize array
        size_t length = 16;
        Kokkos::View<unsigned int *> array("array", length);
        Kokkos::parallel_for("fill", length, KOKKOS_LAMBDA(unsigned int k) { array(k) = k;});


    }
    Kokkos::finalize();
    return 0;
}