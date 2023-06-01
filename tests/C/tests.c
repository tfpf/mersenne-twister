#include <assert.h>
#include <inttypes.h>
#include <mt19937.h>

/******************************************************************************
 * Test MT19937 in C.
 *****************************************************************************/
void tests(void)
{
    struct mt19937_32_t mt32;
    mt19937_seed32(5489, &mt32);
    struct mt19937_64_t mt64;
    mt19937_seed64(5489, &mt64);

    mt19937_drop32(9999, NULL);
    mt19937_drop32(9999, &mt32);
    mt19937_drop64(9999, NULL);
    mt19937_drop64(9999, &mt64);

    assert(mt19937_rand32(NULL) == 0xF5CA0EDBU);
    assert(mt19937_rand64(NULL) == 0x8A8592F5817ED872U);
    assert(mt19937_rand32(&mt32) == 0xF5CA0EDBU);
    assert(mt19937_rand64(&mt64) == 0x8A8592F5817ED872U);

    for(int i = 0; i < 30000; ++i)
    {
        mt19937_init32(NULL);
        {
            uint32_t modulus = mt19937_rand32(NULL);
            assert(mt19937_uint32(modulus, NULL) < modulus);
            int32_t left = mt19937_rand32(NULL);
            int32_t right = mt19937_rand32(NULL);
            if(left < right)
            {
                int32_t middle = mt19937_span32(left, right, NULL);
                assert(left <= middle && middle < right);
            }
        }
        mt19937_init64(NULL);
        {
            uint64_t modulus = mt19937_rand64(NULL);
            assert(mt19937_uint64(modulus, NULL) < modulus);
            int64_t left = mt19937_rand64(NULL);
            int64_t right = mt19937_rand64(NULL);
            if(left < right)
            {
                int64_t middle = mt19937_span64(left, right, NULL);
                assert(left <= middle && middle < right);
            }
        }
    }
}

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(void)
{
    tests();
}
