#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937_seed64(1);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_rand64() << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_real64() << ' ';
    }
    std::cout << '\n';
}
