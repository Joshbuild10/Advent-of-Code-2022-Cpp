#include <iostream> 
#include <string>
#include <vector>
#include <cstdint>
#include <array>

struct compartments
{
    std::string rucksack[2];
    char commonItem;
};

inline short charToPriority(char letter) // Returns the priority of a given letter (maps 'a'-'z' 1-26 and 'A'-'Z' 27-52)
{
    return (letter <= 'Z') ? letter - 'A' + 27: letter - 'a' + 1;
}
inline char priorityToChar(short priority) // Returns the character associated with a given priority (maps 'a'-'z' 1-26 and 'A'-'Z' 27-52)
{
    return (priority <= 26) ? priority - 1 + 'a': priority - 27 + 'A';
}

void read(std::vector<compartments>& outputVec) // Input parsing
{

    std::string tempStr = "";
    int midpoint = 0;

    std::getline(std::cin, tempStr);
    for (int i = 0; !tempStr.empty(); i++) // Iterates through consecutive lines, and for each line, splits the string in half and stores it
    {        
        midpoint = tempStr.length() * 0.5;
        outputVec.push_back({tempStr.substr(0, midpoint), tempStr.substr(midpoint, midpoint), 0});
        std::getline(std::cin, tempStr);
    }
}

void findCommonItem(std::vector<compartments>& rucksackItems)
{
    for (compartments& compartment : rucksackItems)
    {
        bool frequencies[2][54] = { 0 };
        for (int i = 0; i < 2; i++) // Marks occurance of each item in each sack
        {
            for (char item : compartment.rucksack[i])
            {
                frequencies[i][charToPriority(item) - 1] = true;
            }
        }
    
        for (int j = 0; j < 54; j++) // Iterates over possible items
        {
            if (frequencies[0][j] && frequencies[1][j]) // If an item appears in both sacks make it the common item
            {
                compartment.commonItem = priorityToChar(j + 1);
                break;
            }
        }
    }
}

int sumOfPriorities(std::vector<compartments>& rucksackItems)
{
    int sum = 0;
    for (compartments compartment : rucksackItems)
    {
        sum += charToPriority(compartment.commonItem);
    }
    return sum;
}

int main()
{
    std::cout << "Enter your string of the strategy guide: \n";
    std::vector<compartments> data = {}; // Each element stores each half of the string
    read(data);
    findCommonItem(data);
    std::cout << "The sum of priorities is: " << sumOfPriorities(data) << "\n";

    return 0;
}