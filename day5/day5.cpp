#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

enum OPCODE
{
    HALT = 99,
    ADD = 1,
    MULT = 2,
    IN = 3,
    OUT = 4,
    JUMP_IF_TRUE = 5,
    JUMP_IF_FALSE = 6,
    LESS_THAN = 7,
    EQUALS = 8
};

int main()
{
    std::ifstream file;
    file.open("input");
    std::vector<int> op = {};
    std::string line;
    while (getline(file, line, ','))
    {
        op.push_back(stoi(line));
    }
    file.close();

    int i = 0;
    while (i < op.size())
    {
        int types = (op[i] - (op[i] % 100)) / 100;
        int value[3] = {0, 0, 0};
        switch (op[i] % 100)
        {
        case HALT: //=============================================
            return 0;
        case ADD: //=============================================
            for (int j = 1; j <= 2; j++)
            {
                int mod = (int)pow(10, j - 1);
                if ((types - (types % mod)) % (int)pow(10, j) == mod)
                {
                    value[j - 1] = op[i + j];
                }
                else
                {
                    value[j - 1] = op[op[i + j]];
                }
            }
            op[op[i + 3]] = value[0] + value[1];
            i += 4;
            break;
        case MULT: //=============================================
            for (int j = 1; j <= 2; j++)
            {
                int mod = (int)pow(10, j - 1);
                if ((types - (types % mod)) % (int)pow(10, j) == mod)
                {
                    value[j - 1] = op[i + j];
                }
                else
                {
                    value[j - 1] = op[op[i + j]];
                }
            }
            op[op[i + 3]] = value[0] * value[1];
            i += 4;
            break;
        case IN: //=============================================
            std::cin >> op[op[i + 1]];
            i += 2;
            break;
        case OUT: //=============================================
            if (types == 1)
            {
                value[0] = op[i + 1];
            }
            else
            {
                value[0] = op[op[i + 1]];
            }
            std::cout << value[0] << std::endl;
            i += 2;
            break;
        case JUMP_IF_TRUE: //=============================================
            for (int j = 1; j <= 2; j++)
            {
                int mod = (int)pow(10, j - 1);
                if ((types - (types % mod)) % (int)pow(10, j) == mod)
                {
                    value[j - 1] = op[i + j];
                }
                else
                {
                    value[j - 1] = op[op[i + j]];
                }
            }
            if (value[0] != 0)
            {
                i = value[1];
            }
            else
            {
                i += 3;
            }
            break;
        case JUMP_IF_FALSE: //=============================================
            for (int j = 1; j <= 2; j++)
            {
                int mod = (int)pow(10, j - 1);
                if ((types - (types % mod)) % (int)pow(10, j) == mod)
                {
                    value[j - 1] = op[i + j];
                }
                else
                {
                    value[j - 1] = op[op[i + j]];
                }
            }
            if (value[0] == 0)
            {
                i = value[1];
            }
            else
            {
                i += 3;
            }
            break;
        case LESS_THAN: //=============================================
            for (int j = 1; j <= 2; j++)
            {
                int mod = (int)pow(10, j - 1);
                if ((types - (types % mod)) % (int)pow(10, j) == mod)
                {
                    value[j - 1] = op[i + j];
                }
                else
                {
                    value[j - 1] = op[op[i + j]];
                }
            }
            if (value[0] < value[1])
            {
                op[op[i + 3]] = 1;
            }
            else
            {
                op[op[i + 3]] = 0;
            }
            i += 4;
            break;
        case EQUALS: //=============================================
            for (int j = 1; j <= 2; j++)
            {
                int mod = (int)pow(10, j - 1);
                if ((types - (types % mod)) % (int)pow(10, j) == mod)
                {
                    value[j - 1] = op[i + j];
                }
                else
                {
                    value[j - 1] = op[op[i + j]];
                }
            }
            if (value[0] == value[1])
            {
                op[op[i + 3]] = 1;
            }
            else
            {
                op[op[i + 3]] = 0;
            }
            i += 4;
            break;
        default: //=============================================
            std::cout << "BAD_OPCODE " << op[i] << std::endl;
            return 0;
        }
    }
    return 0;
}
