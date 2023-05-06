#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937_64_t mt;
    mt19937_seed64(1, &mt);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_rand64(&mt) << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937_real64(&mt) << ' ';
    }
    std::cout << '\n';
}
