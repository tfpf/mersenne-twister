#include <algorithm>
#include <chrono>
#include <cstdio>
#include <mt19937.h>

// Neither GCC nor Clang eliminate the function call or loops while optimising.
// The definitions of the functions are in a shared object, and not visible to
// the compiler.
#define benchmark(function, iterations)  \
{  \
    auto delay = std::chrono::nanoseconds::max();  \
    for(int i = 0; i < 32; ++i)  \
    {  \
        auto begin = std::chrono::high_resolution_clock::now();  \
        for(int long i = 0; i < iterations; ++i)  \
        {  \
            function();  \
        }  \
        auto end = std::chrono::high_resolution_clock::now();  \
        auto delay_ = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);  \
        delay = std::min(delay, delay_);  \
    }  \
    auto result = delay.count() / static_cast<double>(iterations);  \
    std::printf("%20s %8.2lf ns\n", #function, result);  \
}

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    benchmark(mt19937::init32, 0x1000L)
    benchmark(mt19937::init64, 0x1000L)
    benchmark(mt19937::rand32, 0xFFF0L)
    benchmark(mt19937::rand64, 0xFFF0L)
    benchmark(mt19937::real32, 0xFFF0L)
    benchmark(mt19937::real64, 0xFFF0L)
}
