#include <stdbool.h>
#include <stdio.h>

#include "mt19937.h"
#include "mt19937_64.h"

/******************************************************************************
 * Test MT19937. The results of this implementation must match those of a C++
 * standard library implementation. See
 * https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.
 * @{
 *****************************************************************************/
bool test_mt19937(void)
{
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_rand();
    }
    return mt19937_rand() == 0xF5CA0EDBU;
}
bool test_mt19937_64(void)
{
    for(int i = 1; i < 10000; ++i)
    {
        mt19937_64_rand();
    }
    return mt19937_64_rand() == 0x8A8592F5817ED872U;
}
/******************************************************************************
 * @}
 *****************************************************************************/

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    if(!test_mt19937())
    {
        fprintf(stderr, "32-bit MT19937 not working as expected.\n");
    }
    if(!test_mt19937_64())
    {
        fprintf(stderr, "64-bit MT19937 not working as expected.\n");
    }
}
