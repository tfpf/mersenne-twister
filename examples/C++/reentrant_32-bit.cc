#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937_32_t mt;
    mt19937_seed32(1, &mt);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_rand32(&mt) << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_real32(&mt) << ' ';
    }
    std::cout << '\n';
}
