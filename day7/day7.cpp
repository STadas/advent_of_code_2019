#include "IntComputer.cpp"
int main()
{
    int from = 5, to = 10;
    int maximum = 0;
    /*  
    please don't bully me for this mess of picking out valid phases.
    at the time of writing this i simply could not be bothered to
    figure out a better alternative and it's already fast enough
    */
    for (int i = from; i < to; i++)
        for (int j = from; j < to; j++)
            if (j != i)
                for (int k = from; k < to; k++)
                    if (k != i && k != j)
                        for (int l = from; l < to; l++)
                            if (l != i && l != j && l != k)
                                for (int m = from; m < to; m++)
                                    if (m != i && m != j && m != k && m != l)
                                    {
                                        std::vector<int> op[5];
                                        int phases[5] = {i, j, k, l, m};
                                        int in[2] = {0, 0};
                                        in[0] = phases[0];
                                        int out;
                                        int n = 0;
                                        int it[5] = {0, 0, 0, 0, 0};
                                        while (true)
                                        {
                                            try
                                            {
                                                int_computer("input", in, out, op[n % 5], it[n % 5]);
                                            }
                                            catch (int e)
                                            {
                                                if (e == 5)
                                                    break;
                                            }
                                            n++;
                                            if (n < 5)
                                            {
                                                in[0] = phases[n];
                                                in[1] = out;
                                            }
                                            else
                                                in[0] = out;
                                        }
                                        if (maximum < out)
                                            maximum = out;
                                    }
    std::cout << maximum << std::endl;
}