#include <iostream>
#include <iomanip>
#include <vector>

//#include <boost/multiprecision/cpp_int.hpp>
//using bigint_t = boost::multiprecision::int256_t;

int part_1(int minNum, int maxNum)
{
	int diff = maxNum - minNum;
	int count = 0;

	printf("%d, %d", minNum, diff);
	printf("\n");

	std::vector<std::string> numArr;

	for (int i = 0; i <= diff; i++)
	{
		numArr.push_back(std::to_string(minNum + i));

		bool repeat = false;
		bool inc = true;

		for (int j = 0; j < numArr[i].length(); j++)
		{
			if (j < numArr[i].length() - 1)
			{
				if (numArr[i][j] == numArr[i][j + 1])
				{
					repeat = true;
				}

				int comp1 = (char)numArr[i][j] - '0';
				int comp2 = (char)numArr[i][j + 1] - '0';

				if (comp1 > comp2)
				{
					inc = false;
					break;
				}
			}
		}
		if (repeat && inc)
		{
			count++;
		}
	}

	return count;
}

int part_2(int minNum, int maxNum)
{
	int diff = maxNum - minNum;
	int count = 0;

	printf("%d, %d", minNum, diff);
	printf("\n");

	std::vector<std::string> numArr;

	for (int i = 0; i <= diff; i++)
	{
		numArr.push_back(std::to_string(minNum + i));

		bool repeat = false;
		bool inc = true;
		int repCount = 0;

		for (int j = 0; j < numArr[i].length(); j++)
		{
			if (j < numArr[i].length() - 1)
			{
				if (numArr[i][j] - '0' == numArr[i][j + 1] - '0')
				{
					repCount++;
					if (j + 2 == numArr[i].length() && repCount == 1)
					{
						repeat = true;
					}
				}
				else if (repCount == 1)
				{
					repeat = true;
					repCount = 0;
				}
				else
				{
					repCount = 0;
				}

				int comp1 = numArr[i][j] - '0';
				int comp2 = numArr[i][j + 1] - '0';

				if (comp1 > comp2)
				{
					inc = false;
					break;
				}
			}
		}
		if (repeat && inc)
		{
			count++;
		}
	}

	return count;
}

int main()
{
	int minNum = 245182;
	int maxNum = 790572;

	printf("PART 1: %d", part_1(minNum, maxNum));
	printf("\n");

	printf("PART 2: %d", part_2(minNum, maxNum));
	printf("\n");

	return 0;
}