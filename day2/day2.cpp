#include <iostream>
#include <fstream>
#include <vector>

int opcalc(int noun, int verb, std::vector<int> op)
{
    int i = 0;

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
            /*default:
            std::cout << "BAD_OPCODE " << op[i] << std::endl;
            return -1;*/
        }
        i += 4;
    }

    return op[0];
}

int main()
{
    std::ifstream file;
    std::string filename = "D2P2-RealisticBigBoy";
    file.open(filename);

    if (file.fail())
    {
        std::cout << "BAD_FILE" << std::endl;
        return -1;
    }

    std::vector<int> op = {};
    std::string line;

    while (getline(file, line, ','))
    {
        op.push_back(stoll(line));
    }

    std::cout << "PART 1: " << 100 * 12 + 2 << " = " << opcalc(12, 2, op) << std::endl;
    int max = 100;

    int dir = 1;

    for (int i = max / 2; i < max; i += dir)
    {
        for (int j = max / 2; j < max; j += dir)
        {

            long long calc = opcalc(i, j, op);

            if (calc > 19690720 && i == max / 2)
            {
                std::cout << "DOWN " << i << " " << j << " = " << calc << std::endl;
                dir = -1;
            }
            else if (calc == 19690720)
            {
                std::cout << "PART 2: " << 100 * i + j << " = 19690720" << std::endl;
                file.close();
                return 0;
            }
        }
    }

    file.close();
    return 0;
}