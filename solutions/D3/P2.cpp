#include <iostream> 
#include <string>
#include <vector>
#include <cstdint>
#include <array>

constexpr int GROUPNUM = 3;

struct group
{
    std::string rucksack[GROUPNUM];
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

void read(std::vector<group>& outputVec) // Input parsing
{

    std::string tempStr[GROUPNUM] = {};
    int midpoint = 0;

    std::getline(std::cin, tempStr[0]);
    for (int i = 1; !tempStr[i - 1].empty(); i++) // Iterates through consecutive lines, and for each line, splits the string in half and stores it
    {
        if (i == GROUPNUM) // Every GROUPNUM lines, add the group to the output
        {
            outputVec.push_back({{tempStr[0], tempStr[1], tempStr[2]}, 0});
            i = 0;
        }
        std::getline(std::cin, tempStr[i]);
    }
}

void findCommonItem(std::vector<group>& groups)
{
    int count = 0;
    for (group& group : groups)
    {
        bool frequencies[GROUPNUM][54] = { 0 };
        for (int i = 0; i < GROUPNUM; i++) // Marks occurance of each item in each elves' sack
        {
            for (char item : group.rucksack[i])
            {
                frequencies[i][charToPriority(item) - 1] = true;
            }
        }
    
        for (int j = 0; j < 54; j++) // Iterates over possible items
        {
            count = 0;
            for (int i = 0; i < GROUPNUM; i++) { count += frequencies[i][j]; } // Counts the occurance the item in a group
            if (count == GROUPNUM) // If an item appears in all the sacks make it the common item
            {
                group.commonItem = priorityToChar(j + 1);
                break;
            }
        }
    }
}

int sumOfPriorities(std::vector<group>& groups)
{
    int sum = 0;
    for (group group : groups)
    {
        sum += charToPriority(group.commonItem);
    }
    return sum;
}

int main()
{
    std::cout << "Enter your string of the strategy guide: \n";
    std::vector<group> groups = {}; // Each element stores the rucksack data for each group
    read(groups);
    findCommonItem(groups);
    std::cout << "The sum of priorities is: " << sumOfPriorities(groups) << "\n";

    return 0;
}