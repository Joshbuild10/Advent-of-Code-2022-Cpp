#include <iostream> 
#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include <map>
#include <list>

enum Options
{
    opponentRock = 'A',
    opponentPaper = 'B',
    opponentScissors = 'C',
    lose = 'X',
    draw = 'Y',
    win = 'Z',
    yourRock = 1,
    yourPaper = 2,
    yourScissors = 3
};

class roundData
{
public:
    char opponentMove;
    char roundOutcome;
};

bool operator< ( roundData a, roundData b ) // Function overloading to allow classes to be compared in the map
{
    return std::make_pair(a.opponentMove, a.roundOutcome) < std::make_pair(b.opponentMove,b.roundOutcome); 
}

void read(std::vector<roundData>& outputVec) // Input parsing
{

    std::string tmpStr = "";
    std::string tmpArr[2];
    for (int i = -1; !tmpStr.empty() || i == -1; i++)
    {
        std::stringstream strBuf(tmpStr);
        if (i >= 0)
        {
            outputVec.push_back({});
            strBuf >> outputVec[i].opponentMove;
            strBuf >> outputVec[i].roundOutcome;
        }
        std::getline(std::cin, tmpStr);
    }
}

int calculateScore(std::vector<roundData>& data)
{
    std::map<char, int> outcomeTable { { win, 6}, { draw, 3}, { lose, 0} };
    std::map<roundData, int> predictedShape { 
    { {opponentRock, win}, yourPaper },
    { {opponentPaper, win}, yourScissors },
    { {opponentScissors, win}, yourRock },
    { {opponentRock, draw}, yourRock },
    { {opponentPaper, draw}, yourPaper },
    { {opponentScissors, draw}, yourScissors },
    { {opponentRock, lose}, yourScissors },
    { {opponentPaper, lose}, yourRock },
    { {opponentScissors, lose}, yourPaper }
    };

    int totalScore = 0;
    for (roundData round : data)
    {
        totalScore += outcomeTable[round.roundOutcome] + predictedShape[round];
    }
    
    return totalScore;
}
int main()
{
    std::cout << "Enter your string of the strategy guide: \n";
    std::vector<roundData> data = {};
    read(data);
    std::cout << "Your score is: " << calculateScore(data) << "\n";

    return 0;
}