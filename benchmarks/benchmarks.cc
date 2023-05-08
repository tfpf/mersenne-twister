#include <chrono>
#include <iomanip>
#include <iostream>
#include <mt19937.h>

// Neither GCC nor Clang eliminate the function call or loop while optimising.
#define ITERATIONS 65536
#define BENCHMARK(function_call)  \
{  \
    auto begin = std::chrono::steady_clock::now();  \
    for(int long i = 0; i < ITERATIONS; ++i)  \
    {  \
        function_call;  \
    }  \
    auto end = std::chrono::steady_clock::now();  \
    auto delay = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / ITERATIONS;  \
    std::cout << std::setw(20) << #function_call << std::setw(8) << delay << " ns\n";  \
}

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    BENCHMARK(mt19937_seed32(0))
    BENCHMARK(mt19937_seed64(0))
    BENCHMARK(mt19937_rand32())
    BENCHMARK(mt19937_rand64())
    BENCHMARK(mt19937_real32())
    BENCHMARK(mt19937_real64())
}
