#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937_64_t mt(1);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt.rand64() << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt.real64() << ' ';
    }
    std::cout << '\n';
}
