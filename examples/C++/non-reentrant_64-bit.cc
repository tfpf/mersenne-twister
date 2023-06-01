#include <iostream>
#include <mt19937.h>

int main(void)
{
    mt19937::seed64(1);
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937::rand64() << ' ';
    }
    for(int i = 0; i < 4; ++i)
    {
        std::cout << mt19937::real64() << ' ';
    }
    std::cout << '\n';
}
