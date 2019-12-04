#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
//#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
//using bigint_t = boost::multiprecision::int256_t;

struct Coords
{
	int x;
	int y;
};

vector<vector<string>> get_input()
{

	ifstream file;

	file.open("short1");

	vector<vector<string>> vect2d = {};
	vector<string> lineVect = {};
	string line;

	while (!file.eof())
	{
		getline(file, line);
		//cout << line << endl;
		lineVect.push_back(line);
	}

	long long pos = 0;
	string token;

	for (int i = 0; i < lineVect.size(); i++)
	{
		vector<string> tokens;
		while ((pos = lineVect[i].find(',')) != string::npos)
		{
			token = lineVect[i].substr(0, pos);
			tokens.push_back(token);
			lineVect[i].erase(0, pos + 1);
		}
		vect2d.push_back(tokens);
	}

	file.close();

	cout << "get_compl" << endl;

	return vect2d;
}

vector<vector<Coords>> make_grid(vector<vector<string>> moves)
{

	vector<vector<Coords>> grid = {};

	for (int i = 0; i < moves.size(); i++)
	{
		vector<Coords> emptyVec;
		grid.push_back(emptyVec);
		int x = 0;
		int y = 0;

		for (int j = 0; j < moves[i].size(); j++)
		{
			string instr = moves[i][j];

			string amountStr = "";
			for (int k = 1; k < instr.length(); k++)
			{
				amountStr += string() + instr[k];
			}
			int amount = stoi(amountStr);

			switch (instr[0])
			{
			case 'U':
				for (int k = 1; k <= amount; k++)
				{
					//cout << x << " " << y + k << endl;
					Coords tempC = {x, y + k};
					grid[i].push_back(tempC);
				}
				y += amount;
				break;
			case 'D':
				for (int k = 1; k <= amount; k++)
				{
					//cout << x << " " << y - k << endl;
					Coords tempC = {x, y - k};
					grid[i].push_back(tempC);
				}
				y -= amount;
				break;
			case 'R':
				for (int k = 1; k <= amount; k++)
				{
					//cout << x + k << " " << y << endl;
					Coords tempC = {x + k, y};
					grid[i].push_back(tempC);
				}
				x += amount;
				break;
			case 'L':
				for (int k = 1; k <= amount; k++)
				{
					//cout << x + k << " " << y << endl;
					Coords tempC = {x - k, y};
					grid[i].push_back(tempC);
				}
				x -= amount;
				break;
			}
		}
	}

	cout << "make_compl" << endl;

	return grid;
}

int distance_function(Coords coords)
{
	return fabs(coords.x) + fabs(coords.y);
}

void find_closest(vector<vector<Coords>> grid)
{
	Coords shortestCoords;
	int closestDist = 0;
	shortestCoords.x = 0;
	shortestCoords.y = 0;

	for (int i = 0; i < grid[0].size(); i++)
	{
		for (int j = 0; j < grid[1].size(); j++)
		{
			if (grid[0][i].x != 0 || grid[0][i].y != 0)
			{
				if (grid[0][i].x == grid[1][j].x && grid[0][i].y == grid[1][j].y)
				{
					int dist = distance_function(grid[0][i]);
					if (closestDist > dist || closestDist == 0)
					{
						closestDist = dist;
						shortestCoords.x = grid[0][i].x;
						shortestCoords.y = grid[0][i].y;

						continue;
					}
				}
				if (closestDist > 0)
				{
					if (distance_function(grid[1][j]) > closestDist)
					{
						grid[1].erase(grid[1].begin() + j);
						j--;
					}
					if (distance_function(grid[0][i]) > closestDist)
					{
						grid[0].erase(grid[0].begin() + i);
						i--;
						break;
					}
				}
			}
			else
			{
				if (grid[1][j].x == 0 && grid[1][j].y == 0)
				{
					grid[1].erase(grid[1].begin() + j);
					j--;
				}
				if (grid[0][i].x == 0 && grid[0][i].y == 0)
				{
					grid[0].erase(grid[0].begin() + i);
					i--;
					break;
				}
			}
		}
	}
	cout << "PART 1:" << closestDist << endl;
}

int getSteps(vector<vector<Coords>> grid, int i, int which)
{
	int steps = 0;
	for (int j = i; j > 0; j--)
	{
		for (int k = j; j > k; k--)
		{
			if (grid[which][j].x == grid[which][k].x && grid[which][j].y == grid[which][k].y)
			{
				steps += getSteps(grid, j, which);
			}
		}
		steps++;
	}
	return steps;
}

void find_shortest(vector<vector<Coords>> grid)
{
	int steps1 = 0;
	int steps2 = 0;
	int shortest = 0;

	for (int i = 1; i < grid[0].size(); i++)
	{
		cout << steps1 << endl;

		cout << grid[0][i].x << " ; " << grid[0][i].y << endl;
		for (int j = 1; j < grid[1].size(); j++)
		{
			if (grid[0][i].x != 0 || grid[0][i].y != 0)
			{
				if (grid[0][i].x == grid[1][j].x && grid[0][i].y == grid[1][j].y)
				{
					steps1 = getSteps(grid, i, 0);
					steps1 = getSteps(grid, j, 1);
					if (shortest > steps1 + steps2 || shortest == 0)
					{
						shortest = steps1 + steps2;
					}
				}
			}
		}
	}

	cout << "PART 2: " << shortest << endl;
}

int main()
{
	vector<vector<Coords>> grid = make_grid(get_input());

	//find_closest(grid);

	find_shortest(grid);

	return 0;
}