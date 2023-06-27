#include <inttypes.h>
#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    mt19937_seed64(1, NULL);
    for(int i = 0; i < 4; ++i)
    {
        printf("%"PRIu64" ", mt19937_rand64(NULL));
    }
    for(int i = 0; i < 4; ++i)
    {
        printf("%Lf ", mt19937_real64(NULL));
    }
    printf("\n");
}
