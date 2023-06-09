#pragma once
#include <iostream>

#include "CSV.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Enter csv file's name!";
        return 1;
    }

    std::string name = argv[1];
    CSV_reader reader;
    reader.print(name);
}