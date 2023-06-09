#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <stdexcept>

#include "CSV_field.h"


struct CSV_table
{
public:
	using Table = std::unordered_map< std::string, std::unordered_map< long long, std::shared_ptr<CSV_field> > >;

	using Column = std::unordered_map< long long, std::shared_ptr<CSV_field> >;

	CSV_table() noexcept = default;

	CSV_table(CSV_table&& other) noexcept
		: table(other.table),
		header(other.header),
		rows(other.rows)
	{
		other.header.clear();
		other.rows.clear();
		other.table.clear();
	}

	Table table = {};

	std::vector<std::string> header = {};

	std::vector<long long> rows = {};
};