#include <chrono>
#include <cstdio>
#include <mt19937.h>

// Neither GCC nor Clang eliminate the function call or loop while optimising.
// The definitions of the functions are in a shared object, and not visible to
// the compiler.
#define BENCHMARK(function_call, iterations)  \
{  \
    auto begin = std::chrono::steady_clock::now();  \
    for(int long i = 0; i < iterations; ++i)  \
    {  \
        function_call;  \
    }  \
    auto end = std::chrono::steady_clock::now();  \
    auto delay = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();  \
    std::printf("%20s %8.1lf ns\n", #function_call, delay / static_cast<double>(iterations));  \
}

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    BENCHMARK(mt19937_init32(), 0x10000)
    BENCHMARK(mt19937_init64(), 0x10000)
    BENCHMARK(mt19937_rand32(), 0xFFF00)
    BENCHMARK(mt19937_rand64(), 0xFFF00)
    BENCHMARK(mt19937_real32(), 0xFFF00)
    BENCHMARK(mt19937_real64(), 0xFFF00)
}
