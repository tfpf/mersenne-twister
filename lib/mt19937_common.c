// This file is not supposed to be used directly. It will be included by
// another file after all tokens used here have been defined.


void mt19937_seed(MT19937_WORD seed)
{
    if(seed == 0)
    {
        seed = time(NULL) + getpid();
    }
    mt19937.state[0] = seed;
    for(int i = 1; i < MT19937_STATE_LENGTH; ++i)
    {
        MT19937_WORD shifted = mt19937.state[i - 1] >> (MT19937_WORD_WIDTH - 2);
        mt19937.state[i] = MT19937_MULTIPLIER * (mt19937.state[i - 1] ^ shifted) + i;
    }
    mt19937.index = MT19937_STATE_LENGTH;
}


// Two loops and one iteration using hard-coded indices (i.e. without modulo
// operations) run faster than one loop using indices with modulo operations.
// To reduce code repetition, I have factored the loop body out.
#ifndef MT19937_TWIST_LOOP_BODY
#define MT19937_TWIST_LOOP_BODY(i, j, k)  \
MT19937_WORD upper = MT19937_MASK_UPPER & mt19937.state[i];  \
MT19937_WORD lower = MT19937_MASK_LOWER & mt19937.state[j];  \
MT19937_WORD masked = upper | lower;  \
MT19937_WORD twisted = masked >> 1 ^ twist[masked & 1];  \
mt19937.state[i] = mt19937.state[k] ^ twisted;
#endif

MT19937_WORD mt19937_rand(void)
{
    // Twist.
    if(mt19937.index == MT19937_STATE_LENGTH)
    {
        mt19937.index = 0;
        static MT19937_WORD const twist[] = {0, MT19937_MASK_TWIST};
        for(int i = 0; i < MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; ++i)
        {
            MT19937_TWIST_LOOP_BODY(i, i + 1, i + MT19937_STATE_MIDDLE)
        }
        for(int i = MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; i < MT19937_STATE_LENGTH - 1; ++i)
        {
            MT19937_TWIST_LOOP_BODY(i, i + 1, i + MT19937_STATE_MIDDLE - MT19937_STATE_LENGTH)
        }
        MT19937_TWIST_LOOP_BODY(MT19937_STATE_LENGTH - 1, 0, MT19937_STATE_MIDDLE - 1)
    }

    // Generate.
    MT19937_WORD curr = mt19937.state[mt19937.index++];
    curr ^= (curr >> MT19937_TEMPER_U) & MT19937_TEMPER_D;
    curr ^= (curr << MT19937_TEMPER_S) & MT19937_TEMPER_B;
    curr ^= (curr << MT19937_TEMPER_T) & MT19937_TEMPER_C;
    curr ^= curr >> MT19937_TEMPER_I;
    return curr;
}


MT19937_WORD mt19937_rand_integer(MT19937_WORD modulus)
{
    MT19937_WORD upper = MT19937_WORD_MAX - MT19937_WORD_MAX % modulus;
    MT19937_WORD r;
    do
    {
        r = mt19937_rand();
    }
    while(r >= upper);
    return r % modulus;
}


double mt19937_rand_real(void)
{
    return (double)mt19937_rand() / MT19937_WORD_MAX;
}
