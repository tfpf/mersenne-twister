#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937_seed(1);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_rand() << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_rand_real() << ' ';
    }
    std::cout << '\n';
}
