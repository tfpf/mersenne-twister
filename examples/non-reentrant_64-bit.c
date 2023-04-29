#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    mt19937_64_seed(1);
    for(int i = 0; i < 4; ++i)
    {
        printf("%llu ", mt19937_64_rand());
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%lf ", mt19937_64_rand_real());
    }
    printf("\n");
}
