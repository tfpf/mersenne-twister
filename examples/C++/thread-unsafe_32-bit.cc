#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937::seed32(1);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937::rand32() << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937::real32() << ' ';
    }
    std::cout << '\n';
}
