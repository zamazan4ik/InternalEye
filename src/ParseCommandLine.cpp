#include "ParseCommandLine.h"
#include <QString>
#include <iostream>

bool parseLine(const int argc, char *argv[])
{
    if(argc == 1)   return true;
    for(size_t i = 2; i <= argc; ++i)
    {
        if(strcmp(argv[i - 1], "--version") == 0)
        {
            std::cout << "0.0.1" << std::endl;
            return false;
        }
    }
    return true;
}
