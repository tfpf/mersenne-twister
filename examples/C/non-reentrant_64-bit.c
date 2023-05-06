#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    mt19937_seed64(1);
    for(int i = 0; i < 4; ++i)
    {
        printf("%llu ", mt19937_rand64());
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%Lf ", mt19937_real64());
    }
    printf("\n");
}
