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
void get_params(int i, std::vector<int> &op, int *value, int modes)
{
    for (int j = 1; j <= 2; j++)
    {
        int mod = (int)pow(10, j - 1);
        if ((modes - (modes % mod)) % (int)pow(10, j) == mod)
            value[j - 1] = op[i + j];
        else
            value[j - 1] = op[op[i + j]];
    }
}
void int_computer(std::string filename, int in[2], int &out, std::vector<int> &op, int &i)
{
    int inCount = 0;
    int virtOut = 0;
    if (op.size() == 0)
    {
        std::ifstream file;
        file.open(filename);
        std::string line;
        while (getline(file, line, ','))
            op.push_back(stoi(line));
        file.close();
    }
    while (i < op.size())
    {
        int modes = (op[i] - (op[i] % 100)) / 100;
        int value[3] = {0, 0, 0};
        switch (op[i] % 100)
        {
        case HALT: // ========================= HALT =========================
            throw 5;
        case ADD: // ========================= ADD =========================
            get_params(i, op, value, modes);
            op[op[i + 3]] = value[0] + value[1];
            i += 4;
            break;
        case MULT: // ========================= MULT =========================
            get_params(i, op, value, modes);
            op[op[i + 3]] = value[0] * value[1];
            i += 4;
            break;
        case IN: // ========================= IN =========================
            op[op[i + 1]] = in[inCount];
            inCount++;
            i += 2;
            break;
        case OUT: // ========================= OUT =========================
            get_params(i, op, value, modes);
            out = value[0];
            i += 2;
            return;
        case JUMP_IF_TRUE: // ========================= JUMP IF TRUE =========================
            get_params(i, op, value, modes);
            if (value[0] != 0)
                i = value[1];
            else
                i += 3;
            break;
        case JUMP_IF_FALSE: // ========================= JUMP IF FALSE =========================
            get_params(i, op, value, modes);
            if (value[0] == 0)
                i = value[1];
            else
                i += 3;
            break;
        case LESS_THAN: // ========================= LESS THAN =========================
            get_params(i, op, value, modes);
            if (value[0] < value[1])
                op[op[i + 3]] = 1;
            else
                op[op[i + 3]] = 0;
            i += 4;
            break;
        case EQUALS: // ========================= EQUALS =========================
            get_params(i, op, value, modes);
            if (value[0] == value[1])
                op[op[i + 3]] = 1;
            else
                op[op[i + 3]] = 0;
            i += 4;
            break;
        default: // ========================= DEFAULT =========================
            std::cout << "BAD_OPCODE " << op[i] << "at_pos " << i << std::endl;
            return;
        }
    }
}