#include <iostream>
#include <fstream>
#include <map>

int main()
{
    //P1
    std::ifstream file;
    file.open("input");

    std::string line;
    std::map<std::string, std::string> orbits;

    while (getline(file, line))
    {
        orbits[line.substr(4)] = line.substr(0, 3);
    }

    auto it = orbits.begin();
    std::string temp;
    int amount = 0;

    while (it != orbits.end())
    {
        temp = it->first;
        while (orbits.count(temp) > 0)
        {
            amount++;
            temp = orbits[temp];
        }
        it++;
    }
    std::cout << "PART 1: " << amount << std::endl;

    //P2
    std::map<std::string, int> santaMap;
    temp = orbits["SAN"];
    int santAmount = 1;

    while (orbits.count(temp) > 0)
    {
        temp = orbits[temp];
        santaMap[temp] = santAmount;
        santAmount++;
    }

    int youAmount = 1;
    temp = orbits["YOU"];

    while (santaMap.count(temp) == 0)
    {
        temp = orbits[temp];
        youAmount++;
    }
    std::cout << "PART 2: " << youAmount - 1 + santaMap[temp] << std::endl;
}