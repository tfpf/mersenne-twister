#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    struct mt19937_64_t mt;
    mt19937_seed64(1, &mt);
    for(int i = 0; i < 4; ++i)
    {
        printf("%llu ", mt19937_rand64(&mt));
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%Lf ", mt19937_real64(&mt));
    }
    printf("\n");
}
