#include <assert.h>
#include <inttypes.h>
#include <mt19937.h>
#include <stdbool.h>
#include <stdio.h>

/******************************************************************************
 * Test MT19937. The results of this implementation must match those of a C++
 * standard library implementation. See
 * https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.
 *****************************************************************************/
void tests(void)
{
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_rand();
    }

    for(int i = 1; i < 10000; ++i)
    {
        mt19937_64_rand();
    }

    struct mt19937_t mt32;
    mt19937_seed(5489, &mt32);
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_rand(&mt32);
    }

    struct mt19937_64_t mt64;
    mt19937_64_seed(5489, &mt64);
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_64_rand(&mt64);
    }

    // Placing all assertions here ensures that we detect if any two MT19937
    // objects interfere with each other.
    assert(mt19937_rand() == 0xF5CA0EDBU);
    assert(mt19937_64_rand() == 0x8A8592F5817ED872U);
    assert(mt19937_rand(&mt32) == 0xF5CA0EDBU);
    assert(mt19937_64_rand(&mt64) == 0x8A8592F5817ED872U);
}

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    tests();
}
