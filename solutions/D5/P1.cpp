#include <iostream> 
#include <string>
#include <vector>
#include <math.h>
#include <sstream>
#include <algorithm>

class stack
{
public:
    std::vector<char> crates;
};

class instruction
{
public:
    int count;
    int origin;
    int destination;
};

class cargo
{
public:
    std::vector<stack> stacks;
    std::vector<instruction> instructions;

    void rearrange()
    {
        for (instruction instruction : instructions)
        {
            std::vector<char> transferCrate;
            std::vector<char>::iterator originEnd = stacks[instruction.origin].crates.end();
            std::vector<char>::iterator destinationEnd = stacks[instruction.destination].crates.end();
            transferCrate.insert(
                transferCrate.end(),
                originEnd - instruction.count,
                originEnd);
            std::reverse(transferCrate.begin(), transferCrate.end());

            stacks[instruction.destination].crates.insert(
                destinationEnd,
                transferCrate.begin(),
                transferCrate.end());
            stacks[instruction.origin].crates.erase(originEnd - instruction.count, originEnd);
        }
    }

    std::string topCrates()
    {
        std::string topCrates = "";
        for (stack stack : stacks)
        {
            topCrates += stack.crates.back();
        }
        return topCrates;
    }
};

void read(cargo& cargo) // Input parsing
{

    std::string tempStr = "";
    char currentCrate;

    std::getline(std::cin, tempStr);
    int stackNum = (tempStr.length() + 1) / 4;
    cargo.stacks.resize(stackNum);

    for (int i = 0; !tempStr.empty(); i++) // Loop for crate parsing
    {
        for (int j = 0; j < stackNum; j++)
        {
            currentCrate = tempStr[(4 * j) + 1];
            if ((currentCrate >= 'A') && (currentCrate <= 'Z'))
            {
                cargo.stacks[j].crates.emplace(cargo.stacks[j].crates.begin(), currentCrate);
            }
        }
        std::getline(std::cin, tempStr);
    }

    for (int j = 0; j < stackNum; j++)
    {
        cargo.stacks[j].crates.emplace(cargo.stacks[j].crates.begin(), '-');
    }

    std::string word;
    int instructions[3];
    std::getline(std::cin, tempStr);

    for (; !tempStr.empty(); std::getline(std::cin, tempStr)) // Loop for instruction parsing
    {
        std::stringstream tempBuf;
        tempBuf << tempStr;
        std::string temp;
        int found;
        for (int j = 0; !tempBuf.eof(); temp = "")
        {
            tempBuf >> temp;
            if (std::stringstream(temp) >> found)
            {
                instructions[j] = found;
                j++;
            }
        }
        cargo.instructions.emplace_back(instruction({instructions[0], instructions[1] - 1, instructions[2] - 1}));
    }
        
}

int main()
{
    std::cout << "Enter your string of the assignment list: \n";
    cargo cargo;
    read(cargo);
    cargo.rearrange();
    std::cout << cargo.topCrates() << "\n";
    return 0;
}