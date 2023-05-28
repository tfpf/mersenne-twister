#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <mt19937.h>

// Neither GCC nor Clang eliminate the function call or loops while optimising.
// The definitions of the functions are in a shared object, and not visible to
// the compiler.
template<typename f>
void benchmark(f function, char const* name, int long iterations, int passes=32)
{
    auto delay = std::chrono::nanoseconds::max();
    while(passes-- > 0)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        for(int long i = 0; i < iterations; ++i)
        {
            // Must pass the last argument, because macro expansion won't
            // affect a template.
            function(NULL);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto delay_ = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        delay = std::min(delay, delay_);
    }
    auto result = delay.count() / static_cast<double>(iterations);
    std::printf("%20s %8.2lf ns\n", name, result);
}

#define benchmark(function, iterations) benchmark(function, #function, iterations);

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    benchmark(mt19937_init32, 0x1000)
    benchmark(mt19937_init64, 0x1000)
    benchmark(mt19937_rand32, 0xFFF0)
    benchmark(mt19937_rand64, 0xFFF0)
    benchmark(mt19937_real32, 0xFFF0)
    benchmark(mt19937_real64, 0xFFF0)
}
