#include <iostream>
#include <fstream>
#include <cmath>

int main()
{
    std::ifstream file;
    file.open("input1");

    long sum = 0;

    while (!file.eof())
    {
        long fuel;
        file >> fuel;
        while (fuel > 0) //p2
        {
            //p1
            fuel = (fuel / 3);
            fuel -= 2;
            if (fuel > 0)
            {
                sum += fuel;
            }
        }
    }
    std::cout << sum << std::endl;
}