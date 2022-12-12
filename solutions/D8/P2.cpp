#include <iostream> 
#include <string>
#include <vector>

void read(std::vector<std::vector<char>>& forest) // Input parsing
{

    std::string tempStr = "";
    char currentCrate;

    std::getline(std::cin, tempStr);

    for (int i = 0; !tempStr.empty(); i++) // Loop for crate parsing
    {
        forest.emplace_back();
        for (char tree : tempStr)
        {
            forest[i].push_back(tree);
        }
        std::getline(std::cin, tempStr);
    }
}

int maxScenicScore(std::vector<std::vector<char>>& forest)
{
    int width = forest[0].size();
    int height = forest.size();
    int maxScenicScore = 0, tempScenicScore;
    for (int x = 1; x < width - 1; x++)
    {
        for (int y = 1; y < height - 1; y++)
        {
            bool flag[4] = {1, 1, 1, 1};
            int viewingDistance[4] = {0, 0, 0, 0};

            for (int i = x - 1; i >= 0; i--)
            { 
                viewingDistance[0] += flag[0];
                flag[0] &= (forest[x][y] > forest[i][y]);
            }
            for (int i = x + 1; i < width; i++)
            { 
                viewingDistance[1] += flag[1]; 
                flag[1] &= (forest[x][y] > forest[i][y]);
            }
            for (int i = y - 1; i >= 0; i--)
            { 
                viewingDistance[2] += flag[2]; 
                flag[2] &= (forest[x][y] > forest[x][i]);
            }
            for (int i = y + 1; i < height; i++)
            { 
                viewingDistance[3] += flag[3]; 
                flag[3] &= (forest[x][y] > forest[x][i]);
            }
            tempScenicScore = viewingDistance[0] * viewingDistance[1] * viewingDistance[2] * viewingDistance[3];
            maxScenicScore = tempScenicScore > maxScenicScore ? tempScenicScore : maxScenicScore;
        }
    }
    return maxScenicScore;
}

int main()
{
    std::cout << "Enter your grid string: \n";
    std::vector<std::vector<char>> forest;
    read(forest);
    std::cout << "The max scenic score is: " << maxScenicScore(forest);
    return 0;
}