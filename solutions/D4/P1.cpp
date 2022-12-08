#include <iostream> 
#include <string>
#include <vector>
#include <cstdint>
#include <array>

struct assignment
{
    int start;
    int stop;
};
class assignmentPair
{
public:
    assignment assignment[2];

    bool containsSubset()
    {
        return (
            (assignment[0].start <= assignment[1].start && assignment[0].stop >= assignment[1].stop)
            || (assignment[1].start <= assignment[0].start && assignment[1].stop >= assignment[0].stop))
            ? 1 : 0;
    }
};
void read(std::vector<assignmentPair>& outputVec) // Input parsing
{

    std::string token, token2, tempStr = "",  elfDelim = ",", rangeDelim = "-";
    size_t pos, pos2;

    std::getline(std::cin, tempStr);
    for (int i = 0; !tempStr.empty(); i++)
    {       
        outputVec.push_back({});

        tempStr += elfDelim;
        int j = 0;
        while ((pos = tempStr.find(elfDelim)) != std::string::npos) 
        {
            token = tempStr.substr(0, pos) + rangeDelim;
            tempStr.erase(0, pos + elfDelim.length());

            pos2 = token.find(rangeDelim);
            token2 = token.substr(0, pos2);
            token.erase(0, pos2 + rangeDelim.length());
            outputVec[i].assignment[j].start = stoi(token2);

            pos2 = token.find(rangeDelim);
            token2 = token.substr(0, pos2);
            token.erase(0, pos2 + rangeDelim.length());
            outputVec[i].assignment[j].stop = stoi(token2);

            j++;
        }

        std::getline(std::cin, tempStr);
    }
}

int redundancyCount(std::vector<assignmentPair> assignments)
{
    int sum = 0;
    for (assignmentPair assignment : assignments)
    {
        sum += assignment.containsSubset();
    }
    return sum;
}

int main()
{
    std::cout << "Enter your string of the assignment list: \n";
    std::vector<assignmentPair> data = {}; // Each element stores each half of the string
    read(data);
    std::cout << "The number of redundant assignments are: " << redundancyCount(data) << "\n";

    return 0;
}