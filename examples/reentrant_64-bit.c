#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    struct mt19937_64_t mt;
    mt19937_64_seed(1, &mt);
    for(int i = 0; i < 4; ++i)
    {
        printf("%llu ", mt19937_64_rand(&mt));
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%lf ", mt19937_64_rand_real(&mt));
    }
    printf("\n");
}
