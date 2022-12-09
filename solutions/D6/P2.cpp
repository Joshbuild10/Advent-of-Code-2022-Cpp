#include <iostream> 
#include <string>
#include <algorithm>

void read(std::string& buffer) // Input parsing
{
    char currentCrate;

    std::getline(std::cin, buffer);
}

int packetMarker(std::string& buffer)
{
    std::string window;
    for (int i = 0; i < buffer.length() - 13; i++)
    {
        window = buffer.substr(i, 14);
        std::sort(window.begin(), window.end());
        if (std::unique(window.begin(), window.end()) == window.end())
        {
            return i + 14;
        }
    }
    return 0;
}

int main()
{
    std::cout << "Enter the datastream buffer: \n";
    std::string dataBuffer;
    read(dataBuffer);
    std::cout << packetMarker(dataBuffer) << "\n";
    return 0;
}