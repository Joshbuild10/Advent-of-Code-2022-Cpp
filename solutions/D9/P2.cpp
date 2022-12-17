#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <set>

class coordinate
{
public:
    int x, y;
    coordinate()
    {
        x = 0; y = 0;
    }
    coordinate(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }
};

class instruction
{
public:
    coordinate directionModifier;
    int number;
    instruction(std::string& line)
    {
        std::map<char, coordinate> directionMap {
        { 'L', {-1,0} },
        { 'R', {1,0} },
        { 'U', {0,1} },
        { 'D', {0,-1} } };
        directionModifier = directionMap[line[0]];
        number = stoi(line.substr(2));
    }
};


coordinate operator- ( coordinate a, coordinate b )
{
    return {a.x-b.x, a.y-b.y}; 
}

coordinate operator+ ( coordinate a, coordinate b ) 
{
    return {a.x+b.x, a.y+b.y}; 
} 
void operator+= ( coordinate &a, coordinate b ) 
{
    a = a + b; 
}

bool operator< ( coordinate a, coordinate b ) // Function overloading to allow classes to be compared in the map
{
    return std::make_pair(a.x, a.y) < std::make_pair(b.x,b.y); 
}

// Map containing values for what to move to make depending on the difference between head and tail
/*std::map<coordinate, coordinate> move {
{ {2,2}, {1, 1}},
{ {-2,-2}, {-1, -1}},
{ {2,-2}, {1,-1}},
{ {-2,2}, {-1,1}},
{ {2,0}, {1,0} },
{ {-2,0}, {-1,0} },
{ {0,2}, {0,1} },
{ {0,-2}, {0,-1} },
{ {2,1}, {1,1} },
{ {1,2}, {1,1} },
{ {2,-1}, {1,-1} },
{ {1,-2}, {1,-1} },
{ {-2,1}, {-1,1} },
{ {-1, 2}, {-1,1} },
{ {-2,-1}, {-1,-1} },
{ {-1,-2}, {-1,-1} },

{ {1,0}, {0,0} },
{ {-1, 0}, {0,0} },
{ {0,1}, {0,0} },
{ {0,-1}, {0,0} },
{ {1,1}, {0,0} },
{ {1, -1}, {0,0} },
{ {-1,1}, {0,0} },
{ {-1,-1}, {0,0} },
{ {0, 0}, {0,0} },
{ {1, 1}, {0,0} } };*/

coordinate move(coordinate difference) // Function equivalent to map
{
    if (((difference.x == 2) || (difference.x == -2)) && ((difference.y == 2) || (difference.y == -2)))
    {
        return {difference.x / 2, difference.y / 2};
    }
    if ((difference.x == 2) || (difference.x == -2))
    {
        return {difference.x / 2, difference.y};
    }
    if ((difference.y == 2) || (difference.y == -2))
    {
        return {difference.x, difference.y / 2};
    }
    return {0, 0};
}
void read(std::vector<instruction>& instructions) // Input parsing
{

    std::string tempStr = "";

    std::getline(std::cin, tempStr);

    for (int i = 0; !tempStr.empty(); i++) // Loop for crate parsing
    {
        instructions.emplace_back(instruction(tempStr));
        std::getline(std::cin, tempStr);
    }
}

int positionsVisited(std::vector<instruction>& instructions)
{
    coordinate difference;
    coordinate knots[10];
    std::set<coordinate> visited;
    for (instruction& instruction : instructions)
    {
        for(int i = 0; i < instruction.number; i++)
        {
            knots[0] += instruction.directionModifier;
            for (int j = 1; j < 10; j++)
            {
                difference = knots[j - 1] - knots[j];
                knots[j] += move(difference);
            }
            visited.insert(knots[9]);
        }
    }
    return visited.size();
}
int main()
{
    std::cout << "Enter your grid string: \n";
    std::vector<instruction> instructions;
    read(instructions);
    std::cout << "The number of positions the tail visited atleast once are: " << positionsVisited(instructions) << "\n";
    return 0;
}