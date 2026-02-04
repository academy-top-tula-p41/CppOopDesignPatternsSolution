#include <iostream>

#include "PAIIPattern.h"

int main()
{
    try
    {
        ResourceManager manager("file.log");
        manager.Write("Hello world");
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << "\n";
    }

    std::cout << "other code\n";
}

