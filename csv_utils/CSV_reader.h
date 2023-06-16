#pragma once
#include <string>
#include <iostream>
#include <ostream>

#include "CSV_table.hpp"
#include "CSV_parser.h"
#include "CSV_cyclic_dependency.h"

class CSV_reader
{
public:

	CSV_reader() noexcept;

	~CSV_reader();

	void print(const std::string& filename) const;

private:

	CSV_table get_table(const std::string& filename) const;

	void check_cycles(const CSV_table& table) const;
};

