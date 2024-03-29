#include <inttypes.h>
#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    struct mt19937_32_t mt;
    mt19937_seed32(1, &mt);
    for(int i = 0; i < 4; ++i)
    {
        printf("%"PRIu32" ", mt19937_rand32(&mt));
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%lf ", mt19937_real32(&mt));
    }
    printf("\n");
}
