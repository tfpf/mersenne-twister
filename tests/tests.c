#include <assert.h>
#include <inttypes.h>
#include <mt19937.h>
#include <stdbool.h>
#include <stdio.h>

/******************************************************************************
 * Test MT19937. The results of this implementation must match those of a C++
 * standard library implementation. See
 * https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.
 * @{
 *****************************************************************************/
void test_mt19937(void)
{
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_rand();
    }
    uint32_t r = mt19937_rand();
    assert(r == 0xF5CA0EDBU);
}
void test_mt19937_64(void)
{
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_64_rand();
    }
    uint64_t r = mt19937_64_rand();
    assert(r == 0x8A8592F5817ED872U);
}
/******************************************************************************
 * @}
 *****************************************************************************/

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    test_mt19937();
    test_mt19937_64();
}
