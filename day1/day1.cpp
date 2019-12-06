#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
using bigint_t = boost::multiprecision::int256_t;
int main()
{
    std::ifstream file;
    bigint_t sum1 = 0;
    bigint_t sum2 = 0;
    bool first = true;
    file.open("bigboi1");
    while (!file.eof())
    {
        bigint_t fuel;
        file >> fuel;
        while (fuel > 0)
        {
            fuel = (fuel / 3);
            fuel -= 2;
            if (fuel > 0)
            {
                sum2 += fuel;
                if (first == true)
                {
                    first = false;
                    sum1 += fuel;
                }
            }
        }
        first = true;
    }
    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;
}