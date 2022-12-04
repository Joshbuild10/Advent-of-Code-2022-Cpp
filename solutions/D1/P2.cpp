#include <iostream> 
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <numeric>

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

std::vector<int> greatestSums(std::vector<std::vector<std::string>>& data, int count)
{
    int tmpSum = 0;
    std::vector<int> intDat(data.size());
    std::vector<int> sums(count); // Stores the largest 3 sums

    for (std::vector<std::string> group : data) // Converts the strings data to their integer equivalents
    {
        tmpSum = 0;
        for (std::string num : group) { tmpSum += std::stoi(num); }
        intDat.push_back(tmpSum);
    }

    for (int i = 0; i < count; i++)
    {
        sums[i] = *std::max_element(intDat.begin(), intDat.end());
        intDat.erase(std::remove(intDat.begin(), intDat.end(), sums[i]), intDat.end());
    }
    return sums;
}
int main()
{
    std::vector<std::vector<std::string>> data = {};
    std::cout << "Enter your string of calorie data: \n";
    read(data);

    std::vector<int> sums = greatestSums(data, 3);
    int total = std::reduce(sums.begin(), sums.end()); // Gets the sum of elements in the vector

    std::cout << "The greatest number of calories an elf is carrying is: " << total << "\n";

    return 0;
}