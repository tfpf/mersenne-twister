#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937_t mt;
    mt19937_seed(1, &mt);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_rand(&mt) << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_rand_real(&mt) << ' ';
    }
    std::cout << '\n';
}
