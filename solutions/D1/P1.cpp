#include <iostream> 
#include <string>
#include <vector>
#include <cstdint>

void read(std::vector<std::vector<std::string>>& out) // Input parsing
{
    std::string strBuf = "";

    for (int i = 0; !strBuf.empty() || i == 0; i++)
    {
        out.push_back({});
        for (int j = 0; !strBuf.empty(); j++)
        {
            out[i].push_back(strBuf);
            std::getline(std::cin, strBuf);
        }
        std::getline(std::cin, strBuf);
    }
}

int greatestSum(std::vector<std::vector<std::string>>& data)
{
    int greatestSum = 0, tmpSum = 0;
    for (std::vector<std::string> group : data)
    {
        tmpSum = 0;
        for (std::string num : group)
        {
            tmpSum += std::stoi(num);
        }
        greatestSum = tmpSum > greatestSum ? tmpSum : greatestSum;
    }
    return greatestSum;
}
int main()
{
    std::cout << "Enter your string of calorie data: \n";
    std::vector<std::vector<std::string>> data = {};
    read(data);
    std::cout << "The greatest number of calories an elf is carrying is: " << greatestSum(data) << "\n";
    return 0;
}