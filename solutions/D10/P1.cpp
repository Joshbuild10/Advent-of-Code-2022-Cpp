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
int sumOfStrengths(std::vector<instruction>& instructions)
{
    int curCycle = 1;
    int reg = 1;
    int strengthSum = 0;

    for (instruction instruction : instructions)
    {
        if (((curCycle % 40) == 20) && (curCycle <= 220)) { strengthSum += curCycle * reg; }
        if (instruction.command == "noop")
        {
            ++curCycle;
        }
        if (instruction.command == "addx")
        {
            ++curCycle;
            if (((curCycle % 40) == 20) && (curCycle <= 220)) { strengthSum += curCycle * reg; }
            ++curCycle;
            reg += instruction.count;
        }
    }
    return strengthSum;
}
int main()
{
    std::cout << "Enter your instructions: \n";
    std::vector<instruction> instructions;
    read(instructions);
    std::cout << "The sum of signal strengths are: " << sumOfStrengths(instructions) << "\n";
    return 0;
}