#include "CSV_reader.h"

CSV_reader::CSV_reader() noexcept = default;

CSV_reader::~CSV_reader() = default;

void CSV_reader::print(const std::string& filename) const
{
	CSV_table table = get_table(filename);
	check_cycles(table);

	std::string out;
	out.reserve(table.header.size() * table.rows.size());

	out += ' ';
	for (const auto& column : table.header)
	{
		out += column + ' ';
	}
	out += '\n';

	for (const auto& row : table.rows)
	{
		out += std::to_string(row) + ' ';
		for (const auto& column : table.header)
		{
			if (column == "")
				continue;

			out += std::to_string( (*table.table[column][row]).get_value() ) + ' ';
		}
		out += '\n';
	}
	std::cout << out;
}

CSV_table CSV_reader::get_table(const std::string& filename) const
{
	CSV_parser parser;
	return parser.read(filename);
}

void CSV_reader::check_cycles(const CSV_table& table) const
{
	CSV_cyclic_dependency checker;
	if (checker.has_cyclic_dependencies(table))
		throw std::runtime_error("Given csv file has cyclic dependencies between fields");
}