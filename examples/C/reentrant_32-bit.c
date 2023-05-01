#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    struct mt19937_t mt;
    mt19937_seed(1, &mt);
    for(int i = 0; i < 4; ++i)
    {
        printf("%lu ", mt19937_rand(&mt));
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%lf ", mt19937_rand_real(&mt));
    }
    printf("\n");
}
