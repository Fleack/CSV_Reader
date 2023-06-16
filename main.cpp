#pragma once
#include <iostream>

#include "CSV.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Enter name of csv file!";
        return 1;
    }

	try
	{
		std::string name = argv[1];
		CSV_reader reader;
		reader.print(name);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception!" << '\n';
		std::cout << ex.what();
	}
}