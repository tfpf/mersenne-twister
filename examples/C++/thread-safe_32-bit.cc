#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937_32_t mt(1);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt.rand32() << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt.real32() << ' ';
    }
    std::cout << '\n';
}
