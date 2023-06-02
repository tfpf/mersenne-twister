#include <cassert>
#include <cinttypes>
#include <mt19937.h>

/******************************************************************************
 * Test MT19937 in C++.
 *****************************************************************************/
void tests(void)
{
    mt19937_32_t mt32;
    mt19937_64_t mt64;

    mt19937::drop32(9999);
    mt32.drop32(9999);
    mt19937::drop64(9999);
    mt64.drop64(9999);

    assert(mt19937::rand32() == 0xF5CA0EDBU);
    assert(mt19937::rand64() == 0x8A8592F5817ED872U);
    assert(mt32.rand32() == 0xF5CA0EDBU);
    assert(mt64.rand64() == 0x8A8592F5817ED872U);

    mt19937::init32();
    for(int i = 0; i < 30000; ++i)
    {
        std::uint32_t modulus = mt19937::rand32();
        assert(mt19937::uint32(modulus) < modulus);
        std::int32_t left = mt19937::rand32();
        std::int32_t right = mt19937::rand32();
        if(left < right)
        {
            std::int32_t middle = mt19937::span32(left, right);
            assert(left <= middle && middle < right);
        }
    }

    mt19937::init64();
    for(int i = 0; i < 30000; ++i)
    {
        std::uint64_t modulus = mt19937::rand64();
        assert(mt19937::uint64(modulus) < modulus);
        std::int64_t left = mt19937::rand64();
        std::int64_t right = mt19937::rand64();
        if(left < right)
        {
            std::int64_t middle = mt19937::span64(left, right);
            assert(left <= middle && middle < right);
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
