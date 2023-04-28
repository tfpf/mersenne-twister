#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    mt19937_seed(1);
    for(int i = 0; i < 4; ++i)
    {
        printf("%lu ", mt19937_rand());
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%lf ", mt19937_rand_real());
    }
    printf("\n");
}
