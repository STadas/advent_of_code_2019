#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using bigint_t = boost::multiprecision::int256_t;

int opcalc(int noun, int verb)
{
    std::ifstream file;
    std::string filename = "D2P2-RealisticBigBoy";
    file.open(filename);

    if (file.fail())
    {
        std::cout << "BAD_FILE" << std::endl;
        return -1;
    }

    int i = 0;
    std::vector<int> op = {};
    std::string line;

    while (getline(file, line, ','))
    {
        op.push_back(stoll(line));
    }

    op[1] = noun;
    op[2] = verb;

    i = 0;
    while (i < op.size())
    {
        switch (op[i])
        {
        case 99:
            return op[0];
        case 1:
            op[op[i + 3]] = op[op[i + 1]] + op[op[i + 2]];
            break;
        case 2:
            op[op[i + 3]] = op[op[i + 1]] * op[op[i + 2]];
            break;
        default:
            std::cout << "BAD_OPCODE " << op[i] << std::endl;
            return -1;
        }
        i += 4;
    }

    return op[0];
}

int main()
{
    int max = 100;
    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < max; j++)
        {
            //std::cout << ".";
            if (opcalc(i, j) == 19690720)
            {
                std::cout << i << " " << j << " = " << 100 * i + j << std::endl;
                return 0;
            }
        }
    }
    return 0;
}