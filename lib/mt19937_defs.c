void MT19937_SEED(MT19937_WORD seed, MT19937_OBJECT_TYPE *mt)
{
    mt = mt == NULL ? &MT19937_OBJECT : mt;
    mt->state[0] = seed;
    for(int i = 1; i < MT19937_STATE_LENGTH; ++i)
    {
        // Unsigned overflow is defined behaviour.
        MT19937_WORD shifted = mt->state[i - 1] >> (MT19937_WORD_WIDTH - 2);
        mt->state[i] = MT19937_MULTIPLIER * (mt->state[i - 1] ^ shifted) + i;
    }
    mt->index = MT19937_STATE_LENGTH;
}


void MT19937_INIT(MT19937_OBJECT_TYPE *mt)
{
    MT19937_SEED(time(NULL) + (uintptr_t)&mt, mt);
}


/******************************************************************************
 * Execute one iteration of the twist loop of MT19937.
 *
 * Factoring out the loop body like this allows partially unrolling the loop,
 * thereby eliminating modulo operations in the calculation of indices. As a
 * result, the code runs faster.
 *
 * Another optimisation worth noting is the calculation of `mask`: if `lower`
 * is odd, `MT19937_MASK_TWIST` must be XORed with the result, but not
 * otherwise. This can be accomplished with branch or load instructions.
 * However, it is faster to copy the LSB of `lower` into all of its other bit
 * positions. I did this by negating it. (The C standard requires that unsigned
 * integer types use pure binary representation. It also states that assigning
 * a negative value to an unsigned type causes wrap-around. Effectively, if
 * `lower` is odd, `mask` has all bits set, otherwise it has all bits cleared.
 * Hence, this code does not invoke implementation-defined behaviour.) Indeed,
 * GCC and Clang calculate `mask` using a `neg` instruction, which is
 * consistent with the above.
 *
 * The first optimisation is due to the original authors of MT19937. The second
 * (though inspired by the optimisation in C. S. Larsen's code) is my own idea.
 *****************************************************************************/
#ifndef MT19937_TWIST_LOOP_BODY
#define MT19937_TWIST_LOOP_BODY(i, j, k)  \
MT19937_WORD upper = MT19937_MASK_UPPER & mt->state[i];  \
MT19937_WORD lower = MT19937_MASK_LOWER & mt->state[j];  \
MT19937_WORD combo = upper | lower;  \
MT19937_WORD mask = -(lower & 1);  \
MT19937_WORD twisted = combo >> 1 ^ (mask & MT19937_MASK_TWIST);  \
mt->state[i] = mt->state[k] ^ twisted;
#endif

MT19937_WORD MT19937_RAND(MT19937_OBJECT_TYPE *mt)
{
    mt = mt == NULL ? &MT19937_OBJECT : mt;
    if(mt->index == MT19937_STATE_LENGTH)
    {
        // Twist.
        mt->index = 0;
        for(int i = 0; i < MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; ++i)
        {
            MT19937_TWIST_LOOP_BODY(i, i + 1, i + MT19937_STATE_MIDDLE)
        }
        for(int i = MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; i < MT19937_STATE_LENGTH - 1; ++i)
        {
            MT19937_TWIST_LOOP_BODY(i, i + 1, i + MT19937_STATE_MIDDLE - MT19937_STATE_LENGTH)
        }
        MT19937_TWIST_LOOP_BODY(MT19937_STATE_LENGTH - 1, 0, MT19937_STATE_MIDDLE - 1)

        // Generate.
        for(int i = 0; i < MT19937_STATE_LENGTH; ++i)
        {
            MT19937_WORD curr = mt->state[i];
            curr ^= curr >> MT19937_TEMPER_U & MT19937_TEMPER_D;
            curr ^= curr << MT19937_TEMPER_S & MT19937_TEMPER_B;
            curr ^= curr << MT19937_TEMPER_T & MT19937_TEMPER_C;
            curr ^= curr >> MT19937_TEMPER_I;
            mt->value[i] = curr;
        }
    }
    return mt->value[mt->index++];
}


MT19937_WORD MT19937_UINT(MT19937_WORD modulus, MT19937_OBJECT_TYPE *mt)
{
    MT19937_WORD upper = MT19937_WORD_MAX - MT19937_WORD_MAX % modulus;
    MT19937_WORD r;
    do
    {
        r = MT19937_RAND(mt);
    }
    while(r >= upper);
    return r % modulus;
}


MT19937_WORD_SIGNED MT19937_SPAN(MT19937_WORD_SIGNED left, MT19937_WORD_SIGNED right, MT19937_OBJECT_TYPE *mt)
{
    // Signed exact-width integer types are required to use two's complement
    // representation. This code will always work.
    MT19937_WORD uleft = (MT19937_WORD)left;
    MT19937_WORD uright = (MT19937_WORD)right;
    MT19937_WORD modulus = uright - uleft;
    MT19937_WORD r = MT19937_UINT(modulus, mt);
    return (MT19937_WORD_SIGNED)(r + uleft);
}


MT19937_REAL_TYPE MT19937_REAL(MT19937_OBJECT_TYPE *mt)
{
    return (MT19937_REAL_TYPE)MT19937_RAND(mt) / MT19937_WORD_MAX;
}


void MT19937_SHUF(void *items, MT19937_WORD num_of_items, size_t size_of_item, MT19937_OBJECT_TYPE *mt)
{
    // C++ does not implicitly convert `void *`, so a cast is necessary,
    // because I want to allow users to include this file directly in a C or
    // C++ program.
    char *tmp = (char *)malloc(size_of_item);
    char *items_ = (char *)items;
    for(MT19937_WORD i = num_of_items - 1; i > 0; --i)
    {
        MT19937_WORD j = MT19937_UINT(i + 1, mt);
        if(i != j)
        {
            char *items_i = items_ + i * size_of_item;
            char *items_j = items_ + j * size_of_item;
            memcpy(tmp, items_i, size_of_item);
            memcpy(items_i, items_j, size_of_item);
            memcpy(items_j, tmp, size_of_item);
        }
    }
    free(tmp);
}


void MT19937_DROP(int long long count, MT19937_OBJECT_TYPE *mt)
{
    while(count-- > 0)
    {
        MT19937_RAND(mt);
    }
}
