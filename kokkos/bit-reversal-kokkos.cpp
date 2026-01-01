#include <Kokkos_Core.hpp>

/* Functions and kernels decleartions */
KOKKOS_INLINE_FUNCTION unsigned int bit_reverse(unsigned int indx, unsigned int N);



KOKKOS_INLINE_FUNCTION unsigned int bit_reverse(unsigned int indx, unsigned int log2)
{
    // Result
    unsigned int index_bit_reversed = 0;

    // Reverse the index
    for (unsigned int k = 0; k < log2; k++){
        index_bit_reversed = (index_bit_reversed << 1) | (indx & 1);
        indx >>= 1;
    }

    return index_bit_reversed;
}

int main(int argc, char* argv[])
{
    // Shutting up OpenMP backend messages
    setenv("OMP_PROC_BIND", "spread", 1);

    Kokkos::initialize(argc, argv);
    {
        /* Backend stuff */
        // Checking execution space
        Kokkos::printf("Backend: %s\n", Kokkos::DefaultExecutionSpace::name());

        // Check number of devices available
        Kokkos::printf("Devices: %d\n", Kokkos::num_devices());


        /* Actual bit-reversing */
        // Initialize array
        size_t length = 16;
        Kokkos::View<unsigned int *> array("array", length);
        Kokkos::parallel_for("fill", length, KOKKOS_LAMBDA(unsigned int k) { array(k) = k;});

        // Peeking OG array
        Kokkos::parallel_for("print_og", length, KOKKOS_LAMBDA(unsigned int k) { Kokkos::printf("%d ", array(k));});
        Kokkos::fence();
        Kokkos::printf("\n");

        // Computing the log2(length) a.k.a. number of bits of the length
        unsigned int N = length;
        unsigned int log2 = 0;
        while (N > 1) {
            log2++;
            N >>= 1;
        }

        // Bit-reversing the array
        Kokkos::parallel_for("bit_reverse", length, 
            KOKKOS_LAMBDA(unsigned int k) {
                unsigned int val = array(k);
                unsigned int reversed_index = bit_reverse(k, log2);
                array(reversed_index) = val;
            }
        );

        // Peeking reversed array
        Kokkos::parallel_for("print_rev", length, KOKKOS_LAMBDA(unsigned int k) { Kokkos::printf("%d ", array(k));});
        Kokkos::fence();
        Kokkos::printf("\n");

        // Eh, Working on GPUs is fine, I could copy this back but oh-well
    }
    Kokkos::finalize();
    return 0;
}