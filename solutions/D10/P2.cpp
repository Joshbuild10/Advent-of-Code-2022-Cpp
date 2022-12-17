#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
class instruction
{
public:
    std::string command;
    int count = 0;
    instruction(std::string line)
    {
        std::stringstream ss(line);
        ss >> command;
        if (command == "addx") { ss >> count; }
    }
};
void read(std::vector<instruction>& instructions) // Input parsing
{

    std::string tempStr = "";

    std::getline(std::cin, tempStr);

    for (int i = 0; !tempStr.empty(); i++) // Loop for crate parsing
    {
        instructions.push_back(instruction(tempStr));
        std::getline(std::cin, tempStr);
    }
}
void printImage(std::vector<instruction>& instructions)
{
    int reg = 1;
    int strengthSum = 0;
    int column = 0;
    int curIndex = 0;
    std::string screen[6];
    for (instruction instruction : instructions)
    {
        if ((curIndex == 40) && (curIndex > 0)) { column++; screen[column] = ""; curIndex = 0; }
        screen[column] += (curIndex >= reg - 1) && (curIndex <= reg + 1) ? "#" : ".";
        if (instruction.command == "noop")
        {
            ++curIndex;
        }
        if (instruction.command == "addx")
        {
            ++curIndex;
            if ((curIndex == 40) && (curIndex > 0)) { column++; screen[column] = ""; curIndex = 0; }
            screen[column] += (curIndex >= reg - 1) && (curIndex <= reg + 1) ? "#" : ".";
            ++curIndex;
            reg += instruction.count;
        }
    }
    for (std::string line : screen)
    {
        std::cout << line << "\n";
    }
}
int main()
{
    std::cout << "Enter your instructions: \n";
    std::vector<instruction> instructions;
    read(instructions);
    printImage(instructions);
    return 0;
}