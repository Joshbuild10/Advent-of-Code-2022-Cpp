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
    yourRock = 'X',
    yourPaper = 'Y',
    yourScissors = 'Z',
    win = 6,
    draw = 3,
    lose = 0
};

class roundData
{
public:
    char opponentMove;
    char yourMove;
};

bool operator< ( roundData a, roundData b ) // Function overloading to allow classes to be compared in the map
{
    return std::make_pair(a.opponentMove, a.yourMove) < std::make_pair(b.opponentMove,b.yourMove); 
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
            strBuf >> outputVec[i].yourMove;
        }
        std::getline(std::cin, tmpStr);
    }
}

int calculateScore(std::vector<roundData>& data)
{
    std::map<char, int> shapeScores { { yourRock, 1}, { yourPaper, 2}, { yourScissors, 3} };
    std::map<roundData, int> outcomeTable { 
    { {opponentRock, yourPaper}, win },
    { {opponentPaper, yourScissors}, win },
    { {opponentScissors, yourRock}, win },
    { {opponentRock, yourRock}, draw },
    { {opponentPaper, yourPaper}, draw },
    { {opponentScissors, yourScissors}, draw },
    { {opponentRock, yourScissors}, lose },
    { {opponentPaper, yourRock}, lose },
    { {opponentScissors, yourPaper}, lose }
    };

    int totalScore = 0;
    for (roundData round : data)
    {
        totalScore += shapeScores[round.yourMove] + outcomeTable[round];
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