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

int visibleCount(std::vector<std::vector<char>>& forest)
{
    int width = forest[0].size();
    int height = forest.size();
    int count = 0;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            bool flag[4] = {1, 1, 1, 1};
            for (int i = x - 1; i >= 0; i--) { flag[0] &= (forest[x][y] > forest[i][y]); }
            for (int i = x + 1; i < width; i++) { flag[1] &= (forest[x][y] > forest[i][y]); }
            for (int i = y - 1; i >= 0; i--) { flag[2] &= (forest[x][y] > forest[x][i]); }
            for (int i = y + 1; i < height; i++) { flag[3] &= (forest[x][y] > forest[x][i]); }
            count += (flag[0] || flag[1] || flag[2] || flag[3]);
        }
    }
    return count;
}

int main()
{
    std::cout << "Enter your grid string: \n";
    std::vector<std::vector<char>> forest;
    read(forest);
    std::cout << "The number of visible trees are: " << visibleCount(forest);
    return 0;
}