void MT19937_SEED(MT19937_WORD seed, MT19937_OBJECT_TYPE *mt)
{
    mt = mt == NULL ? &MT19937_OBJECT : mt;
    if(seed == 0)
    {
        seed = time(NULL) + getpid();
    }
    mt->state[0] = seed;
    for(int i = 1; i < MT19937_STATE_LENGTH; ++i)
    {
        MT19937_WORD shifted = mt->state[i - 1] >> (MT19937_WORD_WIDTH - 2);
        mt->state[i] = MT19937_MULTIPLIER * (mt->state[i - 1] ^ shifted) + i;
    }
    mt->index = MT19937_STATE_LENGTH;
}


// Two loops and one iteration using hard-coded indices (i.e. without modulo
// operations) run faster than one loop using indices with modulo operations.
// To reduce code repetition, I have factored the loop body out.
#ifndef MT19937_TWIST_LOOP_BODY
#define MT19937_TWIST_LOOP_BODY(i, j, k)  \
MT19937_WORD upper = MT19937_MASK_UPPER & mt->state[i];  \
MT19937_WORD lower = MT19937_MASK_LOWER & mt->state[j];  \
MT19937_WORD masked = upper | lower;  \
MT19937_WORD twister = twist[masked & 1];  \
MT19937_WORD twisted = masked >> 1 ^ twister;  \
mt->state[i] = mt->state[k] ^ twisted;
#endif

MT19937_WORD MT19937_RAND(MT19937_OBJECT_TYPE *mt)
{
    mt = mt == NULL ? &MT19937_OBJECT : mt;

    // Twist.
    if(mt->index == MT19937_STATE_LENGTH)
    {
        mt->index = 0;
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
    MT19937_WORD curr = mt->state[mt->index++];
    curr ^= curr >> MT19937_TEMPER_U & MT19937_TEMPER_D;
    curr ^= curr << MT19937_TEMPER_S & MT19937_TEMPER_B;
    curr ^= curr << MT19937_TEMPER_T & MT19937_TEMPER_C;
    curr ^= curr >> MT19937_TEMPER_I;
    return curr;
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


MT19937_REAL_TYPE MT19937_REAL(MT19937_OBJECT_TYPE *mt)
{
    return (MT19937_REAL_TYPE)MT19937_RAND(mt) / MT19937_WORD_MAX;
}


void MT19937_SHUFFLE(void *items, MT19937_WORD num_of_items, size_t size_of_item, MT19937_OBJECT_TYPE *mt)
{
    char *tmp = malloc(size_of_item);
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
