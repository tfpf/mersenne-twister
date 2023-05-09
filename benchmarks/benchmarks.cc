#include <chrono>
#include <cstdio>
#include <iomanip>
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
    auto delay = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();  \
    std::printf("%20s %8.1lf ns\n", #function_call, delay / static_cast<double>(ITERATIONS));  \
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
