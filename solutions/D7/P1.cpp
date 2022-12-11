#include <iostream> 
#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include <map>

class file
{
public:
    uint64_t size;
    std::string name;
};

class directory
{
public:
    std::string name;
    uint64_t size = 0;
    std::vector<file> files = {};
    std::map<std::string, directory> directories = {};

    directory(std::string name = "/")
    {
        this->name = name;
    }

    int assignSizes()
    {
        for (file file : files)
        {
            size += file.size;
        }
        for (auto& [key, val] : directories)
        {
            size += val.assignSizes();
        }
        return size;
    }

    void read(directory* root)
    {
        std::string buffer;
        std::string bufferArr[2];
        bool isCommand = 0;

        std::getline(std::cin, buffer);
        while (!buffer.empty())
        {
            std::stringstream ss(buffer);
            ss >> bufferArr[0];
            ss >> bufferArr[0];

            if (bufferArr[0] == "cd")
            {
                ss >> bufferArr[1];

                if (bufferArr[1] == "/")  { (*root).read(root); return;}
                else if(bufferArr[1] == "..") { return; }
                else{ directories[bufferArr[1]].read(root); }
            }

            std::getline(std::cin, buffer);
            if (bufferArr[0] == "ls")
            {
                while(!buffer.empty() && buffer[0] != '$')
                {
                    std::stringstream ss2(buffer);
                    ss2 >> bufferArr[0];
                    ss2 >> bufferArr[1];
                    if (bufferArr[0] == "dir") { directories.insert({bufferArr[1], directory(bufferArr[1])}); }
                    else { files.push_back({stoull(bufferArr[0]), bufferArr[1]}); }
                    std::getline(std::cin, buffer);
                }
            }
        }
        if (name == "/") { assignSizes(); }
    }

    void printContents(int tabs = 0)
    {
        std::cout << std::string(tabs, ' ') << "- " << name << " (dir, size=" << size << ")\n";
        for (file file : files)
        {
            std::cout << std::string(tabs + 1, ' ') << "- " << file.name << " (file, size=" << file.size << ")\n";
        }
        for (auto& [key, val] : directories)
        {
            val.printContents(tabs + 1);
        }
    }

    uint64_t sizeOfMinorFiles(uint64_t limit)
    {
        uint64_t sum = 0;
        sum += size <= limit ? size : 0;
        for (auto& [key, val] : directories)
        {
            sum += val.sizeOfMinorFiles(limit);
        }
        return sum;
    }
};

int main()
{
    std::cout << "Enter the terminal output: \n";
    directory root;
    root.read(&root);
    //root.printContents();
    std::cout << "The total size of files less than 100000 is: " << root.sizeOfMinorFiles(100000) << "\n";
    return 0;
}